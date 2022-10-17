#ifndef LAM_H
#define LAM_H
#include "material.h"
#include "../math/hittable.h"
#include "../math/util.h"
#include "../math/vec3.h"

class lambertian : public material
{
public:
  lambertian(color a) : albedo(a) {}

  bool scatter(ray &r_in, hit_record &rec, color &attenuation, ray &scattered) override
  {
    vec3 scatter_direction = rec.normal + random_in_unit_sphere();
    // avoid zero sum
    if (scatter_direction.near_zero())
      scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

public:
  color albedo;
};
using Material_L = shared_ptr<lambertian>;
#endif
