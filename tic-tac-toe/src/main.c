#include "ttt.h"
#include <raylib.h>

int main() {

  const int screen_height = 640;
  const int screen_width = 800;

  InitWindow(screen_width, screen_height, "Tic Tac Toe");

  SetTargetFPS(60);

  int *players = get_empty_players();

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(BLACK);

    draw_board();
    draw_players(players);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      int position = detect_position();
      if (position != -1) {
        update_players(players, position);
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
