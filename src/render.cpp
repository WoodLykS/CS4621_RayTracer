#include "all.h"
#include <time.h>
using namespace std;

const double aspect_ratio = 16.0 / 9.0;
const int image_width = 1440;
const int image_height = static_cast<int>(image_width / aspect_ratio);
const int samples_per_pixel = 500;
const int max_depth = 50;
const color BACKGROUND = color(0.4, 0.4, 0.4);
SCENE scene = GET_SCENE_random(aspect_ratio);
hittable_list world = scene.world;
camera cam = scene.cam;
vec3 pixels[image_height][image_width];
thread threadBank[image_height][image_width];
// vector<thread> v[image_height + 1];
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
  current_pixel += ray_color(r, BACKGROUND, world, max_depth);
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

vec3 pixel[image_width + 1];
void render_pixel(int i, int j)
{
  for (int k = 0; k < samples_per_pixel; k++)
  {
    double u = (i + rand_unit()) / (image_width - 1);
    double v = (j + rand_unit()) / (image_height - 1);
    ray r = cam.get_ray(u, v);
    pixel[i] += ray_color(r, BACKGROUND, world, max_depth);
  }
}

void render_line(int j)
{
  vector<thread> q;

  for (int i = 0; i < image_width; ++i)
  {
    pixel[i] = vec3(0, 0, 0);
    q.emplace_back(render_pixel, i, j);
  }
  for (int i = 0; i < image_width; ++i)
  {
    q[i].join();
    write_color(cout, pixel[i], samples_per_pixel);
  }
}
int main()
{
  auto t1 = chrono::high_resolution_clock::now();
  srand(time(NULL));
  freopen("render.ppm", "w", stdout);

  // Render
  cout << "P3\n"
       << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j)
  {
    cerr << "\rScanlines remaining: " << j << ' ' << flush;
    render_line(j);
  }
  // new_write_color(cout);
  cerr << "\nDone.\n";
  auto t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, std::milli> ms_double = t2 - t1;
  cerr << ms_double.count() / 1000 << endl;
  return 0;
}