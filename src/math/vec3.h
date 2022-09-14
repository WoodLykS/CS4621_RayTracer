#ifndef VEC3_H
#define VEC3_H
#include <iostream>
class vec3
{
private:
  double e[3];

public:
  vec3();
  vec3(double e0, double e1, double e2);
  // string toString();

  double x();
  double y();
  double z();

  vec3 operator-();
  // double operator[](int i) { return e[i]; }
  double &operator[](int i);

  // Overload operators for vec3 class

  /* Vector addition*/
  vec3 &operator+=(vec3 &v);

  /*Scalar multiplication*/
  vec3 &operator*=(double t);

  vec3 &operator/=(double t);

  double norm();

  void normalized();
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

std::ostream &operator<<(std::ostream &out, vec3 &v);
#endif