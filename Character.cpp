#include "Character.h"
#include "raymath.h"


Character::Character(int windowWidth, int windowHeight)
{
    mSingleTextureWidth = static_cast<float>(mTexture.width) / mScale;
    mSingleTextureHeight = static_cast<float>(mTexture.height);

    mScreenPos = {
        (static_cast<float>(windowWidth) / 2.0f) - mScale * (0.5f * mSingleTextureWidth),
        (static_cast<float>(windowHeight) / 2.0f) - mScale * (0.5f * mSingleTextureHeight)};
}

void Character::Tick(float deltaTime)
{
    mWorldPosLastFrame = mWorldPos;
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

    // Drawing knight
    Rectangle knight_source_rect{mFrame * mSingleTextureWidth, 0.f, mRightLeft * mSingleTextureWidth, mSingleTextureHeight};    // knight source rectangle
    Rectangle knight_dest_pos{mScreenPos.x, mScreenPos.y, (mScale * mSingleTextureWidth), (mScale * mSingleTextureHeight)};     // knight destination is middle of screen
    DrawTexturePro(mTexture, knight_source_rect, knight_dest_pos, Vector2{}, 0, WHITE);                                         // drawing knight to the middle of the screen with origin in top left corner (0,0)
    
}

void Character::UndoMovement()
{
    mWorldPos = mWorldPosLastFrame;
}
