#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = false;

void setup(void) {}
void process_input(void) {}
void update(void) {}
void render(void) {}

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDl.\n");
    return false;
  }

  /* Create SDL window */
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "ERROR: Failed to create SDL window.\n");
    return false;
  }

  // TODO: Create SDL Renderer
  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    fprintf(stderr, "ERROR: Failed to create SDL renderer.\n");
    return false;
  }

  return true;
}

int main(void) {

  is_running = initialize_window();

  setup();

  while (true) {
    process_input();
    update();
    render();
  }

  return 0;
}
