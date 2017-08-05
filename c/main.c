#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hit_record.h"

#include "world.h"

float rand_0_1(void) {
    return (float)rand() / (float)RAND_MAX;
}

vec3 random_in_unit_sphere(void) {
    vec3 p = {{1, 1, 1}};
    do {
        p = sub_vec3f(mul_vec3f(Vec3(rand_0_1(), rand_0_1(), rand_0_1()), 2), 1);
    } while (norm_vec3(p) >= 1);
    return p;
}

/*
  Shoot a ray at the world
  If it hits an object in the world, return the shading of that object
  Otherwise return the background color
 */
vec3 color(ray r, world w, int depth) {
    hit_record rec = hit_world(w, r, 0.001, FLT_MAX);
    if (rec.status) {
        vec3 target = sum_vec3(3, rec.p_hit, rec.normal, random_in_unit_sphere());
        vec3 rval = mul_vec3f(color(Ray(rec.p_hit, sub_vec3(target, rec.p_hit)),
                                    w, depth+1), 0.5);
        return rval;
    } else {
        // Calculate background color
        vec3 unit_dir = unit_vec3(r.dir);
        float t = .5*(unit_dir.y + 1.0);
        vec3 lerped = lerp(Vec3(1, 1, 1), t, Vec3(0, 0, 0));
        return lerped;
    }
}

int main(void) {
    srand(time(NULL));
    printf("P3\n");
    printf("200 100 255\n");
    int nx = 200;
    int ny = 100;
    int ns = 50;

    vec3 llc = Vec3(-2, -1, -1);
    vec3 horizontal = Vec3(4, 0, 0);
    vec3 vertical = Vec3(0, 2, 0);

    hittable hlist[2] = {{SPHERE, {Sphere(Vec3(0, 0, -1), 0.5)}},
                         {SPHERE, {Sphere(Vec3(0, -100.5, -1), 100)}}};
    world w = (world){1, hlist};

    for (int iy=ny-1; iy>=0; iy--) {
        for (int ix=0; ix<nx; ix++) {
            vec3 c = {{0, 0, 0}};
            for (int s=0; s<ns; s++) {
                float u = (float)(ix+rand_0_1())/nx;
                float v = (float)(iy+rand_0_1())/ny;
                ray r = Ray(Vec3(0, 0, 0), sum_vec3(3,
                                                    llc,
                                                    mul_vec3f(horizontal, u),
                                                    mul_vec3f(vertical, v)));
                c = add_vec3(c, color(r, w, 0));
            }
            c = div_vec3f(c, ns);
            print_vec3i(mul_vec3f(c, 255));
            printf(" ");
        }
        printf("\n");
    }
    return 0;
}
