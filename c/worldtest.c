#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "vec3.h"
#include "hit_record.h"
#include "ray.h"
#include "sphere.h"
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

vec3 color(ray r, world w, int depth) {
    hit_record rec = hit_world(w, r, 0.001, FLT_MAX);
    printf(rec.status ? "true\n" : "false\n");
    fprintf(stderr, "%f\n", rec.t_hit);
    fprintf(stderr, "%f %f %f\n", rec.p_hit.x, rec.p_hit.y, rec.p_hit.z);
    fprintf(stderr, "%f %f %f\n", rec.normal.x, rec.normal.y, rec.normal.z);
    if (rec.status) {
        fprintf(stderr, "HIT");
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

int main() {
    hittable hlist[2] = {{SPHERE, {Sphere(Vec3(0, 0, -1), 0.5)}}};
    world w = (world){1, hlist};
    ray r = Ray(Vec3(0, 0, 0), Vec3(0, 0, -.5));
    print_vec3f(color(r, w, 0));
}
