#include "level.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gl.h"

void level_render(const level_data_t* level)
{
    for (int i = 0; i < level->quad_count; i++)
    {
        const level_quad_t* q = &level->quads[i];
        sgl_push_matrix();
        sgl_translate(q->pos.x, q->pos.y, q->pos.z);
        sgl_rotate(q->rot.x, 1.0f, 0.0f, 0.0f);
        sgl_rotate(q->rot.y, 0.0f, 1.0f, 0.0f);
        sgl_rotate(q->rot.z, 0.0f, 0.0f, 1.0f);

        float hw = q->size.x * 0.5f, hh = q->size.y * 0.5f;
        sgl_c3f(q->color.x, q->color.y, q->color.z);
        sgl_begin_quads();
        sgl_v3f(-hw, -hh, 0.0f);
        sgl_v3f( hw, -hh, 0.0f);
        sgl_v3f( hw,  hh, 0.0f);
        sgl_v3f(-hw,  hh, 0.0f);
        sgl_end();

        sgl_pop_matrix();
    }
}
