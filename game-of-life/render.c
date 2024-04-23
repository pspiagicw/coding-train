#include "golf.h"
#include "raylib.h"

void vertical() {
  for (int i = 0; i < COLUMNS; i++) {
    DrawLine(GRID_START + (i * CELL_DIMENSION), GRID_START,
             GRID_START + (i * CELL_DIMENSION), GRID_HEIGHT + GRID_START,
             RAYWHITE);
  }
}

void horizontal() {
  for (int i = 0; i < ROWS; i++) {
    DrawLine(GRID_START, GRID_START + (i * CELL_DIMENSION),
             GRID_WIDTH + GRID_START, GRID_START + (i * CELL_DIMENSION),
             RAYWHITE);
  }
}

void border() {
  DrawRectangleLines(GRID_START, GRID_START, GRID_WIDTH, GRID_HEIGHT, RAYWHITE);
}

void cells(State *state) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (state->board[i][j]) {
        int x = GRID_START + (j * CELL_DIMENSION);
        int y = GRID_START + (i * CELL_DIMENSION);
        DrawRectangle(x, y, CELL_DIMENSION, CELL_DIMENSION, RAYWHITE);
      }
    }
  }
}

void title() { DrawText("GAME OF LIFE", 300, 10, 20, RAYWHITE); }

void render(State *state) {
  title();
  border();
  vertical();
  horizontal();
  cells(state);
}
void game_over() { DrawText("GAME OVER", 250, 250, 50, RED); }
