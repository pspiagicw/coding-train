#include "ttt.h"
#include <raylib.h>
#include <stdlib.h>

typedef struct {
  Vector2 leftStart;
  Vector2 leftEnd;
  Vector2 rightStart;
  Vector2 rightEnd;
} Cross;

void draw_board() {
  // Horizontal lines
  DrawLine(150, 200, 650, 200, WHITE);
  DrawLine(150, 400, 650, 400, WHITE);

  // Vertical Lines
  DrawLine(300, 75, 300, 550, WHITE);
  DrawLine(500, 75, 500, 550, WHITE);
}

int *get_empty_players() {
  int *board = malloc(sizeof(int) * 9);
  return board;
}

void draw_circles() {
  Vector2 centers[] = {{220, 125}, {400, 125}, {590, 125},
                       {220, 300}, {400, 300}, {590, 300},
                       {220, 490}, {400, 490}, {590, 490}};
  const int radius = 50;
  for (int i = 0; i < 9; i++) {
    DrawCircleLinesV(centers[i], radius, WHITE);
  }
}

void draw_crosses() {
  Cross xs[] = {
      // First Row
      {.leftStart = {200, 90},
       .leftEnd = {250, 170},
       .rightStart = {250, 90},
       .rightEnd = {200, 170}},
      {.leftStart = {375, 90},
       .leftEnd = {425, 170},
       .rightStart = {425, 90},
       .rightEnd = {375, 170}},
      {.leftStart = {550, 90},
       .leftEnd = {600, 170},
       .rightStart = {600, 90},
       .rightEnd = {550, 170}},

      // Second Row
      {.leftStart = {200, 260},
       .leftEnd = {250, 340},
       .rightStart = {250, 260},
       .rightEnd = {200, 340}},

      {.leftStart = {375, 260},
       .leftEnd = {425, 340},
       .rightStart = {425, 260},
       .rightEnd = {375, 340}},

      {.leftStart = {550, 260},
       .leftEnd = {600, 340},
       .rightStart = {600, 260},
       .rightEnd = {550, 340}},

      // Third Row
      {.leftStart = {200, 440},
       .leftEnd = {250, 520},
       .rightStart = {250, 440},
       .rightEnd = {200, 520}},

      {.leftStart = {375, 440},
       .leftEnd = {425, 520},
       .rightStart = {425, 440},
       .rightEnd = {375, 520}},

      {.leftStart = {550, 440},
       .leftEnd = {600, 520},
       .rightStart = {600, 440},
       .rightEnd = {550, 520}},
  };

  for (int i = 0; i < 9; i++) {
    Cross cross = xs[i];
    DrawLineV(cross.leftStart, cross.leftEnd, WHITE);
    DrawLineV(cross.rightStart, cross.rightEnd, WHITE);
  }
}

void draw_players(int *board) {
  draw_circles();
  draw_crosses();
}

int detect_position() {}
