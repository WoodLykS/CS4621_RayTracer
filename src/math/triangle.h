#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../render/material.h"
#include "hittable.h"
#include "hittablelist.h"
#include "aabb.h"
#include "vec3.h"
#include <cmath>
#include <memory>

class triangle : public hittable
{
public:
  point3 v1;
  point3 v2;
  point3 v3;
  shared_ptr<material> mat_ptr;
  triangle();
  triangle(point3 v1, point3 v2, point3 v3, shared_ptr<material> m);
};

triangle::triangle()
{
  v1 = vec3();
  v2 = vec3();
  v3 = vec3();
}

triangle::triangle(point3 v1, point3 v2, point3 v3, shared_ptr<material> m)
{
  v1 = v1;
  v2 = v2;
  v3 = v3;
  mat_ptr = m;
}

//matrix opperation for determinants/... more work here
// bool triangle::hit(ray r, doubl)
#endif