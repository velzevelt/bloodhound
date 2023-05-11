#include "enemies.cpp"
#include "players.cpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

Vector2 GetMoveDirection();
void RickRoll();

Enemies PrepareEnemies() {
  const uint32_t MAX_ENEMIES = 1000;
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

void SpawnEnemy(Enemies &enemies, int id) {
  Vector2 boundX = {-10, GetRenderWidth() + 10};
  Vector2 boundY = {-10, GetRenderHeight() + 10};



}

Camera2D PrepareCamera(Rectangle &playerRect) {
  Camera2D camera;
  camera.offset = {GetRenderWidth() / 2 - playerRect.width / 2, GetRenderHeight() / 2 - playerRect.height / 2};
  camera.target = {0, 0};
  camera.rotation = 0.0;
  camera.zoom = 1.0;

  return camera;
}

int main() {
  SetRandomSeed(13231);

  Enemies enemies = PrepareEnemies();

  Players players = PreparePlayers();

  int initWindowWidth = 800;
  int initWindowHeight = 600;

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(initWindowWidth, initWindowHeight, "Bloodhound");

  Camera2D camera = PrepareCamera(players.rect[0]);

  while (!WindowShouldClose()) {
    camera.target = players.position[0];
    BeginDrawing();
    ClearBackground(DARKGRAY);

    BeginMode2D(camera);
      enemies.Draw();

      for(int i = 0; i < players.GetSize(); ++i) {
          Vector2* position = &players.position[i];
          Rectangle* rect = &players.rect[i];
          Color* color = &players.color[i];

          Vector2 newPos = GetMoveDirection();

          if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
              newPos.x *= 2;
              newPos.y *= 2;
          }

          position->x += newPos.x * GetFrameTime() * 100;
          position->y += newPos.y * GetFrameTime() * 100;


          RectToPosition(*rect, *position);
          DrawRectangleRec(*rect, *color);
      }

    EndMode2D();

    RickRoll();
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

Vector2 GetMoveDirection() {
  Vector2 moveDirection = Vector2{0, 0};

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    moveDirection.x += -1;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    moveDirection.x += 1;
  }

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    moveDirection.y += -1;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    moveDirection.y += 1;
  }

  moveDirection = Vector2Normalize(moveDirection);
  return moveDirection;
}

void RickRoll() {
  if (IsKeyPressed(KEY_SPACE)) {
    // OpenURL("https://customrickroll.github.io/");
    OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1");
    // OpenURL("https://shattereddisk.github.io/rickroll/rickroll.mp4");
  }
}
