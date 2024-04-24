#include <float.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  Vector2 *a;
  Vector2 *b;
} Boundary;

typedef struct {
  Vector2 *pos;
  Vector2 *dir;
} Ray2D;

typedef struct {
  Vector2 *pos;
  Ray2D **rays;
} Particle;

void lookAtMouse(Ray2D *r) {
  r->dir->x = GetMouseX() - r->pos->x;
  r->dir->y = GetMouseY() - r->pos->y;
  *r->dir = Vector2Normalize(*r->dir);
}

Ray2D *newRay(Vector2 *pos, int angle) {
  Ray2D *r = malloc(sizeof(Ray2D));

  Vector2 *d = malloc(sizeof(Vector2));
  d->x = cos(angle);
  d->y = sin(angle);

  r->pos = pos;
  r->dir = d;

  return r;
}

void showRay(Ray2D *r) {
  int x = r->pos->x;
  int y = r->pos->y;

  int xd = r->dir->x * 20;
  int yd = r->dir->y * 20;
  DrawLine(x, y, x + xd, y + yd, WHITE);
}

Vector2 *castRay(Ray2D *ray, Boundary *wall) {
  const float x1 = wall->a->x;
  const float y1 = wall->a->y;
  const float x2 = wall->b->x;
  const float y2 = wall->b->y;

  const float x3 = ray->pos->x;
  const float y3 = ray->pos->y;
  const float x4 = ray->pos->x + ray->dir->x;
  const float y4 = ray->pos->y + ray->dir->y;

  const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  if (den == 0) {
    return NULL;
  }

  const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
  const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

  Vector2 *pt = malloc(sizeof(Vector2));
  if (t >= 0 && t <= 1 && u > 0) {
    pt->x = x1 + t * (x2 - x1);
    pt->y = y1 + t * (y2 - y1);
    return pt;
  } else {
    return NULL;
  }
}

Boundary *newBoundary(float x1, float y1, float x2, float y2) {
  Boundary *boundary = malloc(sizeof(Boundary));

  Vector2 *a = malloc(sizeof(Vector2));
  a->x = x1;
  a->y = y1;

  Vector2 *b = malloc(sizeof(Vector2));
  b->x = x2;
  b->y = y2;

  boundary->a = a;
  boundary->b = b;

  return boundary;
}
void showBoundary(Boundary *b) { DrawLineV(*b->a, *b->b, WHITE); }

Ray2D **createRays(Vector2 *pos) {
  Ray2D **rays = malloc(sizeof(Ray2D *) * 360);
  for (int i = 0; i < 360; i++) {
    rays[i] = newRay(pos, i);
  }
  return rays;
}

void showParticle(Particle *p) {
  DrawCircleV(*p->pos, 5, WHITE);
  for (int i = 0; i < 360; i++) {
    showRay(p->rays[i]);
  }
}

Vector2 *newVector(float x, float y) {
  Vector2 *v = malloc(sizeof(Vector2));
  v->x = x;
  v->y = y;

  return v;
}
void particleLook(Particle *p, Boundary **walls) {
  for (int i = 0; i < 360; i++) {
    Vector2 *closest = NULL;
    float record = FLT_MAX;
    for (int j = 0; j < 5; j++) {
      Vector2 *pt = castRay(p->rays[i], walls[j]);
      if (pt != NULL) {
        float d = Vector2DistanceSqr(*p->pos, *pt);
        if (d <= record) {
          record = d;
          closest = pt;
        }
      }
    }
    if (closest != NULL) {
      DrawLineV(*p->pos, *closest, WHITE);
    }
  }
}

void updateParticle(Particle *p, Vector2 mousePos) { p->pos = &mousePos; }

Boundary **createWalls() {
  Boundary **walls = malloc(sizeof(Boundary *) * 5);
  for (int i = 0; i < 5; i++) {
    walls[i] = newBoundary(GetRandomValue(0, 800), GetRandomValue(0, 800),
                           GetRandomValue(0, 800), GetRandomValue(0, 800));
  }

  return walls;
}

int main() {
  const int screen_width = 800;
  const int screen_height = 800;
  InitWindow(screen_width, screen_height, "Raycasting");
  SetTargetFPS(60);

  // Boundary *b = newBoundary(700, 100, 700, 700);
  Boundary **walls = createWalls();
  // Ray2D *r = newRay(100, 400);
  Vector2 *pos = newVector(100, 400);
  Particle p;
  p.pos = pos;
  p.rays = createRays(pos);

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < 5; i++) {
      showBoundary(walls[i]);
    }
    updateParticle(&p, GetMousePosition());
    // showParticle(&p);
    particleLook(&p, walls);
    // showRay(r);
    // lookAtMouse(r);
    // Vector2 *pt = castRay(r, b);
    // if (pt != NULL) {
    //   DrawCircleV(*pt, 5, WHITE);
    // }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
