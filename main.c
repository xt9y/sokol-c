#if defined(__APPLE__)
    #define SOKOL_METAL
#elif defined(_WIN32)
    #define SOKOL_D3D11
#else
    #define SOKOL_GLCORE
#endif
#define SOKOL_IMPL
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gp.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_log.h"

#include <stdio.h>          // for fprintf()
#include <stdlib.h>         // for exit()
#include <math.h>           // for sinf() and cosf()

static void frame(void) 
{
    int w = sapp_width(), h = sapp_height();
    float ratio = (float)w/(float)h;
    
    float time = sapp_frame_count() * sapp_frame_duration();
    float r = sinf(time)*0.5+0.5, 
          g = cosf(time)*0.5+0.5;

    sgp_begin(w, h);

    sgp_viewport(0, 0, w, h); sgp_project(-ratio, ratio, 1.0f, -1.0f);
    sgp_set_color(0.1f, 0.1f, 0.1f, 1.0f); sgp_clear(); 
    sgp_reset_color();

    sgp_rotate_at(time, 0.0f, 0.0f); 
    sgp_set_color(r, g, 1.0f, 1.0f); sgp_draw_filled_rect(-0.5f, -0.5f, 1.0f, 1.0f); 

    sg_pass pass = {.swapchain = sglue_swapchain()};
    sg_begin_pass(&pass);
    sgp_flush();
    sgp_end();
    sg_end_pass();
    sg_commit();
}

static void init(void) 
{
    sg_desc sgdesc = {
        .environment = sglue_environment(),
        .logger.func = slog_func
    };
    sg_setup(&sgdesc);
    if (!sg_isvalid()) {
        fprintf(stderr, "Failed to create Sokol GFX context!\n");
        exit(-1);
    }

    sgp_desc sgpdesc = {0};
    sgp_setup(&sgpdesc);
    if (!sgp_is_valid()) {
        fprintf(stderr, "Failed to create Sokol GP context: %s\n", sgp_get_error_message(sgp_get_last_error()));
        exit(-1);
    }
}

static void cleanup(void) 
{
    sgp_shutdown();
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) 
{
    (void)argc; (void)argv;
    return (sapp_desc) {
        .init_cb = init, .frame_cb = frame, .cleanup_cb = cleanup, .window_title = "Sokol GP", .logger.func = slog_func,
    };
}
