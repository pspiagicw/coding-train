#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINES 150

enum Algorithm { BubbleSort, SelectionSort, QuickSort };

typedef struct {
  bool shouldClose;

  int arr[LINES];

  // Sorting algorithm used
  int sortAlgo;

  // Input flags
  bool paused;

  // Selection sort
  int index;
} State;

void fill(State *state) {
  for (int i = 0; i < LINES; i++) {
    state->arr[i] = i + 1;
  }
}

void shuffle(State *state) {
  for (int i = LINES - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = state->arr[i];
    state->arr[i] = state->arr[j];
    state->arr[j] = temp;
  }
}

void init() {
  const int screen_height = 800;
  const int screen_width = 800;

  InitWindow(screen_width, screen_height, "Sorts");

  SetTargetFPS(60);

  srand(time(NULL));
}
void toggle(State *state) { state->paused = !state->paused; }

void reset(State *state) {
  fill(state);
  shuffle(state);
  state->index = 0;
}

void input(State *state) {
  if (IsKeyPressed(KEY_R)) {
    reset(state);
  } else if (IsKeyPressed(KEY_B)) {
    state->sortAlgo = BubbleSort;
  } else if (IsKeyPressed(KEY_SPACE)) {
    toggle(state);
  } else if (IsKeyPressed(KEY_S)) {
    state->sortAlgo = SelectionSort;
  } else if (IsKeyPressed(KEY_Q)) {
    state->sortAlgo = QuickSort;
  }
}

void quit() { CloseWindow(); }

void bubble(State *state) {
  for (int i = 0; i < LINES - 1; i++) {
    if (state->arr[i] > state->arr[i + 1]) {
      int temp = state->arr[i];
      state->arr[i] = state->arr[i + 1];
      state->arr[i + 1] = temp;
    }
  }
}

void selection(State *state) {
  int min = state->arr[state->index];
  int minIndex = state->index;
  for (int i = state->index; i < LINES; i++) {
    if (min > state->arr[i]) {
      min = state->arr[i];
      minIndex = i;
    }
  }
  int temp = state->arr[minIndex];
  state->arr[minIndex] = state->arr[state->index];
  state->arr[state->index] = temp;
  state->index += 1;
}

// void quickFunc(State *state, int low, int high) {
//   if (low < high) {
//     int pi = partition(arr, low, high);
//
//     quickFunc(arr, low, pi - 1);
//     quickFunc(arr, pi + 1, high);
//   }
// }
//
// void quicksort(State *state) {}

void sort(State *state) {
  if (state->sortAlgo == BubbleSort) {
    bubble(state);
  } else if (state->sortAlgo == SelectionSort) {
    selection(state);
  } else if (state->sortAlgo == QuickSort) {
  }
}

void update(State *state) {
  state->shouldClose = WindowShouldClose();

  if (!state->paused) {
    sort(state);
  }
}

void lines(State *state) {
  int start_x = 25;

  int start_y = 775;

  for (int i = 0; i < LINES; i++) {
    int length = state->arr[i] * 5;

    DrawRectangle(start_x, start_y - length, 5, length, WHITE);

    start_x += 5;
  }
}

void help() {
  DrawRectangleLines(10, 10, 200, 300, WHITE);
  DrawText("R - Reset", 15, 15, 20, WHITE);
  DrawText("B - Bubble Sort", 15, 40, 20, WHITE);
  DrawText("S - Selection Sort", 15, 65, 20, WHITE);
  DrawText("M - Merge Sort", 15, 90, 20, WHITE);
  DrawText("Q - Quick Sort", 15, 115, 20, WHITE);
  DrawText("SPACE - Pause", 15, 140, 20, WHITE);
}

void render(State *state) {
  BeginDrawing();

  ClearBackground(BLACK);

  lines(state);
  help();

  EndDrawing();
}

State *new() {
  State *state = malloc(sizeof(State));

  state->shouldClose = false;
  state->sortAlgo = BubbleSort;
  state->index = 0;

  fill(state);
  shuffle(state);

  return state;
}

int main() {

  init();

  State *state = new ();

  while (!state->shouldClose) {

    input(state);
    update(state);
    render(state);
  }

  quit();

  return 0;
}
