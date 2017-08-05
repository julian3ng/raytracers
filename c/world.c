#include "world.h"

hit_record hit_world(world w, ray r, float t_min, float t_max) {
    hit_record temp;
    hit_record rval = (hit_record){false, 0.0, Vec3(-1, -1, -1), Vec3(-1, -1, -1)};
    double cur_closest = t_max;
    for (int i=0; i<w.num_objects; i++) {
        switch (w.objects[i].ot) {
        case SPHERE:
            temp = hit_sphere(w.objects[i].obj.s, r, t_min, cur_closest);
            if (temp.status) {
                cur_closest = temp.t_hit;
                rval = temp;
            }
            break;
        default:
            break;
        }
    }
    return rval;
}
