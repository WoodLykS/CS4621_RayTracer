#include "hittable.h"
#include "hittablelist.h"
#include <cmath>
#include <memory>
#include <vector>

using namespace std;

hittable_list::hittable_list() {}
hittable_list::hittable_list(shared_ptr<hittable> object)
{
  add(object);
}
void hittable_list::clear()
{
  objects.clear();
}
void hittable_list::add(shared_ptr<hittable> object)
{
  objects.push_back(object);
}

bool hittable_list::hit(ray r, double t_min, double t_max, hit_record &rec)
{
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;

  for (int i = 0; i < objects.size(); i++)
  {
    shared_ptr<hittable> object = objects[i];
    if (object->hit(r, t_min, closest_so_far, temp_rec))
    {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}