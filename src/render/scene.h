#ifndef SCENE_H
#define SCENE_H
#include "../math/hittablelist.h"
#include "material.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"

hittable_list GET_SCENE_1()
{
  hittable_list world;
  Material_L material_ground = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  Material_L material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  Material_D material_left = make_shared<dielectric>(1.5);
  Material_M material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
  world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
  world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
  return world;
}

hittable_list GET_SCENE_random()
{
  hittable_list world;

  auto ground_material = make_shared<lambertian>(color(0.4, 0.4, 0.4));
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  // for (int a = -11; a < 11; a++)
  // {
  //   for (int b = -11; b < 11; b++)
  //   {
  //     auto choose_mat = rand_unit();
  //     point3 center(a + 0.9 * rand_unit(), 0.2, b + 0.9 * rand_unit());

  //     if ((center - point3(4, 0.2, 0)).norm() > 0.9)
  //     {
  //       shared_ptr<material> sphere_material;

  //       if (choose_mat < 0.8)
  //       {
  //         // diffuse
  //         auto albedo = vrandom() * vrandom();
  //         sphere_material = make_shared<lambertian>(albedo);
  //         world.add(make_shared<sphere>(center, 0.2, sphere_material));
  //       }
  //       else if (choose_mat < 0.95)
  //       {
  //         // metal
  //         auto albedo = vrandom();
  //         auto fuzz = rand_range(0, 0.5);
  //         sphere_material = make_shared<metal>(albedo, fuzz);
  //         world.add(make_shared<sphere>(center, 0.2, sphere_material));
  //       }
  //       else
  //       {
  //         // glass
  //         sphere_material = make_shared<dielectric>(1.5);
  //         world.add(make_shared<sphere>(center, 0.2, sphere_material));
  //       }
  //     }
  //   }
  // }

  // glass
  auto material1 = make_shared<dielectric>(1.5);
  // world.add(make_shared<sphere>(point3(0, 1, -2), 1.0, material1));
  //  world.add(make_shared<sphere>(point3(0, 0.5, -2), -0.5, material1));

  auto material2 = make_shared<lambertian>(color(0.8, 0.0, 0.0));
  world.add(make_shared<sphere>(point3(-4, 1, -0.5), 1.0, material2));

  auto material3 = make_shared<metal>(color(0.4, 0.4, 0.7), 0.2);
  world.add(make_shared<sphere>(point3(4, 1, 2), 1.0, material3));

  world.add(make_shared<box>(vec3(6, 0, 3), vec3(7, 1, 4), material2));
  world.add(make_shared<box>(vec3(6, 1, 2.5), vec3(7, 2, 3.5), material1));

  auto LIGHT_Blue = make_shared<light>(color(1, 1, 1));
  auto LIGHT_Orange = make_shared<light>(color(1, 0.5, 0));
  world.add(make_shared<sphere>(point3(4, 0.7, 4.5), 0.7, LIGHT_Blue));
  world.add(make_shared<sphere>(point3(6, 0.3, 0.5), 0.3, LIGHT_Orange));

  world.add(make_shared<box>(vec3(6, 0, -0.5), vec3(7, 1, 0), material1));

  auto material4 = make_shared<metal>(color(0.9, 0.4, 0.5), 0);
  world.add(make_shared<sphere>(point3(6.5, 0.5, 2.5), 0.5, material1));

  auto material5 = make_shared<metal>(color(0.6, 0.2, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(4, 1, -5), 1.0, material4));

  auto material6 = make_shared<dielectric>(0.7);
  world.add(make_shared<sphere>(point3(8.5, 0.7, 0), 0.7, material6));

  auto material7 = make_shared<metal>(color(0.6, 0.2, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(-3, 1, -5), 1.0, material7));
  world.add(make_shared<sphere>(point3(-3, 1, 7), 1.0, material7));
  world.add(make_shared<sphere>(point3(-9, 1, -3), 1.0, material7));

  auto LIGHT_Red = make_shared<light>(color(1, 0, 0));
  world.add(make_shared<sphere>(point3(-6.5, 2, 6), 2, LIGHT_Red));

  auto material8 = make_shared<metal>(color(1, 1, 1), 0.2);
  world.add(make_shared<sphere>(point3(-2, 1, 3), 1.0, material8));
  return world;
}
#endif