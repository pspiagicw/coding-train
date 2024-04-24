#include "golf.h"
#include <goreland.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void input(State *state) {
  if (IsKeyPressed(KEY_R)) {
    *state = *initial();
    randomize(state);
  }
}

int main() {

  srand(time(NULL));

  const int screen_height = SCREEN_HEIGHT;
  const int screen_width = SCREEN_WIDTH;

  InitWindow(screen_width, screen_height, "Game of Life");

  SetTargetFPS(60);

  State *state = initial();
  randomize(state);

  while (WindowShouldClose() == false) {

    BeginDrawing();

    ClearBackground(BLACK);

    input(state);
    update(state);
    render(state);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
