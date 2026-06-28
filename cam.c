#include "cam.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gl.h"
#include <math.h>

#define CAM_SPEED 8.0f
#define MOUSE_SENS 0.004f

static bool g_keys[512] = {false};
static float g_mx = 0, g_my = 0;
static bool g_locked = false;

void camera_event(const sapp_event* ev)
{
    switch (ev->type) {
    case SAPP_EVENTTYPE_KEY_DOWN:
        if ((size_t)ev->key_code < 512) g_keys[ev->key_code] = true;
        if (ev->key_code == SAPP_KEYCODE_ESCAPE && g_locked) {
            sapp_lock_mouse(false);
            g_locked = false;
        }
        break;
    case SAPP_EVENTTYPE_KEY_UP:
        if ((size_t)ev->key_code < 512) g_keys[ev->key_code] = false;
        break;
    case SAPP_EVENTTYPE_MOUSE_DOWN:
        if (ev->mouse_button == SAPP_MOUSEBUTTON_LEFT) {
            sapp_lock_mouse(true);
            g_locked = true;
        }
        break;
    case SAPP_EVENTTYPE_MOUSE_MOVE:
        if (g_locked) { g_mx += ev->mouse_dx; g_my += ev->mouse_dy; }
        break;
    default:
        break;
    }
}

void camera_init(camera_t* cam, vec3 pos, float yaw)
{
    cam->pos = pos;
    cam->yaw = yaw;
    cam->pitch = 0.0f;
}

void camera_update(camera_t* cam, float dt)
{
    if (g_locked) {
        cam->yaw   += g_mx * MOUSE_SENS;
        cam->pitch -= g_my * MOUSE_SENS;
        if (cam->pitch > 1.5f)  cam->pitch = 1.5f;
        if (cam->pitch < -1.5f) cam->pitch = -1.5f;
    }
    g_mx = 0.0f;
    g_my = 0.0f;

    float fx = cosf(cam->yaw) * cosf(cam->pitch);
    float fy = sinf(cam->pitch);
    float fz = sinf(cam->yaw) * cosf(cam->pitch);
    float rx = -sinf(cam->yaw);
    float rz =  cosf(cam->yaw);

    float mx = 0.0f, my = 0.0f, mz = 0.0f;
    if (g_keys[SAPP_KEYCODE_W]) { mx += fx; my += fy; mz += fz; }
    if (g_keys[SAPP_KEYCODE_S]) { mx -= fx; my -= fy; mz -= fz; }
    if (g_keys[SAPP_KEYCODE_A]) { mx -= rx;           mz -= rz; }
    if (g_keys[SAPP_KEYCODE_D]) { mx += rx;           mz += rz; }

    float len = sqrtf(mx*mx + my*my + mz*mz);
    if (len > 0.001f) {
        mx /= len; my /= len; mz /= len;
        cam->pos.x += mx * CAM_SPEED * dt;
        cam->pos.y += my * CAM_SPEED * dt;
        cam->pos.z += mz * CAM_SPEED * dt;
    }
}

void camera_apply(const camera_t* cam)
{
    int w = sapp_width(), h = sapp_height();
    float aspect = (float)w / (float)h;

    sgl_matrix_mode_projection();
    sgl_load_identity();
    sgl_perspective(sgl_rad(60.0f), aspect, 0.1f, 100.0f);

    sgl_matrix_mode_modelview();
    sgl_load_identity();

    float cx = cam->pos.x + cosf(cam->yaw) * cosf(cam->pitch);
    float cy = cam->pos.y + sinf(cam->pitch);
    float cz = cam->pos.z + sinf(cam->yaw) * cosf(cam->pitch);

    sgl_lookat(
        cam->pos.x, cam->pos.y, cam->pos.z,
        cx, cy, cz,
        0.0f, 1.0f, 0.0f
    );
}
