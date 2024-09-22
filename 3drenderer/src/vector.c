#include "vector.h"
#include "camera.h"

// TODO: implementation of transforms
vec2_t project(vec3_t point) {
  vec2_t projected_point = {
      .x = (FOV_FACTOR * point.x) / point.z,
      .y = (FOV_FACTOR * point.y) / point.z,
  };
  return projected_point;
}
