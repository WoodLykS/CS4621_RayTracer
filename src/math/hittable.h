#ifndef HITTABLE_H
#define HITTABLE_H
#include <memory>
#include "ray.h"
//#include "../render/material.h"

class material;
struct hit_record
{
  point3 p;
  // normal unit vector to the surface;
  // we assume it points "out"
  vec3 normal;
  double t;
  double u, v;
  // if the ray and the normal face in the same direction,
  // the ray is inside the object; otherwise, outsside
  bool front_face;
  std::shared_ptr<material> mat_ptr;

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