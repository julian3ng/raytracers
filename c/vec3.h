#ifndef VEC3_H
#define VEC3_H

typedef union vec3 {
    struct {
        float x;
        float y;
        float z;
    };
    struct {
        float u;
        float v;
        float w;
    };
    struct {
        float r;
        float g;
        float b;
    };
    float elements[3];
} vec3;

vec3 Vec3(float x, float y, float z);
vec3 add_vec3(vec3 u, vec3 v);
vec3 sum_vec3(int n, ...);
vec3 sum_vec3f(vec3 u, int n, ...);
vec3 sub_vec3(vec3 u, vec3 v);
vec3 mul_vec3(vec3 u, vec3 v);
vec3 div_vec3(vec3 u, vec3 v);
vec3 add_vec3f(vec3 u, float f);
vec3 sub_vec3f(vec3 u, float f);
vec3 mul_vec3f(vec3 u, float f);
vec3 div_vec3f(vec3 u, float f);
float norm2_vec3(vec3 u);
float norm_vec3(vec3 u);
vec3 unit_vec3(vec3 u);
float dot_vec3(vec3 u, vec3 v);
vec3 cross_vec3(vec3 u, vec3 v);
void print_vec3i(vec3 u);
void print_vec3f(vec3 u);
vec3 lerp(vec3 u, float t, vec3 v);
#endif /* VEC3_H */
