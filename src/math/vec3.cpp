#include <iostream>
#include "vec3.h"
#include <cmath>

vec3::vec3()
{
  e[0] = 0;
  e[1] = 0;
  e[2] = 0;
}
vec3::vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

double vec3::x() { return e[0]; }
double vec3::y() { return e[1]; }
double vec3::z() { return e[2]; }

vec3 vec3::operator-() { return vec3(-e[0], -e[1], -e[2]); }
// double vec3::operator[](int i) {return e[i];}
double &vec3::operator[](int i) { return e[i]; }

vec3 &vec3::operator+=(vec3 &v)
{
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

vec3 &vec3::operator*=(double t)
{
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

vec3 &vec3::operator/=(double t)
{
  return *this *= 1 / t;
}

double vec3::norm()
{
  return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

void vec3::normalized()
{
  double n = norm();
  *this *= 1 / n;
}

std::ostream &operator<<(std::ostream &out, vec3 &v)
{
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}
// int main() { return 0; }