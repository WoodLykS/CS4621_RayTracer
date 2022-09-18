#include <iostream>
#include "math/vec3.h"
#include "math/ray.h"
using namespace std;
int main()
{
  point3 a = vec3(1, 2, 3);
  point3 b = vec3(1, 2, 3);
  // point3 b = vec3(3, 1, 3);
  // cout << a.dot(b) << endl;
  cout << a << endl;
  a -= b;
  cout << a.cross(b) << endl;

  ray xaxis = ray(vec3(0, 0, 0), vec3(1, 0, 0));

  point3 x10 = xaxis.point_at_time(10);

  cout << x10 << endl;
  // freopen("1.ppm", "w", stdout);
  //  Image
  const int image_width = 2;
  const int image_height = 2;
  // Render
  cout << "P3 \n"
       << image_width << " " << image_height << " " << '\n';
  cout << "255 " << '\n';
  for (int j = image_height - 1; j >= 0; --j)
  {
    // std::cerr << "\rScanlines remaining: " << j << ' ' << flush;
    for (int i = 0; i < image_width; ++i)
    {
      double r = double(i) / (image_width - 1);
      double g = double(j) / (image_height - 1);
      double b = 0.25;

      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);

      cout << ir << ' ' << ig << ' ' << ib << ' ' << '\n';
    }
  }
  // std::cerr << "\nDone.\n";
  return 0;
}