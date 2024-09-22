#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

extern const int FOV_FACTOR;
extern vec3_t camera_position;

typedef struct {
  vec3_t position;
  vec3_t rotation;
  float fov_angle;
} camera_t;

#endif
