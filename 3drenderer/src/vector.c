#include "vector.h"
#include "camera.h"
#include <math.h>

vec2_t project(vec3_t point) {
  vec2_t projected_point = {
      .x = (FOV_FACTOR * point.x) / point.z,
      .y = (FOV_FACTOR * point.y) / point.z,
  };
  return projected_point;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
  vec3_t rotated_vector = {
      .x = v.x * cos(angle) - v.z * sin(angle), // sin (a+b)
      .y = v.y,
      .z = v.x * sin(angle) + v.z * cos(angle), // cos (a+b)
  };

  return rotated_vector;
}

vec3_t vec3_rotate_x(vec3_t v, float angle) {
  vec3_t rotated_vector = {
      .x = v.x,
      .y = v.y * cos(angle) - v.z * sin(angle), // sin (a+b),
      .z = v.y * sin(angle) + v.z * cos(angle), // cos (a+b)
  };
  return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
  vec3_t rotated_vector = {
      .x = v.x * cos(angle) - v.y * sin(angle), // sin (a+b)
      .y = v.x * sin(angle) + v.y * cos(angle), // cos (a+b)
      .z = v.z};

  return rotated_vector;
}
