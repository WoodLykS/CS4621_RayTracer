#include "all.h"

using namespace std;

const double aspect_ratio = 16.0 / 9.0;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);
const int samples_per_pixel = 1440;
const int max_depth = 50;
hittable_list world;
camera cam(point3(3, 3, 2), point3(0, 0, -1), vec3(0, 1, 0), 20.0,
           aspect_ratio, 0.1, 10);
vec3 pixels[image_height][image_width];
thread threadBank[image_height][image_width];
vector<thread> v[image_height + 1];
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

// pixels should be an array of array of color/vec3
void new_write_color(ostream &out)
{
  for (int i = 0; i < image_height; i++)
  {
    for (int j = 0; j < image_width; j++)
    {
      // v[i][j].join();
      out << static_cast<int>(255.99 * pixels[i][j].x()) << ' '
          << static_cast<int>(255.99 * pixels[i][j].y()) << ' '
          << static_cast<int>(255.99 * pixels[i][j].z()) << '\n';
    }
  }
}

color current_pixel;
void add_color(double u, double v)
{
  ray r = cam.get_ray(u, v);
  current_pixel += ray_color(r, world, max_depth);
}
color one_pixel_multisample(int i, int j)
{
  // cerr << "*" << i << " " << j << endl;
  current_pixel = color(0, 0, 0);
  vector<thread> thread_queue;
  for (int k = 0; k < samples_per_pixel; k++)
  {
    double u = (i + rand_unit()) / (image_width - 1);
    double v = (j + rand_unit()) / (image_height - 1);
    thread_queue.emplace_back(add_color, u, v);
  }
  for (int k = 0; k < samples_per_pixel; k++)
  {
    thread_queue[k].join();
  }
  return current_pixel;
}

int main()
{
  // Image

  srand(time(NULL));
  // World

  Material_L material_ground = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  Material_L material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  Material_D material_left = make_shared<dielectric>(1.5);
  Material_M material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

  world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
  world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

  freopen("render.ppm", "w", stdout);

  // Render
  cout << "P3\n"
       << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j)
  {
    cerr << "\rScanlines remaining: " << j << ' ' << flush;
    for (int i = 0; i < image_width; ++i)
    {
      // cerr << i << " " << j << endl;
      // // thread t(one_pixel, i, j, cam, world);
      // v[j].emplace_back(one_pixel, i, j);
      color p = one_pixel_multisample(i, j);
      write_color(cout, p, samples_per_pixel);
    }
  }
  // new_write_color(cout);

  cerr << "\nDone.\n";
  return 0;
}
