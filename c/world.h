#ifndef WORLD_H
#define WORLD_H
#include <stdbool.h>
#include "sphere.h"
#include "hit_record.h"

typedef enum OBJTYPE {SPHERE} OBJTYPE;

typedef union shape {
    sphere s;
} shape;

typedef struct hittable {
    OBJTYPE ot;
    shape obj;
} hittable;

typedef struct world {
    int num_objects;
    hittable *objects;
} world;

hit_record hit_world(world w, ray r, float t_min, float t_max);

#endif
