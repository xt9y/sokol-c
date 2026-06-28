#ifndef CAM_H
#define CAM_H

#include "level.h"

#ifndef SOKOL_APP_INCLUDED
#include "sokol/sokol_app.h"
#endif

typedef struct {
    vec3 pos;
    float yaw;
    float pitch;
} camera_t;

void camera_init(camera_t* cam, vec3 pos, float yaw);
void camera_update(camera_t* cam, float dt);
void camera_apply(const camera_t* cam);
void camera_event(const sapp_event* ev);

#endif
