#include <raylib.h>
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    int window_dimensions[2]{1024, 1024}; // width, height

    InitWindow(window_dimensions[0], window_dimensions[1], "Riley's Top Down");

    Texture2D world_map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 world_map_pos{0.0, 0.0};
    const float map_scale{6.0f};

    Character knight(window_dimensions[0], window_dimensions[1]);
    
    Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset/Rock.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        world_map_pos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Drawing the world map
        DrawTextureEx(world_map, world_map_pos, 0, map_scale, WHITE);

        rock.Render(knight.getWorldPos());

        knight.Tick(GetFrameTime());
        //checking map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + window_dimensions[0] > world_map.width * map_scale ||
            knight.getWorldPos().y + window_dimensions[1] > world_map.height * map_scale)
        {
            knight.UndoMovement();
        }

        EndDrawing();
    }
    CloseWindow();
}