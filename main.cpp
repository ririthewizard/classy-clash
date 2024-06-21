#include <raylib.h>
#include "raymath.h"

int main()
{
    int windowDimensions[2]{1024, 1024}; //width, height

    InitWindow(windowDimensions[0], windowDimensions[1], "Riley's Top Down");

    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");

    float speed{6.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos
    {
        ((float)windowDimensions[0] / 2.0f) - 6.0f * (0.5f * (float)knight.width / 6.0f),
        ((float)windowDimensions[1] / 2.0f) - 6.0f * (0.5f * (float)knight.height)
    };

    Vector2 worldMapPos{0.0, 0.0};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        // moving map opposite of key press to simulate character movement
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            //set worldMapPos = worldMapPos - direction
            worldMapPos = Vector2Subtract(worldMapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }
        
        //Drawing the world map
        DrawTextureEx(worldMap, worldMapPos, 0, 6, WHITE);

        //Drawing knight
        Rectangle knightSourceRect{0.f, 0.f, (float)knight.width / 6.f, (float)knight.height};                                  //knight source rectangle
        Rectangle knightDestPos{knightPos.x, knightPos.y, (6.f * (float)knight.width / 6.f), (6.f * (float)knight.height)};     //knight destination is middle of screen
        DrawTexturePro(knight, knightSourceRect, knightDestPos, Vector2{}, 0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}