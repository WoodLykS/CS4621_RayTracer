#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "../render/material.h"
#include "hittable.h"
#include "hittablelist.h"
#include "aabb.h"
#include "vec3.h"
#include <cmath>
#include <memory>
#include "ray.h"

class bvh_node : public hittable
{
public:
  shared_ptr<bvh_node> left;
  shared_ptr<bvh_node> right;
  aabb bbox;
  bvh_node();
  bvh_node(std::vector<shared_ptr<aabb>> &src_bboxes, size_t start, size_t end, int idx);
  virtual bool hit(ray r, double t_min, double t_max, hit_record &rec) override;
  virtual bool bounding_box(double t_min, double t_max, aabb &output_box) override;
};

bool bvh_node::bounding_box(double t_min, double t_max, aabb &output_box)
{
  output_box = bbox;
  return true;
}

bool bvh_node::hit(ray r, double t_min, double t_max, hit_record &rec)
{
  if (!bbox.hit(r, t_min, t_max))
  {
    return false;
  }
  bool lhit = left->hit(r, t_min, t_max, rec);
  bool rhit = right->hit(r, t_min, t_max, rec);
  return lhit || rhit;
}

bvh_node ::bvh_node()
{
  bbox = aabb();
  left = make_shared<bvh_node>();
  right = make_shared<bvh_node>();
}
bool bbox_helper(aabb &bbox1, aabb &bbox2, aabb &bbox3)
{
  point3 v1 = vec3(std::min(bbox1.minimum.x(), bbox2.minimum.x()), std::min(bbox1.minimum.y(), bbox2.minimum.y()), std::min(bbox1.minimum.z(), bbox2.minimum.z()));
  point3 v2 = vec3(std::max(bbox1.maximum.x(), bbox2.maximum.x()), std::max(bbox1.maximum.y(), bbox2.maximum.y()), std::max(bbox1.maximum.z(), bbox2.maximum.z()));

  bbox3 = aabb(v1, v2);
  return true;
}

bool newcompare(shared_ptr<aabb> &a, shared_ptr<aabb> &b, int idx)
{
  return (a->minimum[idx] < b->minimum[idx]);
}

bool xcomp(shared_ptr<aabb> &a, shared_ptr<aabb> &b)
{
  newcompare(a, b, 0);
}
bool ycomp(shared_ptr<aabb> &a, shared_ptr<aabb> &b)
{
  newcompare(a, b, 1);
}
bool zcomp(shared_ptr<aabb> &a, shared_ptr<aabb> &b)
{
  newcompare(a, b, 2);
}

bvh_node::bvh_node(std::vector<shared_ptr<aabb>> &src_bboxes, size_t start, size_t end, int idx)
{
  std::vector<shared_ptr<aabb>> &lst = src_bboxes;
  int lstsize = end - start;
  if (lstsize == 0)
  {
    bvh_node();
  }
  else if (lstsize == 1)
  {
    bbox = *lst[start];
    left = make_shared<bvh_node>();
    right = make_shared<bvh_node>();
  }
  else if (lstsize == 2)
  {
    bbox = aabb();
    bbox_helper(*lst[start], *lst[start + 1], bbox);
    left = make_shared<bvh_node>(lst, 1, 2, 0);
    right = make_shared<bvh_node>();
  }
  else
  {
    size_t mid = (start + end) / 2;
    bbox = aabb();
    if (idx == 0)
    {
      sort(lst.begin() + start, lst.begin() + end, xcomp);
    }
    else if (idx == 1)
    {
      sort(lst.begin() + start, lst.begin() + end, ycomp);
    }
    else if (idx == 2)
    {
      sort(lst.begin() + start, lst.begin() + end, zcomp);
    }
    left = make_shared<bvh_node>(lst, start, mid, ((idx + 1) % 3));
    right = make_shared<bvh_node>(lst, mid + 1, end, ((idx + 1) % 3));
    bbox_helper(left->bbox, right->bbox, bbox);
  }
}
// // bool bvh_node ::hit(ray r, float t_min, float t_max)
// // {
// //   if (not bbox.hit(r, t_min, t_max))
// //   {
// //     return false;
// //   }

// //   bool rb = right->bbox.hit(r, t_min, t_max);
// //   bool lb = left->bbox.hit(r, t_min, t_max);
// //   return rb || lb;
// // }

#endif