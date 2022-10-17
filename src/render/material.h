#ifndef MATERIAL_H
#define MATERIAL_H
#include <memory>
#include "../math/ray.h"

struct hit_record;
class material
{
public:
  bool diffuse = false;
  bool metal = false;
  virtual bool scatter(ray &r_in, hit_record &rec,
                       color &attenuation, ray &scattered) = 0;
};

#endif