#include "golf.h"
#include <goreland.h>
#include <stdlib.h>

State *initial() {
  State *s = malloc(sizeof(State));
  if (s == NULL) {
    logFatal("Can't allocate memory for state;");
  }
  s->board = board();
  s->alive = 0;
  s->dead = 0;
  return s;
}
void randomize(State *state) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      state->board[i][j] = rand() & 1;
    }
  }
}

bool **board() {
  bool **board = malloc(sizeof(bool *) * ROWS);
  if (board == NULL) {
    logFatal("Can't allocate memory for board;");
  }

  for (int i = 0; i < ROWS; i++) {
    bool *row = malloc(sizeof(bool) * COLUMNS);
    if (row == NULL) {
      logFatal("Can't allocate memory for grid row;");
    }
    board[i] = row;
  }
  return board;
}

int get_neighbor_count(State *state, int i, int j) {
  int count = 0;
  for (int id = -1; id < 2; id++) {
    for (int jd = -1; jd < 2; jd++) {
      int ni = i + id;
      int nj = j + jd;
      if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLUMNS &&
          !(id == 0 && jd == 0)) {
        if (state->board[ni][nj]) {
          count++;
        }
      }
    }
  }
  return count;
}

void update(State *state) {
  State *newState = initial();
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      int ncount = get_neighbor_count(state, i, j);
      if (state->board[i][j]) {
        // Alive
        if (ncount < 2 || ncount > 3) {
          newState->board[i][j] = false;
        } else {
          newState->board[i][j] = true;
        }
      } else {
        // Dead
        if (ncount == 3) {
          newState->board[i][j] = true;
        } else {
          newState->board[i][j] = false;
        }
      }
    }
  }
  *state = *newState;
}

bool check(State *state) {
  bool alive = false;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      alive = alive || state->board[i][j];
    }
  }
  return alive;
}
