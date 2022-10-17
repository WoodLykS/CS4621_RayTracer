#ifndef CAMERAH
#define CAMERAH

#include "vec3.h"
#include "ray.h"

class camera
{
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;

public:
  camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio)
  {

    double theta = degrees_to_radians(vfov);
    double h = tan(theta / 2);
    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    double focal_length = 1;

    vec3 w = (lookfrom - lookat).normalize();
    vec3 u = vup.cross(w).normalize();
    vec3 v = w.cross(u);

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    // double aspect_ratio = 16.0 / 9.0;
    // double viewport_height = 2.0;
    // double viewport_width = aspect_ratio * viewport_height;
    // double focal_length = 1.0;

    // origin = point3(0, 0, 0);
    // horizontal = vec3(viewport_width, 0.0, 0.0);
    // vertical = vec3(0.0, viewport_height, 0.0);
    // lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
  }

  ray get_ray(double u, double v)
  {
    return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
  }
};

#endif