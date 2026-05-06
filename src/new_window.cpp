#include "raylib.h"
#include <cstdint>

int main() {
  // Define window sizes
  const uint16_t WIDTH = 800;
  const uint16_t HEIGHT = 450;
  uint8_t currentFps = 60;

  InitWindow(WIDTH, HEIGHT, "TEST WINDOW");

  Vector2 delta_circle = {0, (float) HEIGHT / 3.0f};
  Vector2 frame_circle = {0, (float) HEIGHT * (2.0f / 3.0f )};

  const float speed = 10.0f;
  const float circleRadius = 32.0f;

  SetTargetFPS(currentFps);

  while (!WindowShouldClose()) {


    delta_circle.x += GetFrameTime() * 6.0f * speed;
    frame_circle.x += 0.1f * speed;

    if (delta_circle.x > WIDTH) delta_circle.x = 0;
    if (frame_circle.x > WIDTH) frame_circle.x = 0;

    if (IsKeyPressed(KEY_R)) {
        delta_circle.x = 0;
        frame_circle.x = 0;
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(delta_circle, circleRadius, RED);
    DrawCircleV(frame_circle, circleRadius, BLUE);

    const char *fpsText = nullptr;
    if (currentFps <= 0) fpsText = TextFormat("FPS: unlimited (%i)", GetFPS());
    else fpsText = TextFormat("FPS: %i (target: %i)", GetFPS(), currentFps);
    DrawText(fpsText, 10, 10, 20, DARKGRAY);
    DrawText(TextFormat("Frame time: %02.02f ms", GetFrameTime()), 10, 30, 20, DARKGRAY);
    DrawText("FUNC: x += GetFrameTime()*speed", 10, 90, 20, RED);
    DrawText("FUNC: x += speed", 10, 240, 20, BLUE);

    EndDrawing();
  }

  CloseWindow();
}
