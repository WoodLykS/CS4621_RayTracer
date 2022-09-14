#include <iostream>
#include "math/vec3.h"
using namespace std;
int main()
{
  point3 a = vec3(1, 2, 3);
  cout << a << endl;

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
      auto r = double(i) / (image_width - 1);
      auto g = double(j) / (image_height - 1);
      auto b = 0.25;

      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);

      cout << ir << ' ' << ig << ' ' << ib << ' ' << '\n';
    }
  }
  // std::cerr << "\nDone.\n";
  return 0;
}