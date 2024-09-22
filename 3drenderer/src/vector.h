#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} vec2_t;

typedef struct {
  float x;
  float y;
  float z;
} vec3_t;

// TODO: declarations of transforms

vec2_t project(vec3_t point);

#endif
