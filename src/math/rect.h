#ifndef AARECT_H
#define AARECT_H
#include "util.h"
#include "hittable.h"

class xy_rect : public hittable
{
public:
  xy_rect() {}

  xy_rect(
      double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<material> mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat){};

  virtual bool hit(ray r, double t_min, double t_max, hit_record &rec) override;

public:
  shared_ptr<material> mp;
  double x0, x1, y0, y1, k;
};

class xz_rect : public hittable
{
public:
  xz_rect() {}

  xz_rect(
      double _x0, double _x1, double _z0, double _z1, double _k, shared_ptr<material> mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat){};

  virtual bool hit(ray r, double t_min, double t_max, hit_record &rec) override;

public:
  shared_ptr<material> mp;
  double x0, x1, z0, z1, k;
};

class yz_rect : public hittable
{
public:
  yz_rect() {}

  yz_rect(
      double _y0, double _y1, double _z0, double _z1, double _k, shared_ptr<material> mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat){};

  virtual bool hit(ray r, double t_min, double t_max, hit_record &rec) override;

public:
  shared_ptr<material> mp;
  double y0, y1, z0, z1, k;
};

bool xy_rect::hit(ray r, double t_min, double t_max, hit_record &rec)
{
  auto t = (k - r.origin.z()) / r.velocity.z();
  if (t < t_min || t > t_max)
    return false;

  auto x = r.origin.x() + t * r.velocity.x();
  auto y = r.origin.y() + t * r.velocity.y();
  if (x < x0 || x > x1 || y < y0 || y > y1)
    return false;

  rec.u = (x - x0) / (x1 - x0);
  rec.v = (y - y0) / (y1 - y0);
  rec.t = t;
  auto outward_normal = vec3(0, 0, 1);
  rec.set_face_normal(r, outward_normal);
  rec.mat_ptr = mp;
  rec.p = r.point_at_time(t);

  return true;
}

bool xz_rect::hit(ray r, double t_min, double t_max, hit_record &rec)
{
  auto t = (k - r.origin.y()) / r.velocity.y();
  if (t < t_min || t > t_max)
    return false;

  auto x = r.origin.x() + t * r.velocity.x();
  auto z = r.origin.z() + t * r.velocity.z();
  if (x < x0 || x > x1 || z < z0 || z > z1)
    return false;

  rec.u = (x - x0) / (x1 - x0);
  rec.v = (z - z0) / (z1 - z0);
  rec.t = t;
  auto outward_normal = vec3(0, 1, 0);
  rec.set_face_normal(r, outward_normal);
  rec.mat_ptr = mp;
  rec.p = r.point_at_time(t);

  return true;
}

bool yz_rect::hit(ray r, double t_min, double t_max, hit_record &rec)
{
  auto t = (k - r.origin.x()) / r.velocity.x();
  if (t < t_min || t > t_max)
    return false;

  auto y = r.origin.y() + t * r.velocity.y();
  auto z = r.origin.z() + t * r.velocity.z();
  if (y < y0 || y > y1 || z < z0 || z > z1)
    return false;

  rec.u = (y - y0) / (y1 - y0);
  rec.v = (z - z0) / (z1 - z0);
  rec.t = t;
  auto outward_normal = vec3(1, 0, 0);
  rec.set_face_normal(r, outward_normal);
  rec.mat_ptr = mp;
  rec.p = r.point_at_time(t);

  return true;
}

#endif