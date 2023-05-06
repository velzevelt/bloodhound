#include <raylib.h>
#include <raymath.h>
#include <iostream>


void MovePlayerDebug(Rectangle &player);
void RickRoll();


int main() {

    int initWindowWidth = 800;
    int initWindowHeight = 600;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(initWindowWidth, initWindowHeight, "Bloodhound");


    Rectangle player = {GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f, 40, 40};

    Rectangle obstacle = player;
    obstacle.x *= 1.5f;
    obstacle.width *= 2;
    obstacle.height *= 2;
    
    Camera2D camera;
    camera.offset = Vector2{GetRenderWidth() / 2.0f - player.width, GetRenderHeight() / 2.0f - player.height};
    camera.target = Vector2{player.x, player.y};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        camera.target = Vector2{player.x, player.y};
        
        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode2D(camera);
                DrawRectangleRec(obstacle, LIGHTGRAY);
                DrawRectangleRec(player, RED);
            EndMode2D();

            MovePlayerDebug(player);
            RickRoll();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


void MovePlayerDebug(Rectangle &player) {
    Vector2 moveDirection = Vector2{0, 0};

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        DrawText("A is pressed", GetRenderWidth() - MeasureText("A is pressed", 15) - 10,
                 10,
                 15,
                 ORANGE
        );
        moveDirection.x += -1;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        DrawText("D is pressed", GetRenderWidth() - MeasureText("D is pressed", 15) - 10,
                 10 + 20,
                 15,
                 ORANGE
        );
        moveDirection.x += 1;
    }

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        DrawText("W is pressed", GetRenderWidth() - MeasureText("W is pressed", 15) - 10,
                 30 + 20,
                 15,
                 ORANGE
        );
        moveDirection.y += -1;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        DrawText("S is pressed", GetRenderWidth() - MeasureText("S is pressed", 15) - 10,
                 50 + 20,
                 15,
                 ORANGE
        );
        moveDirection.y += 1;
    }

    DrawText(TextFormat("inputVelocity: %f, %f", moveDirection.x, moveDirection.y), 20, 30, 14, YELLOW);

    moveDirection = Vector2Normalize(moveDirection);

    DrawText(TextFormat("normalizedVector: %f, %f", moveDirection.x, moveDirection.y), 20, 30 * 2, 14, YELLOW);

    moveDirection.x *= GetFrameTime() * 100;
    moveDirection.y *= GetFrameTime() * 100;

    DrawText(TextFormat("finalVector: %f, %f", moveDirection.x, moveDirection.y), 20, 30 * 3, 14, YELLOW);

    player.x += moveDirection.x;
    player.y += moveDirection.y;
}


void RickRoll() {
    if (IsKeyPressed(KEY_SPACE)) {
        OpenURL("https://customrickroll.github.io/");
        //OpenURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1");
        //OpenURL("https://shattereddisk.github.io/rickroll/rickroll.mp4");
    }
}
