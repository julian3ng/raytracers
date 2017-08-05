#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include "vec3.h"

vec3 Vec3(float x, float y, float z) {
    vec3 rval = {{x, y, z}};
    return rval;
}

vec3 add_vec3(vec3 u, vec3 v) {
    vec3 rval = {{u.x+v.x, u.y+v.y, u.z+v.z}};
    return rval;
}

vec3 sum_vec3(int n, ...) {
    va_list valist;
    vec3 rval = {{0, 0, 0}};
    
    va_start(valist, n);
    for (int i=0; i<n; i++)
        rval = add_vec3(rval, va_arg(valist, vec3));
    va_end(valist);

    return rval;
}
vec3 sum_vec3f(vec3 u, int n,...) {
    va_list valist;
    vec3 rval = {{u.x, u.y, u.z}};
    
    va_start(valist, n);
    for (int i=0; i<n; i++)
        rval = add_vec3f(rval, (float)va_arg(valist, double));
    va_end(valist);

    return rval;
}

vec3 sub_vec3(vec3 u, vec3 v) {
    vec3 rval = {{u.x-v.x, u.y-v.y, u.z-v.z}};
    return rval;
}

vec3 mul_vec3(vec3 u, vec3 v) {
    vec3 rval = {{u.x*v.x, u.y*v.y, u.z*v.z}};
    return rval;
}

vec3 div_vec3(vec3 u, vec3 v) {
    vec3 rval = {{u.x/v.x, u.y/v.y, u.z/v.z}};
    return rval;
}

vec3 add_vec3f(vec3 u, float f) {
    vec3 rval = {{u.x+f, u.y+f, u.z+f}};
    return rval;
}


vec3 sub_vec3f(vec3 u, float f) {
    vec3 rval = {{u.x-f, u.y-f, u.z-f}};
    return rval;
}

vec3 mul_vec3f(vec3 u, float f) {
    vec3 rval = {{u.x*f, u.y*f, u.z*f}};
    return rval;
}

vec3 div_vec3f(vec3 u, float f) {
    vec3 rval = {{u.x/f, u.y/f, u.z/f}};
    return rval;
}

float norm2_vec3(vec3 u) {
    return u.x*u.x + u.y*u.y + u.z*u.z;
}

float norm_vec3(vec3 u) {
    return sqrt(norm2_vec3(u));
}

vec3 unit_vec3(vec3 u) {
    float l = norm_vec3(u);
    vec3 rval = {{u.x/l, u.y/l, u.z/l}};
    return rval;
}

float dot_vec3(vec3 u, vec3 v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

vec3 cross_vec3(vec3 u, vec3 v) {
    float d1 = u.y*v.z - u.z*v.y;
    float d2 = u.x*v.z - u.z*v.x;
    float d3 = u.x*v.y - u.y*v.z;
    vec3 rval = {{d1, -d2, d3}};
    return rval;
}

void print_vec3i(vec3 u) {
    for (int i=0; i<3; i++)
        printf("%d ", (int)u.elements[i]);
}

void print_vec3f(vec3 u) {
    for (int i=0; i<3; i++)
        printf("%f ", u.elements[i]);
}

float clamp(float a, float t, float b) {
    if (t < a) return a;
    if (t > b) return b;
    return t;
}

vec3 lerp(vec3 u, float t, vec3 v) {
    float clamped_t = clamp(0, t, 1);
    vec3 rval = add_vec3(mul_vec3f(u, 1-clamped_t), mul_vec3f(v, clamped_t));
    return rval;
}
