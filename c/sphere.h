#ifndef SPHERE_H
#define SPHERE_H
#include "vec3.h"
#include "ray.h"
#include "hit_record.h"


typedef struct sphere {
    vec3 center;
    float radius;
} sphere;

sphere Sphere(vec3 center, float radius);
hit_record hit(sphere s, ray r, float t_min, float t_max);

#endif /* SPHERE_H */
