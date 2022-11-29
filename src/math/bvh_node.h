#ifndef BVH_NODE_H
#define BVH_NODE_H

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
}
#endif