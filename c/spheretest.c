#include <stdio.h>
#include "sphere.h"
#include "ray.h"
int main() {
    sphere s = Sphere(Vec3(0, 0, -2), 1);
    ray r = Ray(Vec3(0, 0, 0), Vec3(0, .5, -1));

    hit_record rec = hit(s, r, 0, 10);

    printf("SPHERE\n");
    print_vec3f(s.center);
    printf(" %f\n", s.radius);
    printf("RAY\n");
    print_ray(r);
    printf("\n");
    printf("REC\n");
    printf(rec.status ? "true\n" : "false\n");
    printf("%f\n", rec.t_hit);
    print_vec3f(rec.p_hit);
    printf("\n");
    print_vec3f(rec.normal);
    return 0;
}
