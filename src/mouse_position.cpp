#include "raylib.h"
#include <cstdint>

int main() {
  // Define window sizes
  const uint16_t WIDTH = 800;
  const uint16_t HEIGHT = 450;
  uint8_t currentFps = 60;

  InitWindow(WIDTH, HEIGHT, "BALL MOVEMENT");

  Vector2 ball_pos = { WIDTH / 2.0f, HEIGHT / 2.0f };

  const float circleRadius = 32.0f;

  SetTargetFPS(currentFps);

  while (!WindowShouldClose()) {

    ball_pos = GetMousePosition();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(ball_pos, circleRadius, BLUE);

    EndDrawing();
  }

  CloseWindow();
}
