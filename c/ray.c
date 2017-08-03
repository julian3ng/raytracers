#include <stdio.h>
#include "ray.h"

ray Ray(vec3 origin, vec3 dir) {
    ray rval = {origin, dir};
    return rval;
}

vec3 point_at_t(ray r, float t) {
    return add_vec3(r.origin, mul_vec3f(r.dir, t));
}

void print_ray(ray r) {
    printf("<");
    print_vec3f(r.origin);
    printf(", ");
    print_vec3f(r.dir);
    printf(">");
}


