#include "raylib.h"
#include <cstdint>

# define MAX_BUILDINGS 100

int main() {
  // Define window sizes
  const uint16_t WIDTH = 800;
  const uint16_t HEIGHT = 450;
  uint8_t currentFps = 60;

  InitWindow(WIDTH, HEIGHT, "CAMERA_3D");

  Vector3 cube_pos = { 0.0f, 0.0f, 0.0f };

  Camera3D camera = { 0 };
  camera.position = { 0.0f, 10.0f, 10.0f };
  camera.target = { 0.0f, 0.0f, 0.0f };
  camera.up = { 0.0f, 1.0f, 0.0f };
  camera.fovy = 45.f;
  camera.projection = CAMERA_PERSPECTIVE;
  SetTargetFPS(currentFps);

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_RIGHT)) cube_pos.x += 2 * GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) cube_pos.x -= 2 * GetFrameTime();
    if (IsKeyDown(KEY_UP)) cube_pos.z -= 2 * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) cube_pos.z += 2 * GetFrameTime();

    if(IsKeyDown(KEY_W)) camera.position.z -= 2 * GetFrameTime();
    if(IsKeyDown(KEY_S)) camera.position.z += 2 * GetFrameTime();


    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera);
        DrawCube(cube_pos, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cube_pos, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);

    EndMode3D();

    EndDrawing();
  }

  CloseWindow();
}
