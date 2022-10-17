#include "all.h"
using namespace std;

// vertical linear color interpolation aka lerp
color ray_color(ray &r, hittable &world, int depth)
{
  hit_record rec;

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    return color(0, 0, 0);

  if (world.hit(r, 0.001, infinity, rec))
  {
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);
    return color(0, 0, 0);
  }

  vec3 unit_direction = r.velocity.normalize();
  int t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;
  srand(time(NULL));

  // World
  hittable_list world;

  Material_L material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  Material_L material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
  Material_M material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
  Material_M material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

  world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
  world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
  // Camera
  camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);

  freopen("render.ppm", "w", stdout);

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
        pixel_color += ray_color(r, world, max_depth);
      }
      // pixel_color =
      write_color(cout, pixel_color, samples_per_pixel);
    }
  }

  cerr << "\nDone.\n";
  return 0;
}
