#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class material
{
public:
  bool diffuse = false;
  bool metal = false;
  // virtual bool scatter(ray &r_in, hit_record &rec,
  //                      vec3 &attenuation, ray &scattered) = 0;
};

struct hit_record
{
  point3 p;
  // normal unit vector to the surface;
  // we assume it points "out"
  vec3 normal;
  double t;
  // if the ray and the normal face in the same direction,
  // the ray is inside the object; otherwise, outsside
  bool front_face;

  inline void set_face_normal(ray r, vec3 outward_normal)
  {
    front_face = dot(r.velocity, outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable
{
public:
  virtual bool hit(ray r, double t_min, double t_max, hit_record &rec) = 0;
};
#endif