#include "sokol.h"
#include "level.h"
#include "cam.h"

#include "1.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVELS 16

static level_data_t g_levels[MAX_LEVELS] = {0};
static unsigned int g_current_level = 0;
static camera_t g_cam;
static sg_pass_action g_pass_action;

static void frame(void)
{
    float dt = sapp_frame_duration();
    camera_update(&g_cam, dt);

    sg_begin_pass(&(sg_pass){
        .action = g_pass_action,
        .swapchain = sglue_swapchain()
    });

    camera_apply(&g_cam);
    level_render(&g_levels[0]);
    sgl_draw();

    sg_end_pass();
    sg_commit();
}

static void init(void)
{
    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func
    });
    if (!sg_isvalid()) {
        fprintf(stderr, "Failed to create Sokol GFX context!\n");
        exit(-1);
    }

    sgl_setup(&(sgl_desc_t){ .logger.func = slog_func });
    if (!sg_isvalid()) {
        fprintf(stderr, "Failed to create Sokol GL context!\n");
        exit(-1);
    }

    g_pass_action = (sg_pass_action){
        .colors[0] = { .load_action = SG_LOADACTION_CLEAR, .clear_value = { 0.1f, 0.1f, 0.1f, 1.0f } }
    };

    g_levels[g_current_level] = load_1(); g_current_level++;

    camera_init(&g_cam, (vec3){ 0.0f, 0.0f, 5.0f }, 0.0f);
}

static void cleanup(void)
{
    sgl_shutdown();
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[])
{
    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb = init, .frame_cb = frame, .cleanup_cb = cleanup, .event_cb = camera_event, .window_title = "demo", .logger.func = slog_func,
    };
}
