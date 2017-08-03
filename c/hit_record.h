#ifndef HIT_RECORD_H
#define HIT_RECORD_H
#include "vec3.h"
#include <stdbool.h>

typedef struct hit_record {
    bool status;
    float t_hit;
    vec3 p_hit;
    vec3 normal;
} hit_record;

#endif /* HIT_RECORD_H */
