#include "BVH.h"
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <queue>
#include <Object.h>
namespace raytrace {
RT_FLOAT get_dimension(const Vector &v, int d) {
  switch (d) {
    case 0: return v.X();
    case 1: return v.Y();
    default: return v.Z();
  }
}

RT_FLOAT BVHNode::Volume() const {
  return (boundary_[0][1] - boundary_[0][0]) * (boundary_[1][1] - boundary_[1][0]) * (boundary_[1][1] - boundary_[1][0]);
}

/**
 * if this returns true, means there `could` be intersection;
 * otherwise there is no intersection
 */
bool BVHNode::FastBoxIntersect(const Ray &ray, RT_FLOAT t) const {
  Point begin = ray.Origin();
  Point end = ray.Calculate(t);
  RT_FLOAT x_min = std::min(begin.X(), end.X()),
           x_max = std::max(begin.X(), end.X()),
           y_min = std::min(begin.Y(), end.Y()),
           y_max = std::max(begin.Y(), end.Y()),
           z_min = std::min(begin.Z(), end.Z()),
           z_max = std::max(begin.Z(), end.Z());
  return !(x_max < boundary_[0][0] || x_min > boundary_[0][1] ||
           y_max < boundary_[1][0] || y_min > boundary_[1][1] ||
           z_max < boundary_[2][0] || z_min > boundary_[2][1]);
}

bool BVHNode::BoxIntersect(const raytrace::Ray &ray, RT_FLOAT t) const {
  if (!FastBoxIntersect(ray, t)) {
    return false;
  }
  const std::array<Vector, 3> directions{Vector{1, 0, 0}, Vector{0, 1, 0}, Vector{0, 0, 1}};
  for (int di = 0; di < 3; di++) {
    Vector d = directions[di];
    int face_id = d.dot(ray.Direction()) < 0;
    const Point p1 = d * boundary_[di][face_id];
    d *= face_id * 2 - 1;
    RT_FLOAT solution = (p1 - ray.Origin()).dot(d) / ray.Direction().dot(d);
    auto intersection = ray.Calculate(solution);
    auto coord1 = get_dimension(intersection, (di + 1) % 3), coord2 = get_dimension(intersection, (di + 2) % 3);
    if (boundary_[(di + 1) % 3][0] <= coord1 && coord1 <= boundary_[(di + 1) % 3][1] &&
        boundary_[(di + 2) % 3][0] <= coord2 && coord2 <= boundary_[(di + 2) % 3][1] &&
        solution < t) {
      return true;
    }
  }
  return false;
}

BVHLeaf::BVHLeaf(RT_FLOAT xlo, RT_FLOAT xhi, RT_FLOAT ylo, RT_FLOAT yhi, RT_FLOAT zlo, RT_FLOAT zhi, const Hittable *object) :
    BVHNode(xlo, xhi, ylo, yhi, zlo, zhi), object_(object) {

}

bool BVHLeaf::Intersect(const raytrace::Ray &ray, raytrace::Intersection &intersection) const {
  return BoxIntersect(ray, intersection.m_t_) && object_->Intersect(ray, intersection);
}

BVHRoot::BVHRoot(std::shared_ptr<BVHNode> left, std::shared_ptr<BVHNode> right)
    : BVHNode(std::min(left->boundary_[0][0], right->boundary_[0][0]),
              std::max(left->boundary_[0][1], right->boundary_[0][1]),
              std::min(left->boundary_[1][0], right->boundary_[1][0]),
              std::max(left->boundary_[1][1], right->boundary_[1][1]),
              std::min(left->boundary_[2][0], right->boundary_[2][0]),
              std::max(left->boundary_[2][1], right->boundary_[2][1])),
      left_(std::move(left)),
      right_(std::move(right)) {
}

bool BVHRoot::Intersect(const raytrace::Ray &ray, raytrace::Intersection &intersection) const {
  if (!BoxIntersect(ray, intersection.m_t_)) {
    return false;
  }
  bool ret = false;
  ret = left_->Intersect(ray, intersection) || ret;
  ret = right_->Intersect(ray, intersection) || ret;
  return ret;
}

struct triple_greater {
  using value_type = std::tuple<RT_FLOAT, int, int>;
  bool operator()(const value_type &lhs, const value_type &rhs) const {
    return std::get<0>(lhs) > std::get<0>(rhs);
  }
};

std::shared_ptr<BVHNode> BuildBVHTree(const std::list<std::unique_ptr<AbstractObject> > &objects) {
  if (objects.size() == 1) {
    return (*objects.begin())->BVH();
  }
  std::map<int, std::shared_ptr<BVHNode>> leaves;
  int n = 0;
  for (auto &obj : objects) {
    leaves.emplace(n++, obj->BVH());
  }

  std::priority_queue<std::tuple<RT_FLOAT, int, int>, std::vector<std::tuple<RT_FLOAT, int, int> >, triple_greater> queue;
  std::set<int> deleted;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      queue.emplace(BVHRoot(leaves[i], leaves[j]).Volume() - leaves[i]->Volume() - leaves[j]->Volume(), i, j);
    }
  }
  while (!queue.empty()) {
    int n1, n2;
    do {
      auto elem = queue.top();
      n1 = std::get<1>(elem);
      n2 = std::get<2>(elem);
      queue.pop();
    } while (!queue.empty() && (deleted.count(n1) > 0 || deleted.count(n2) > 0));
    if (queue.empty())
      break;
    deleted.emplace(n1);
    deleted.emplace(n2);
    auto new_obj = std::make_shared<BVHRoot>(leaves[n1], leaves[n2]);
    leaves.erase(n1);
    leaves.erase(n2);
    leaves.emplace(n++, new_obj);
    for (auto &tup : leaves) {
      if (tup.first == n-1)
        continue;
      queue.emplace(BVHRoot(new_obj, tup.second).Volume() - new_obj->Volume() - tup.second->Volume(),
                    tup.first,
                    n-1);
    }
  }
  return leaves.begin()->second;
}

}