#include <stdio.h>
#include <math.h>
#include "sphere.h"


sphere Sphere(vec3 center, float radius) {
    sphere rval = {center, radius};
    return rval;
}

hit_record hit_sphere(sphere s, ray r, float t_min, float t_max) {
    vec3 oc = sub_vec3(r.origin, s.center);
    float a = dot_vec3(r.dir, r.dir);
    float b = 2.0 * dot_vec3(oc, r.dir);
    float c = dot_vec3(oc, oc) - s.radius*s.radius;
    float discriminant = b*b - 4*a*c;
    hit_record rval = (hit_record){false, 0, Vec3(-1, -1, -1), Vec3(1, 0, 0)};
    if (discriminant < 0) {
        rval = (hit_record){false, 0, Vec3(-1, -1, -1), Vec3(1, 0, 0)};
        return rval;
    } else {
        float temp = (-b - sqrt(discriminant))/(2*a);
        if (temp > t_min && temp < t_max) {
            rval.t_hit = temp;
            rval.p_hit = point_at_t(r, rval.t_hit);
            rval.normal = div_vec3f(sub_vec3(rval.p_hit, s.center), s.radius);
            return rval;
        } 
        temp = (-b + sqrt(discriminant))/(2*a);
        if (temp > t_min && temp < t_max) {
            rval.t_hit = temp;
            rval.p_hit = point_at_t(r, rval.t_hit);
            rval.normal = div_vec3f(sub_vec3(rval.p_hit, s.center), s.radius);
            return rval;
        }
    }
    return rval;
}
