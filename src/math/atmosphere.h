#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class atmosphere : public hittable
{
public:
  //settings
  int inScatteringPoints = 10;
  //optical depth is the density of the atmosphere,
  //it determines how much or how likely the light is bouced off the "ray"
  //higher optical depth, lower transmittance, transmisttance = e^-depth
  //again we use 10 samples points, which shoudl be good enough for a large scale picture
  int opticalDepthPoints = 10;
  //parameter that controls how quickly the atmosphere density changes
  double densityFalloff = 4;
  double atomsphreScale = 1; //depth of the atmosphere
  vec3 wavelengths = vec3(700, 530, 440);
  double scatteringStrength = 1;
  //hittable usuals
  std::shared_ptr<hittable> planet;
  point3 center;
  double radius;
  double planetRadius;

  atmosphere();
  atmosphere(std::shared_ptr<hittable> planet, point3 center, double radius);
  virtual bool hit(ray r, double t_min, double t_max, hit_record &rec) override;
  virtual bool bounding_box(aabb &output_box) override;
  // dist should return (dist1, dist2, _)
  // dist1 is the distance between the hit point of the ray on the atmosphere
  // dist2 is the distance between the hit point of the ray on either the planet
  // of the other side of the sphere.
  // what if the ray starts inside the atmosphere
  // the distance should be used to determine the intensity of in-scattering light
  // as different lights have different wavelength, the intensity of different
  // light received shoudl be differen
  vec3 dist(ray r, double t_min, double t_max, hit_record &rec);

  // for the calculation of light, we need a couple of helper functions
  // 1. how much light get to the in scattering point (This times the transmittance)
  // 2. at the in sacttering point, how much of it will go in the desired direction
  // the peanut function with angles
  // 3. again, on its way to human eye, it can also be bounced off to somewhere else
  // use for loop to calculate the sum of the light at each in scattering point

  double densityAtPoint(vec3 densitySamplePoint);
  double opticalDepth(ray r, double ray_length);
  double calculateLight(ray r, double t_min, double t_max, hit_record &rec);
};

// first helper, point density, exponentially thiner air as you go up

double atmosphere::densityAtPoint(vec3 densitySamplePoint)
{
  double heightAboveSurface = (densitySamplePoint - center).norm() - planetRadius;
  double height01 = heightAboveSurface / (radius - planetRadius);
  double localDensity = exp(-height01 * densityFalloff) * (1 - height01);
  return localDensity;
}

// second helper, calculate the accumulated density along a ray/path
double atmosphere::opticalDepth(ray r, double ray_length)
{
  //this ray is the ray that is coming into the in sacttering point
  //I think it is a valid assumption to say that the sun is super super far
  //away, the ray start from the top surface of the atmosphere
  vec3 densitySamplePoint = r.origin;
  double stepSize = ray_length / (opticalDepthPoints - 1);
  double opticalDepth = 0;
  for (int i = 0; i < opticalDepthPoints; i++)
  {
    double localDensity = densityAtPoint(densitySamplePoint);
    opticalDepth += localDensity * stepSize;
    densitySamplePoint += r.velocity * stepSize;
  }
  return opticalDepth;
}

#endif