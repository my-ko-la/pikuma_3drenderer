#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "camera.h"
#include "display.h"
#include "vector.h"

/*

* * * * GLOBALS * * * *

*/

const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];

const int LAPTOP_MONITOR = 0;
const int RED = 0xFFFF0000;
const int GRAY = 0xFF333333;

SDL_DisplayMode display_mode;
bool is_running = false;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

void setup(void) {
  color_buffer = // a.k.a. Frame Buffer
      (uint32_t *)malloc(sizeof(color_buffer) * WINDOW_WIDTH * WINDOW_HEIGHT);

  if (!color_buffer) {
    fprintf(stderr, "Buy more RAM.\n");
  }

  color_buffer_texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_ARGB8888, // Format is alpha first then colors, all 8 bits
      SDL_TEXTUREACCESS_STREAMING, // Frame by frame dynamic updates
      WINDOW_WIDTH, WINDOW_HEIGHT);

  int point_count = 0;
  for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        vec3_t new_point = {.x = x, .y = y, .z = z};
        cube_points[point_count] = new_point;
        point_count++;
      }
    }
  }
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
    }
    break;
  }
}

/*

* * * * UPDATE * * * *

*/

void update(void) {}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 214, 250, 78, 255);
  SDL_RenderClear(renderer);

  draw_grid(10, 10);

  draw_rect(400, 300, 155, 100, RED);
  draw_pixel(399, 288, RED);

  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

/*

* * * * INIT * * * *

*/

int main(void) {

  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  return 0;
}
