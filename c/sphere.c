#include <stdio.h>
#include <math.h>
#include "sphere.h"

sphere Sphere(vec3 center, float radius) {
    sphere rval = {center, radius};
    return rval;
}

hit_record hit(sphere s, ray r, float t_min, float t_max) {
    vec3 oc = sub_vec3(r.origin, s.center);
    float a = dot_vec3(r.dir, r.dir);
    float b = 2.0 * dot_vec3(oc, r.dir);
    float c = dot_vec3(oc, oc) - s.radius*s.radius;
    float discriminant = b*b - 4*a*c;
    bool status;
    float t_hit;
    vec3 p_hit;
    vec3 normal;
    if (discriminant < 0) {
        status = false;
        t_hit = 0;
        p_hit = Vec3(-1, -1, -1);
        normal = Vec3(-1, -1, -1);
        hit_record rval = {status, t_hit, p_hit, normal};
        return rval;
    } else {
        float temp = (-b - sqrt(discriminant))/(2*a);
        if (temp > t_min && temp < t_max) {
            status = true;
            t_hit = temp;
            p_hit = point_at_t(r, t_hit);
            normal = div_vec3f(sub_vec3(p_hit, s.center), s.radius);
            hit_record rval = {status, t_hit, p_hit, normal};
            return rval;
        } 
        temp = (-b + sqrt(discriminant))/(2*a);
        if (temp > t_min && temp < t_max) {
            status = true;
            t_hit = temp;
            p_hit = point_at_t(r, t_hit);
            normal = div_vec3f(sub_vec3(p_hit, s.center), s.radius);
            hit_record rval = {status, t_hit, p_hit, normal};
            return rval;
        }
    }
    hit_record rval = {false, 0, Vec3(-1, -1, -1), Vec3(-1, -1, -1)};
    return rval;
}
