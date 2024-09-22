#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "helper.h"

/*

* * * * GLOBALS * * * *

*/

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_DisplayMode display_mode;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

extern const int LAPTOP_MONITOR;
extern const int RED;
extern const int GRAY;

/*

* * * * PROTOTYPES * * * *

*/

bool initialize_window(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void draw_grid(int yfreq, int xfreq);
void render_color_buffer(void);
void destroy_window(void);
void clear_color_buffer(uint32_t color);
void set_window_width(int *ww, int w);
void set_window_height(int *wh, int h);

#endif
