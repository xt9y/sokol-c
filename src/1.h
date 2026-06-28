#pragma once
#include "level.h"

static const level_quad_t g_level1_quads[] = {
    { .pos = { 3.0f, 0.0f, 5.0f }, .rot = { 0.0f, 90.0f, 0.0f }, .color = { 1.0f, 0.0f, 0.0f }, .size = { 2.0f, 2.0f } },
};

static level_data_t load_1(void)
{
    return (level_data_t){
        .name = "Level 1",
        .quads = (level_quad_t*)g_level1_quads,
        .quad_count = sizeof(g_level1_quads) / sizeof(g_level1_quads[0]),
    };
}
