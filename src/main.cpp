#include "enemies.cpp"
#include "players.cpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

Vector2 MovePlayerDebug();
void RickRoll();

Enemies PrepareEnemies() {
  const uint32_t MAX_ENEMIES = 300;
  Enemies enemies;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    Enemy enemy;
    enemies.AddEnemy(enemy);
  }

  return enemies;
}

Players PreparePlayers() {
  const uint32_t MAX_PLAYERS = 1;
  Players players;
  for (int i = 0; i < MAX_PLAYERS; i++) {
    Player player;
    players.AddPlayer(player);
  }

  return players;
}

void SpawnEnemies(Enemies &enemies) {
  Vector2 prevPos = Vector2{0, 0};
  int minDistance = 500;
  for (auto &position : enemies.position) {
    position.x += GetRandomValue(-1000, 1000);
    position.y += GetRandomValue(-1000, 1000);

    int respawnAttempts = 2500;
    int i = 0;
    while(i < respawnAttempts && Vector2Distance(position, prevPos) < minDistance) {
        position.x = prevPos.x + GetRandomValue(-10000, 10000);
        position.y = prevPos.y + GetRandomValue(-10000, 10000);
        std::cout << "Respawned \n";

        respawnAttempts++;
        i++;
    }


    prevPos.x = position.x;
    prevPos.y = position.y;
  }
}

int main() {
  SetRandomSeed(13231);

  Enemies enemies = PrepareEnemies();
  SpawnEnemies(enemies);
  // for(auto t : enemies.position) {
  //     std::cout << t.x << " " << t.y << '\n';
  // }

  Players players = PreparePlayers();

  int initWindowWidth = 800;
  int initWindowHeight = 600;

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(initWindowWidth, initWindowHeight, "Bloodhound");

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(DARKGRAY);

    enemies.Draw();

    for(int i = 0; i < players.GetSize(); ++i) {
        Vector2* position = &players.position[i];
        Rectangle* rect = &players.rect[i];
        Color* color = &players.color[i];

        Vector2 newPos = MovePlayerDebug();

        if(IsKeyDown(KEY_LEFT_SHIFT)) {
            newPos.x *= 2;
            newPos.y *= 2;
        }

        position->x += newPos.x * GetFrameTime() * 100;
        position->y += newPos.y * GetFrameTime() * 100;


        RectToPosition(*rect, *position);
        DrawRectangleRec(*rect, *color);
    }

    RickRoll();
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

Vector2 MovePlayerDebug() {
  Vector2 moveDirection = Vector2{0, 0};

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    DrawText("A is pressed",
             GetRenderWidth() - MeasureText("A is pressed", 15) - 10, 10, 15,
             ORANGE);
    moveDirection.x += -1;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    DrawText("D is pressed",
             GetRenderWidth() - MeasureText("D is pressed", 15) - 10, 10 + 20,
             15, ORANGE);
    moveDirection.x += 1;
  }

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    DrawText("W is pressed",
             GetRenderWidth() - MeasureText("W is pressed", 15) - 10, 30 + 20,
             15, ORANGE);
    moveDirection.y += -1;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    DrawText("S is pressed",
             GetRenderWidth() - MeasureText("S is pressed", 15) - 10, 50 + 20,
             15, ORANGE);
    moveDirection.y += 1;
  }

  DrawText(TextFormat("inputVector: %f, %f", moveDirection.x, moveDirection.y),
           20, 30, 14, YELLOW);

  moveDirection = Vector2Normalize(moveDirection);

  DrawText(
      TextFormat("normalizedVector: %f, %f", moveDirection.x, moveDirection.y),
      20, 30 * 2, 14, YELLOW);

  DrawText(TextFormat("finalVector: %f, %f", moveDirection.x, moveDirection.y),
           20, 30 * 3, 14, YELLOW);

  return moveDirection;
}

void RickRoll() {
  if (IsKeyPressed(KEY_SPACE)) {
    // OpenURL("https://customrickroll.github.io/");
    OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1");
    // OpenURL("https://shattereddisk.github.io/rickroll/rickroll.mp4");
  }
}
