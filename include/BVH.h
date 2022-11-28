#ifndef RAYTRACE_INCLUDE_BVH_H_
#define RAYTRACE_INCLUDE_BVH_H_
#include <array>
#include <list>
#include <memory>
#include "Hittable.h"
namespace raytrace {
class BVHNode : public Hittable {
 public:
  BVHNode(RT_FLOAT xlo, RT_FLOAT xhi, RT_FLOAT ylo, RT_FLOAT yhi, RT_FLOAT zlo, RT_FLOAT zhi) {
    boundary_[0][0] = xlo;
    boundary_[0][1] = xhi;
    boundary_[1][0] = ylo;
    boundary_[1][1] = yhi;
    boundary_[2][0] = zlo;
    boundary_[2][1] = zhi;
  }
 protected:
  bool BoxIntersect(const Ray &ray, RT_FLOAT t) const;
  bool FastBoxIntersect(const Ray &ray, RT_FLOAT t) const;
 private:
  std::array<std::array<RT_FLOAT, 2>, 3> boundary_;
  friend std::shared_ptr<BVHNode> BuildBVHTree(const std::list<std::unique_ptr<AbstractObject> > &objects);
  friend class BVHRoot;
};

class BVHLeaf : public BVHNode {
 public:
  BVHLeaf(RT_FLOAT xlo, RT_FLOAT xhi, RT_FLOAT ylo, RT_FLOAT yhi, RT_FLOAT zlo, RT_FLOAT zhi, const Hittable *object);
  bool Intersect(const Ray &ray, Intersection &) const override;
 private:
  const Hittable *object_;
};


class BVHRoot : public BVHNode {
 public:
  BVHRoot(std::shared_ptr<BVHNode> left, std::shared_ptr<BVHNode> right);
  bool Intersect(const Ray &ray, Intersection &) const override;
 private:
  std::shared_ptr<BVHNode> left_, right_;
};

std::shared_ptr<BVHNode> BuildBVHTree(const std::list<std::unique_ptr<AbstractObject> > &objects);
}
#endif //RAYTRACE_INCLUDE_BVH_H_
