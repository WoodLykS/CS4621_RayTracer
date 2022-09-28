#include <iostream>
#include <cmath>
#include "ray.h"

ray::ray()
{
  origin = vec3();
  direction = vec3();
}
ray::ray(vec3 a, vec3 b)
{
  origin = a;
  direction = b;
}

vec3 &ray::get_origin() { return origin; }

vec3 &ray::get_direction() { return direction; }

vec3 &ray::point_at_time(double t)
{
  point3 v = origin.plus(direction.times(t));
  return v;
}