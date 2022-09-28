// this file includes both general util and color util

#ifndef RAY_TRACER_UTIL_H
#define RAY_TRACER_UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include <iostream>
#include "ray.h"
#include "vec3.h"

/*
using std::shared_ptr;
using std::make_shared;
using std::sqrt;
*/
using namespace std;

const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
  return degrees * pi / 180.0;
}

// this helper map a decimal to rgb value
void write_color(ostream &out, color pixel_color)
{
  //cout<<pixel_color.x();
  out << static_cast<int>(255.99 * pixel_color.x()) << ' '
      << static_cast<int>(255.99 * pixel_color.y()) << ' '
      << static_cast<int>(255.99 * pixel_color.z()) << '\n';
}

#endif