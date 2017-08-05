#include <stdio.h>
#include "vec3.h"


int main() {
    vec3 v = Vec3(1, 2, 3);
    vec3 w = Vec3(0, 0, 1);
    print_vec3f(v);
    printf("\n");
    print_vec3f(w);
    printf("\n");
    print_vec3f(add_vec3(v, w));
    printf("\n");
    print_vec3f(sub_vec3(v, w));
    printf("\n");
    print_vec3f(mul_vec3(v, w));
    printf("\n");
    print_vec3f(div_vec3(v, w));
    printf("\n");
    print_vec3f(add_vec3f(v, 1));
    printf("\n");
    print_vec3f(sub_vec3f(v, 1));
    printf("\n");
    print_vec3f(mul_vec3f(v, 2));
    printf("\n");
    print_vec3f(div_vec3f(v, 2));
    printf("\n");
    printf("%f\n", norm2_vec3(v));
    printf("%f\n", norm_vec3(v));
    print_vec3f(unit_vec3(v));
    printf("\n");
    printf("Unit vectors: ");
    v = Vec3(1, 0, 0);
    w = Vec3(0, 1, 0);
    print_vec3f(v);
    print_vec3f(w);
    printf("\n");
    print_vec3f(cross_vec3(v, w));
    printf("\n");
    print_vec3f(lerp(v, 0.5, w));
    printf("LERP TEST\n");
    for (int i=0; i<100; i++) {
        print_vec3f(lerp(Vec3(0, 0, 0), (float)i/100, Vec3(1, 1, 1)));
        printf("\n");
    }
    return 0;
}
