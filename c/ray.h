#ifndef RAY_H
#define RAY_H
#include "vec3.h"

typedef struct ray {
    vec3 origin;
    vec3 dir;
} ray;

ray Ray(vec3 origin, vec3 dir);
vec3 point_at_t(ray r, float t);
void print_ray(ray r);

#endif /* RAY_H */
