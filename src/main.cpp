#include <iostream>
#include <Scene.h>
#include <Material/Lambert.h>
#include <Material/Metal.h>
#include <Material/Light.h>
#include <Shape/Sphere.h>
#include <Shape/Cube.h>
#include <Camera/PerspectiveCamera.h>
#include <Renderer/BasicRenderer.h>
#include <FileFormat/PPM.h>

using namespace std;
using namespace raytrace;

int main() {
  std::cout << "Hello, World!" << std::endl;
  Scene scene;
  auto diffuse = scene.AddMaterial<material::LambertDiffuse>(Color::White() * 0.9);
  auto green_diffuse = scene.AddMaterial<material::LambertDiffuse>(Color(0.1, 0.7, 0.15));
  auto metal = scene.AddMaterial<material::Metal>(Color(0.7, 0.71, 0.15));
  auto white_wall = scene.AddMaterial<material::LambertDiffuse>(Color(0.42, 0.41, 0.435) * 1.5);
  auto purple_wall = scene.AddMaterial<material::LambertDiffuse>(Color(0.7, 0.71, 0.15));
  auto green_wall = scene.AddMaterial<material::LambertDiffuse>(Color::Green() * 0.7);
  auto light_purple = scene.AddMaterial<material::Light>(Color(1.0, 0.7, 1.3));
  auto light_white = scene.AddMaterial<material::Light>(Color::White() * 10.5);
  // front wall
  scene.AddShape<shape::Cube>(Point(0, 0, 5), Vector(0, 0, 1), Vector(0, 1, 0), 0.1, 100, 100, white_wall);
  // back wall
  scene.AddShape<shape::Cube>(Point(0, 0, -1), Vector(0, 0, 1), Vector(0, 1, 0), 0.1, 100, 100, white_wall);
  // left wall
  scene.AddShape<shape::Cube>(Point(-5, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 100, 0.1, purple_wall);
  // right wall
  scene.AddShape<shape::Cube>(Point(5, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 100, 0.1, green_wall);
  // top
  scene.AddShape<shape::Cube>(Point(0, 3, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 0.1, 100, white_wall);
  // floor
  scene.AddShape<shape::Cube>(Point(0, -0.05, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 0.1, 100, white_wall);
  // light
  scene.AddShape<shape::Sphere>(Point(0, 13.2, 2.5), 10.3, light_white);
  // objects
  scene.AddShape<shape::Sphere>(Point(1.0, 0.9, 2.7), 0.9, metal);
  scene.AddShape<shape::Sphere>(Point(0.8, 0.5, 1.5), 0.5, diffuse);
  scene.AddShape<shape::Sphere>(Point(-1.2, 0.25, 2.2), 0.25, diffuse);
  scene.AddShape<shape::Sphere>(Point(-0.8, 0.45, 1.7), 0.45, green_diffuse);
  size_t height = 480, width = 640;
  RT_FLOAT aspect = static_cast<RT_FLOAT>(width) / static_cast<RT_FLOAT>(height);
  camera::PerspectiveCamera camera(120, aspect, Point(0, 1.0, 0.2), Point(0, 0.4, 2.5), Vector(0, 1, 0));
  renderer::BasicRenderer renderer(width, height, 5000, 7);
  renderer::RenderSet rset(scene, camera);
  Canvas canvas = renderer.Render(rset);
  file_format::PPM ppm(canvas);
  ppm.Output("test.ppm");
  return 0;
}
