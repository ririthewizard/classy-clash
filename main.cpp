#include <raylib.h>
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return mWorldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D mTexture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D mIdle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D mRun{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 mScreenPos;
    Vector2 mWorldPos;
    // 1 : facing right, -1 : facing left
    float mRightLeft{1.f};
    // animation variables
    float mRunningTime{};
    int mFrame{};
    const int mMaxFrames{6};
    const float mUpdateTime{1.f / 12.f};
    const float speed{6.f};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    mScreenPos = {
        ((float)winWidth / 2.0f) - 6.0f * (0.5f * (float)mTexture.width / 6.0f),
        ((float)winHeight / 2.0f) - 6.0f * (0.5f * (float)mTexture.height)};
};

void Character::tick(float deltaTime)
{
    Vector2 direction{};

    // moving map opposite of key press to simulate character movement
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set mWorldPos = mWorldPos + direction
        mWorldPos = Vector2Add(mWorldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // ternary for setting our rightLeft value based on which direction we are moving(i.e facing)
        direction.x < 0.f ? mRightLeft = -1.f : mRightLeft = 1.f;
        mTexture = mRun;
    }
    else
    {
        mTexture = mIdle;
    }

    mRunningTime += deltaTime;
    if (mRunningTime >= mUpdateTime)
    {
        mFrame++;
        mRunningTime = 0.f;
        if (mFrame >= mMaxFrames)
            mFrame = 0;
    }
};

int main()
{
    int window_dimensions[2]{1024, 1024}; // width, height

    InitWindow(window_dimensions[0], window_dimensions[1], "Riley's Top Down");

    Texture2D world_map = LoadTexture("nature_tileset/WorldMap.png");

    float speed{6.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    // knight running texture
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    // knight idle texture
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");

    float single_knight_width = (float)knight.width / 6.f; // the width of a single knight sprite as a float
    float single_knight_height = (float)knight.height;     // the height of a single knight sprite as a float

    Vector2 knightPos{
        ((float)window_dimensions[0] / 2.0f) - 6.0f * (0.5f * (float)knight.width / 6.0f),
        ((float)window_dimensions[1] / 2.0f) - 6.0f * (0.5f * (float)knight.height)};

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};

    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};

    Vector2 world_map_pos{0.0, 0.0};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        // moving map opposite of key press to simulate character movement
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            // set world_map_pos = world_map_pos - direction
            world_map_pos = Vector2Subtract(world_map_pos, Vector2Scale(Vector2Normalize(direction), speed));
            // ternary for setting our rightLeft value based on which direction we are moving(i.e facing)
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }

        // Drawing the world map
        DrawTextureEx(world_map, world_map_pos, 0, 6, WHITE);

        // update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame >= maxFrames)
                frame = 0;
        }

        // Drawing knight
        Rectangle knight_source_rect{frame * single_knight_width, 0.f, rightLeft * single_knight_width, single_knight_height}; // knight source rectangle
        Rectangle knight_dest_pos{knightPos.x, knightPos.y, (6.f * single_knight_width), (6.f * single_knight_height)};        // knight destination is middle of screen
        DrawTexturePro(knight, knight_source_rect, knight_dest_pos, Vector2{}, 0, WHITE);                                      // drawing knight to the middle of the screen with origin in top left corner (0,0)

        EndDrawing();
    }
    CloseWindow();
}