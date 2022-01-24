#include <iostream>
#include <Scene.h>
#include <Material/Lambert.h>
#include <Material/Metal.h>
#include <Material/Light.h>
#include <Material/Dielectric.h>
#include <Shape/Sphere.h>
#include <Shape/Cube.h>
#include <Texture/Solid.h>
#include <Texture/Checker.h>
#include <Texture/Image.h>
#include <Camera/PerspectiveCamera.h>
#include <Renderer/BasicRenderer.h>
#include <FileFormat/PPM.h>

using namespace std;
using namespace raytrace;

int main() {
  std::cout << "Hello, World!" << std::endl;
  Scene scene;
  // front wall
  scene.AddObject(
      shape::Cube(Point(0, 0, 5), Vector(0, 0, 1), Vector(0, 1, 0), 0.1, 100, 100),
      material::LambertDiffuse(),
//      material::Metal(),
      texture::Solid(Color::White() * 0.8));
  // back wall
  scene.AddObject<shape::Cube, material::LambertDiffuse, texture::Solid>(
      shape::Cube(Point(0, 0, -1), Vector(0, 0, 1), Vector(0, 1, 0), 0.1, 100, 100),
      material::LambertDiffuse(),
      texture::Solid(Color::White() * 0.8));
  // left wall
  scene.AddObject<shape::Cube, material::LambertDiffuse, texture::Solid>(
      shape::Cube(Point(-5, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 100, 0.1),
      material::LambertDiffuse(),
      texture::Solid(Color::White() * 0.8));
  // right wall
  scene.AddObject<shape::Cube, material::LambertDiffuse, texture::Solid>(
      shape::Cube(Point(5, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 100, 0.1),
      material::LambertDiffuse(),
      texture::Solid(Color::White() * 0.8));
  // top
  scene.AddObject<shape::Cube, material::LambertDiffuse, texture::Solid>(
      shape::Cube(Point(0, 3, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 0.1, 100),
      material::LambertDiffuse(),
      texture::Solid(Color::White() * 0.8));
  // floor
  scene.AddObject(
      shape::Cube(Point(0, -0.05, 0), Vector(0, 0, 1), Vector(0, 1, 0), 100, 0.1, 100),
      material::LambertDiffuse(),
      texture::Checker(Color::White(), Color::White() * 0.3, 100)
//      texture::Solid(Color::White() * 0.8)
      );
  // light
  scene.AddObject(
      shape::Sphere(Point(0, 13.2, 2.5), 10.3),
      material::Light(Color::White() * 10.5),
      texture::Solid(Color::Black()));
  // objects
  scene.AddObject(
      shape::Sphere(Point(0.3, 0.9, 2.7), 0.9),
      material::Metal(),
      texture::Solid(Color(0.7, 0.71, 0.15)));
  scene.AddObject(
      shape::Sphere(Point(1.2, 0.5, 1.5), 0.5),
      material::LambertDiffuse(),
      texture::Image("../resource/image/earthmap.jpeg")
      );
  scene.AddObject(
      shape::Sphere(Point(-0.8, 0.45, 1.7), 0.45),
      material::Dielectric(1.3),
      texture::Solid(Color::White()));
  size_t height = 480, width = 640;
  RT_FLOAT aspect = static_cast<RT_FLOAT>(width) / static_cast<RT_FLOAT>(height);
  camera::PerspectiveCamera camera(120, aspect, Point(0, 1.0, 0.2), Point(0, 0.4, 2.5), Vector(0, 1, 0));
  renderer::BasicRenderer renderer(width, height, 10000, 8);
  renderer::RenderSet rset(scene, camera);
  Canvas canvas = renderer.Render(rset);
  file_format::PPM ppm(canvas);
  ppm.Output("test.ppm");
  return 0;
}
