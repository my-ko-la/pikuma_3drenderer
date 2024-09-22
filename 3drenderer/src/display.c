#include "display.h"

#define SET_COLOR_BUFFER(x, y, color)                                          \
  (color_buffer[WINDOW_WIDTH * (y) + (x)] = (color))

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

#if 0
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
#endif

  return true;
}

void destroy_window() {
  free(color_buffer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

/*

* * * * RENDER * * * *

*/

void render_color_buffer() {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int)(WINDOW_WIDTH * sizeof(uint32_t)));

  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

// Set color buffer
void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
      SET_COLOR_BUFFER(x, y, color);
    }
  }
}

void draw_grid(int yfreq, int xfreq) {
  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
      if (divisible(y, yfreq) || divisible(x, xfreq))
        SET_COLOR_BUFFER(x, y, GRAY);
    }
  }
}

void draw_dotted(int yfreq, int xfreq) {
  for (int y = 0; y < WINDOW_HEIGHT; y += yfreq) {
    for (int x = 0; x < WINDOW_WIDTH; x += xfreq) {
      SET_COLOR_BUFFER(x, y, GRAY);
    }
  }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
  // Bounding box
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      // To do less work, only iterate over the pixels you need
      // by using an offset immediately, no if condition required
      int current_x = x + i;
      int current_y = y + j;
      SET_COLOR_BUFFER(current_x, current_y, color);
    }
  }
}

void draw_pixel(int x, int y, uint32_t color) { SET_COLOR_BUFFER(x, y, color); }

/*

* * * * MISC * * * *

*/
void set_window_height(int *wh, int value) { *wh = value; };

void set_window_width(int *ww, int value) { *ww = value; };
