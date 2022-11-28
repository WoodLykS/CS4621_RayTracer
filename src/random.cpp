#include "all.h"
using namespace std;

// vertical linear color interpolation aka lerp
// color ray_color(ray &r, hittable &world, int depth)
// {
//   hit_record rec;

//   // If we've exceeded the ray bounce limit, no more light is gathered.
//   if (depth <= 0)
//     return color(0, 0, 0);

//   if (world.hit(r, 0.001, infinity, rec))
//   {
//     ray scattered;
//     color attenuation;
//     if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
//       return attenuation * ray_color(scattered, world, depth - 1);
//     return color(0, 0, 0);
//   }

//   vec3 unit_direction = r.velocity.normalize();
//   int t = 0.5 * (unit_direction.y() + 1.0);
//   return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
// }

color ray_color(ray &r, color background, hittable &world, int depth)
{
  hit_record rec;

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    return color(0, 0, 0);

  // If the ray hits nothing, return the background color.
  if (!world.hit(r, 0.001, infinity, rec))
    return background;

  ray scattered;
  color attenuation;
  color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

  if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
    return emitted;

  return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}

hittable_list random_scene()
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

int main()
{
  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 1440;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 500;
  const int max_depth = 50;
  srand(time(NULL));

  hittable_list world = random_scene();
  camera cam(point3(13, 2, 4), point3(0, 0, 0), vec3(0, 1, 0), 50,
             aspect_ratio, 0, 20);

  freopen("random.ppm", "w", stdout);
  // Render
  cout << "P3\n"
       << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j)
  {
    cerr << "\rScanlines remaining: " << j << ' ' << flush;
    for (int i = 0; i < image_width; ++i)
    {
      color pixel_color(0, 0, 0);
      for (int k = 0; k < samples_per_pixel; k++)
      {
        double u = (i + rand_unit()) / (image_width - 1);
        double v = (j + rand_unit()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, color(0.4, 0.4, 0.4), world, max_depth);
      }
      // pixel_color =
      write_color(cout, pixel_color, samples_per_pixel);
    }
  }

  cerr << "\nDone.\n";
  return 0;
}
