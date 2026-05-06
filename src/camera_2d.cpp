#include "raylib.h"
#include <cstdint>
#include <cmath>

# define MAX_BUILDINGS 100

int main() {
  // Define window sizes
  const uint16_t WIDTH = 800;
  const uint16_t HEIGHT = 450;
  const uint8_t MIN_BUILDING_WIDTH = 50;
  const uint8_t MAX_BUILDING_WIDTH = 200;
  const uint8_t MIN_BUILDING_HEIGHT = 200;
  const uint8_t MAX_BUILDING_HEIGHT = 100;

  uint8_t currentFps = 60;

  InitWindow(WIDTH, HEIGHT, "CAMERA_2D");

  Rectangle player_pos = { 400, 280, 40, 40 }; // Player initial position, heigth and width
  Rectangle buildings[MAX_BUILDINGS] = { 0 }; // Array of rectangles that will be buildings
  Color buildColors[MAX_BUILDINGS] = { 0 };

  int spacing = 0;

  for (uint8_t i = 0; i < MAX_BUILDINGS; i++) {
      buildings[i].width = (float)GetRandomValue(MIN_BUILDING_WIDTH, MAX_BUILDING_WIDTH);
      buildings[i].height = (float)GetRandomValue(MIN_BUILDING_HEIGHT, MAX_BUILDING_HEIGHT);
      buildings[i].y = HEIGHT - 130.0f - buildings[i].height;
      buildings[i].x = -6000.0f + spacing;

      spacing += (int)buildings[i].width;

      //TODO: Understand better how color works
      buildColors[i] = (Color) {
          (unsigned char)GetRandomValue(200, 240),
          (unsigned char)GetRandomValue(200, 240),
          (unsigned char)GetRandomValue(200, 240),
          255
      };
  }

  Camera2D camera = { 0 };
  camera.target = { player_pos.x + 20.0f, player_pos.y + 20.0f };
  camera.offset = { WIDTH / 2.0f, HEIGHT / 2.0f };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetTargetFPS(currentFps);

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_RIGHT)) player_pos.x += 2;
    else if (IsKeyDown(KEY_LEFT)) player_pos.x -= 2;

    camera.target = (Vector2){ player_pos.x + 20, player_pos.y + 20 };

    if (IsKeyDown(KEY_A)) camera.rotation--;
    else if (IsKeyDown(KEY_S)) camera.rotation++;

    // Camera zoom controls
    // Uses log scaling to provide consistent zoom speed
    camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));

    if (camera.zoom > 3.0f) camera.zoom = 3.0f;
    else if (camera.zoom < 0.1f) camera.zoom = 0.1f;


    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
        DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
        for(uint8_t i = 0; i < MAX_BUILDINGS; i++) DrawRectangleRec(buildings[i], buildColors[i]);
        DrawRectangleRec(player_pos, RED);
    EndMode2D();

    EndDrawing();
  }

  CloseWindow();
}
