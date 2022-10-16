//////////// Wed Sep 28 1:13 AM ////////////
#include "math/util.h"
#include "math/hittable.h"
#include "math/hittablelist.h"
#include "math/sphere.h"
#include "math/vec3.h"
#include "math/camera.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

// vertical linear color interpolation aka lerp
color ray_color(ray r, hittable &world)
{
  hit_record rec;
  if (world.hit(r, 0, infinity, rec))
  {
    return (rec.normal + color(1, 1, 1)) * 0.5;
  }
  vec3 unit_velocity = r.velocity.normalize();
  // cout << unit_velocity.x() << unit_velocity.y() << unit_velocity.z() << endl;
  double t = 0.5 * (unit_velocity.y() + 1.0);
  color e1 = color(1.0, 1.0, 1.0), e2 = color(0.5, 0.7, 1.0);
  e1 *= 1.0 - t;
  e2 *= t;
  e1 += e2;
  return e1;
}

int main()
{
  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 960;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  srand(time(NULL));

  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Camera
  camera cam;

  // double viewpoint_height = 2.0;
  // double viewpoint_width = aspect_ratio * viewpoint_height;
  // double focal_length = 1.0;

  // point3 origin = point3(0, 0, 0);
  // vec3 horizontal = vec3(viewpoint_width, 0, 0);
  // vec3 vertical = vec3(0, viewpoint_height, 0);
  // point3 lower_left_corner = origin;
  // lower_left_corner -= (horizontal / 2);
  // lower_left_corner -= (vertical / 2);
  // lower_left_corner -= vec3(0, 0, focal_length);

  freopen("pic.ppm", "w", stdout);

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
        pixel_color += ray_color(r, world);
      }
      // pixel_color =
      write_color(cout, pixel_color, samples_per_pixel);
    }
  }

  cerr << "\nDone.\n";
  return 0;
}

// #include <iostream>
// #include "math/vec3.h"
// using namespace std;
// int main()
// {
//   point3 a = vec3(1, 2, 3);
//   cout << a << endl;

//   freopen("1.ppm", "w", stdout);
//   //  Image
//   const int image_width = 2;
//   const int image_height = 2;
//   // Render
//   cout << "P3 \n"
//        << image_width << " " << image_height << " " << '\n';
//   cout << "255 " << '\n';
//   for (int j = image_height - 1; j >= 0; --j)
//   {
//     // std::cerr << "\rScanlines remaining: " << j << ' ' << flush;
//     for (int i = 0; i < image_width; ++i)
//     {
//       double r = double(i) / (image_width - 1);
//       double g = double(j) / (image_height - 1);
//       double b = 0.25;

//       int ir = static_cast<int>(255.999 * r);
//       int ig = static_cast<int>(255.999 * g);
//       int ib = static_cast<int>(255.999 * b);

//       cout << ir << ' ' << ig << ' ' << ib << ' ' << '\n';
//     }
//   }
//   // std::cerr << "\nDone.\n";
//   return 0;
// }