#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "../render/material.h"
#include "hittable.h"
#include "hittablelist.h"
#include "aabb.h"
#include "vec3.h"
#include <cmath>
#include <memory>
#include "aabb.h"
#include "ray.h"

class bvh_node
{
public:
  aabb bbox;
  bvh_node *right;
  bvh_node *left;
  bvh_node();
  bvh_node(aabb box, bvh_node r, bvh_node l);
  hit(ray r, hit_record &rec);
};

bvh_node ::bvh_node()
{
  bbox = aabb();
  right = NULL;
  left = NULL;
}
bvh_node ::bvh_node(aabb box, bvh_node r, bvh_node l)
{
  bbox = box;
  right = r;
  left = l;
}

bool bvh_node ::hit(ray r, hit_record rec)
{
  return false;
}
#endif