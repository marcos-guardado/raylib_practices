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

    if(IsKeyDown(KEY_RIGHT)) ball_pos.x += 2.0f;
    if(IsKeyDown(KEY_LEFT)) ball_pos.x -= 2.0f;
    if(IsKeyDown(KEY_UP)) ball_pos.y -= 2.0f;
    if(IsKeyDown(KEY_DOWN)) ball_pos.y += 2.0f;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(ball_pos, circleRadius, RED);

    EndDrawing();
  }

  CloseWindow();
}
