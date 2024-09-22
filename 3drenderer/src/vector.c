#include "vector.h"
#include "camera.h"

// TODO: implementation of transforms
vec2_t project(vec3_t point) {
  vec2_t projected_point = {
      .x = (FOV_FACTOR * point.x),
      .y = (FOV_FACTOR * point.y),
  };
  return projected_point;
}
