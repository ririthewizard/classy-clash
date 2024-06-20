#include <raylib.h>
#include "raymath.h"

int main()
{
    int windowDimensions[2]{1024, 1024}; //width, height

    InitWindow(windowDimensions[0], windowDimensions[1], "Riley's Top Down");

    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");

    float speed{6.0};

    Vector2 worldMapPos{0.0, 0.0};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        //movement
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            //set worldMapPos = worldMapPos - direction
            worldMapPos = Vector2Subtract(worldMapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }
        
        DrawTextureEx(worldMap, worldMapPos, 0, 6, WHITE);


        EndDrawing();
    }
    CloseWindow();
}