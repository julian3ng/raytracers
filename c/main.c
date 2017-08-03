#include <stdio.h>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hit_record.h"
#include <float.h>

vec3 color(ray r, sphere s) {
    hit_record rec = hit(s, r, 0.0, FLT_MAX);
    if (rec.status == true) {
        return mul_vec3f(add_vec3f(rec.normal, 1), .5);
    } else {
        return Vec3(0, 0, 0);
        vec3 unit_dir = unit_vec3(r.dir);
        float t = .5*(unit_dir.y + 1.0);
        return lerp(Vec3(1, 1, 1), t, Vec3(0, 0, 0));
    }
}

int main(void) {
    printf("P3\n");
    printf("200 100 255\n");
    int nx = 200;
    int ny = 100;

    vec3 llc = Vec3(-2, -1, -1);
    vec3 horizontal = Vec3(4, 0, 0);
    vec3 vertical = Vec3(0, 2, 0);

    sphere s = Sphere(Vec3(0, 0, -1), .5);

    for (int iy=ny-1; iy>=0; iy--) {
        for (int ix=0; ix<nx; ix++) {
            float u = (float)ix/nx;
            float v = (float)iy/ny;
            ray r = Ray(Vec3(0, 0, 0), sum_vec3(3,
                                                llc,
                                                mul_vec3f(horizontal, u),
                                                mul_vec3f(vertical, v)));
            vec3 c = color(r, s);
            print_vec3i(mul_vec3f(c, 255));
            printf(" ");
        }
        printf("\n");
    }
    return 0;
}
