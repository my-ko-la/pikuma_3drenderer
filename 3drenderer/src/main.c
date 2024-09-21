#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "helper.h"

/*

* * * * GLOBALS * * * *

*/

// Local
const int LAPTOP_MONITOR = 0;

SDL_DisplayMode display_mode;
bool is_running = false;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

const int RED = 0xFFFF0000;
const int GRAY = 0xFF333333;

/*

* * * * MISC * * * *

*/
void set_window_height(int *wh, int value) { *wh = value; };

void set_window_width(int *ww, int value) { *ww = value; };
/*

* * * * UPDATE * * * *

*/
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

void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
      color_buffer[(WINDOW_WIDTH * y) + x] = color;
    }
  }
}

/*

* * * * RENDER * * * *

*/
void render_color_buffer() {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int)(WINDOW_WIDTH * sizeof(uint32_t)));

  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid(int yfreq, int xfreq) {
  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
      if (divisible(y, yfreq) || divisible(x, xfreq))
        color_buffer[(WINDOW_WIDTH * y) + x] = GRAY;
    }
  }
}

void draw_dotted(int yfreq, int xfreq) {
  for (int y = 0; y < WINDOW_HEIGHT; y += yfreq) {
    for (int x = 0; x < WINDOW_WIDTH; x += xfreq) {
      color_buffer[(WINDOW_WIDTH * y) + x] = GRAY;
    }
  }
}

void draw_rect(int pos_x, int pos_y, int width, int height, uint32_t color) {
  // Bounding box
  const int vert_bound = pos_y + height;
  const int hori_bound = pos_x + width;

  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
      if (y >= pos_y && y <= vert_bound && x >= pos_x && x <= hori_bound)
        color_buffer[(WINDOW_WIDTH * y) + x] = color;
    }
  }
}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 214, 250, 78, 255);
  SDL_RenderClear(renderer);

#if 0
  draw_grid(10, 10);
  draw_dotted(10, 10);
#endif

  draw_rect(400, 300, 75, 50, RED);

  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

/*

* * * * INIT * * * *

*/
bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDl.\n");
    return false;
  }

  // Fullscreen the program
  SDL_GetCurrentDisplayMode(LAPTOP_MONITOR, &display_mode);
  set_window_width(&WINDOW_WIDTH, display_mode.w);
  set_window_height(&WINDOW_HEIGHT, display_mode.h);

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "ERROR: Failed to create SDL window.\n");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    fprintf(stderr, "ERROR: Failed to create SDL renderer.\n");
    return false;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return true;
}

void destroy_window() {
  free(color_buffer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

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
