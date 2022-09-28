#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include <cmath>

class sphere : public hittable
{
public:
  point3 center;
  double radius;

  sphere();
  sphere(point3 center, double rad);
  virtual bool hit(ray r, double t_min, double t_max, hit_record &rec) override;
};

#endif