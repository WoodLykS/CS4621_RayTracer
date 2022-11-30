#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "hittable.h"
#include "hittablelist.h"
class aabb
{
public:
  point3 minimum;
  point3 maximum;

  aabb();
  aabb(point3 v1, point3 v2);
  bool hit(ray r, float t_min, float t_max);
};

aabb::aabb()
{
  minimum = vec3();
  maximum = vec3();
}
aabb::aabb(point3 v1, point3 v2)
{
  minimum = v1;
  maximum = v2;
}

bool aabb::hit(ray r, float t_min, float t_max)
{
  vec3 ori = r.origin;
  vec3 invD = vec3(1 / r.velocity.x(), 1 / r.velocity.y(), 1 / r.velocity.z());
  vec3 lbound = (minimum - ori) * invD;
  vec3 rbound = (maximum - ori) * invD;
  for (int i = 0; i < 3; i++)
  {
    float t0 = min(lbound[i], rbound[i]);
    float t1 = max(lbound[i], rbound[i]);
    float tmin = max(t_min, t0);
    float tmax = min(t_max, t1);
    if (tmax < tmin)
    {
      return false;
    }
  }
  return true;
}

#endif