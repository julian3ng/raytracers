#include "ray.h"
#include <stdio.h>
int main() {
    ray r = Ray(Vec3(0, 0, 0), Vec3(1, 0, 0));
    print_ray(r);
    printf("\n");
    print_vec3f(point_at_t(r, 10));
}
