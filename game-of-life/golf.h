#include <stdbool.h>

#ifndef GOLF_HEADER

#define GOLF_HEADER

#define CELL_DIMENSION 2
#define GRID_START 50
#define COLUMNS GRID_WIDTH / CELL_DIMENSION
#define ROWS GRID_HEIGHT / CELL_DIMENSION
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define GRID_WIDTH 700
#define GRID_HEIGHT 500
#define WINDOW_NAME "Game of Life"

typedef struct {
  bool **board;
  int alive;
  int dead;
} State;

// State stuff
bool **board();
void randomize(State *state);
State *initial();
int get_neighbor_count(State *state, int i, int j);
void update(State *state);
bool check(State *state);
void game_over();

// Render Stuff
void vertical();
void horizontal();
void border();
void cells(State *state);
void render(State *state);

// Lifecycle
void setup();
void game_loop();
void close();

#endif

enum Screen { TITLE = 0, GAME };
