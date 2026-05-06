#include <cstdint>
#include <raylib.h>
#include <sys/types.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800
#define FPS 60
#define PADDING_X 10
#define PADDLE_COMMON_WIDTH 25
#define PADDLE_COMMON_HEIGHT 120

class Ball {
public:
  float x, y;
  float speedX, speedY;
  float radius;

  void Draw() { DrawCircle(x, y, radius, WHITE); }
  void Update() {
    x += speedX;
    y += speedY;
  }
};

class Paddle {
public:
  float x, y;
  float speed;

  void Draw() {
    DrawRectangleRounded(
        Rectangle{x, y, PADDLE_COMMON_WIDTH, PADDLE_COMMON_HEIGHT}, 2, 0,
        WHITE);
  }

  void Update(Ball &ball) {

    if (IsKeyDown(KEY_W)) {
      y -= 5;
    }
    if (IsKeyDown(KEY_S)) {
      y += 5;
    }

    CheckBoundaries();
    CheckCollisions(ball);
  }

protected:
  void CheckCollisions(Ball &ball) {
    bool hasCollision = CheckCollisionCircleRec(
        Vector2{ball.x, ball.y}, ball.radius,
        Rectangle{x, y, PADDLE_COMMON_WIDTH, PADDLE_COMMON_HEIGHT});

    if (hasCollision) {
      ball.speedX *= -1;
    }
  }

  void CheckBoundaries() {
    if (y <= 0) {
      y = 0;
    }

    if (y + PADDLE_COMMON_HEIGHT >= WINDOW_HEIGHT) {
      y = WINDOW_HEIGHT - PADDLE_COMMON_HEIGHT;
    }
  }
};

class CpuPaddle : public Paddle {
public:
  void Update(Ball &ball) {
    if (y + PADDLE_COMMON_HEIGHT / 2.f > ball.y) {
      y -= 5;
    }

    if (y - PADDLE_COMMON_HEIGHT / 2.f <= ball.y) {
      y += 5;
    }

    CheckBoundaries();
    CheckCollisions(ball);
  }
};

void GameManager(Ball &ball, Paddle &player, CpuPaddle &cpu, uint16_t &cpuScore,
                 uint16_t &playerScore);

Ball ball;
Paddle player;
CpuPaddle bot;

int main() {
  std::uint16_t cpuScore = 0;
  std::uint16_t playerScore = 0;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ping Pong - Also play terraria");
  SetTargetFPS(FPS);
  const std::uint16_t initialX = WINDOW_WIDTH / 2;
  const std::uint16_t initialY = WINDOW_HEIGHT / 2;

  std::uint16_t initialPaddleOneY = initialY - (PADDLE_COMMON_HEIGHT / 2);
  std::uint16_t initialPaddleTwoY = initialY - (PADDLE_COMMON_HEIGHT / 2);

  const std::uint16_t initialPaddleOneX = PADDING_X;
  const std::uint16_t initialPaddleTwoX =
      WINDOW_WIDTH - PADDLE_COMMON_WIDTH - PADDING_X;

  ball.radius = 10;
  ball.x = initialX;
  ball.y = initialY;
  ball.speedX = 7;
  ball.speedY = 7;

  player.x = initialPaddleOneX;
  player.y = initialPaddleOneY;

  bot.x = initialPaddleTwoX;
  bot.y = initialPaddleTwoY;

  while (WindowShouldClose() == false) {
    // Update
    GameManager(ball, player, bot, cpuScore, playerScore);
    ball.Update();
    player.Update(ball);
    bot.Update(ball);

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(initialX, 0, initialX, WINDOW_HEIGHT, WHITE);
    DrawText(TextFormat("%i", cpuScore), WINDOW_WIDTH / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", playerScore), 3 * WINDOW_WIDTH / 4 - 20, 20, 80,
             WHITE);
    bot.Draw();
    ball.Draw();
    player.Draw();
    EndDrawing();
  }

  return 0;
}

void GameManager(Ball &ball, Paddle &player, CpuPaddle &cpu, uint16_t &cpuScore,
                 uint16_t &playerScore) {
  const int speedChoices[2] = {-1, 1};

  auto resetBall = [&]() {
    ball.x = WINDOW_WIDTH / 2.f;
    ball.y = WINDOW_HEIGHT / 2.f;

    ball.speedX *= speedChoices[GetRandomValue(0, 1)];
    ball.speedY *= speedChoices[GetRandomValue(0, 1)];
  };

  if (ball.y + ball.radius >= WINDOW_HEIGHT || ball.y - ball.radius <= 0) {
    ball.speedY *= -1;
  }

  if (ball.x + ball.radius >= WINDOW_WIDTH) {
    playerScore += 1;
    resetBall();
  }

  if (ball.x - ball.radius <= 0) {
    cpuScore += 1;
    resetBall();
  }
}
