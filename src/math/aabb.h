#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "hittable.h"
#include "hittablelist.h"
class aabb
{

  point3 minimum;
  point3 maximum;
  hittable_list lst;

  aabb();
  aabb(point3 v1, point3 v2, hittable_list lst);
  bool hit(ray r, float t_min, float t_max);
};

aabb::aabb()
{
  minimum = vec3();
  maximum = vec3();
  lst = hittable_list();
}
aabb::aabb(point3 v1, point3 v2, hittable_list lst)
{
  minimum = v1;
  maximum = v2;
  lst = lst;
}
// origin = ray.origin
//         invD = 1 / ray.direction
//         tmin = ray.start
//         tmax = ray.end
//         lbound = (self.minimum - origin)*invD
//         rbound = (self.maximum - origin)*invD

//         for i in range(3):
//             t0 = min(lbound[i], rbound[i])
//             t1 = max(lbound[i], rbound[i])
//             tmin = max(t0, tmin)
//             tmax = min(t1, tmax)
//             if (tmax < tmin):
//                 return False
//         # print("ture")
//         return True
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