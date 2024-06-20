#include <raylib.h>

int main()
{
    int windowDimensions[2]{1024, 1024}; //width, height

    InitWindow(windowDimensions[0], windowDimensions[1], "Riley's Top Down");

    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 worldMapPos{0.0, 0.0};
        DrawTextureEx(worldMap, worldMapPos, 0, 4, WHITE);


        EndDrawing();
    }
    CloseWindow();
}