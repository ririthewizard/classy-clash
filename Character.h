#include <raylib.h>

class Character
{
public:
    Character();
    Vector2 getWorldPos() { return mWorldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void Tick(float deltaTime);
    void UndoMovement();

private:
    Texture2D mTexture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D mIdle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D mRun{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 mScreenPos{};
    Vector2 mWorldPos{};
    Vector2 mWorldPosLastFrame{};
    // 1 : facing right, -1 : facing left
    float mRightLeft{1.f};
    // animation variables
    float mRunningTime{};
    int mFrame{};
    int mMaxFrames{6};
    float mUpdateTime{1.f / 12.f};
    float speed{6.f};
    float mSingleTextureWidth{};
    float mSingleTextureHeight{};
};