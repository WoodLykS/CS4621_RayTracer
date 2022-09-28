#ifndef RAY_H
#define RAY_H
#include <iostream>
#include "vec3.h"

class ray
{
  vec3 origin;
  vec3 direction;

public:
  ray();
  ray(vec3 a, vec3 b);
  vec3 &get_origin();
  vec3 &get_direction();
  vec3 &point_at_time(double t);
};
#endif