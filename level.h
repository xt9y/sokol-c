#ifndef LEVEL_H
#define LEVEL_H

typedef struct {
    float x, y, z;
} vec3;

typedef struct {
    float x, y;
} vec2;

typedef struct {
    vec3 pos;   
    vec3 rot;   
    vec3 color; 
    vec2 size;  
} level_quad_t;

typedef struct {
    const char* name;
    level_quad_t* quads;
    int quad_count;
} level_data_t;

void level_render(const level_data_t* level);

#endif
