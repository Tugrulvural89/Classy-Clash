#include "raylib.h"
#include "raymath.h"

class Character
{
private:
    Vector2 screenPos{};
    Vector2 worldPos{};
    Texture2D texture{LoadTexture("C:/Users/Shadow/CLionProjects/RaylibProject2/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("C:/Users/Shadow/CLionProjects/RaylibProject2/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("C:/Users/Shadow/CLionProjects/RaylibProject2/characters/knight_run_spritesheet.png")};
    // 1 right -1 left
    float rightLeft{1.0f};

    // animation character
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.0f / 12.0f};

    const float speed{4.0f};
public:
    Vector2 getWorldPos(){return worldPos;}
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width/6),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height),
    };

}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if(IsKeyDown(KEY_A))direction.x -= 1.0;
    if(IsKeyDown(KEY_D))direction.x += 1.0;
    if(IsKeyDown(KEY_W))direction.y -= 1.0;
    if(IsKeyDown(KEY_S))direction.y += 1.0;
    if(Vector2Length(direction)!= 0.0)
    {
        // set mappos
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x <= 0.f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;

    } else
    {
        texture = idle;
    }

    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        runningTime = 0.0f;
        frame++;
        if(frame >= maxFrames)frame = 0;
    }
    Rectangle source{frame * (float)texture.width/6, 0.f, rightLeft * (float)texture.width/6.0f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width/6.0f, 4.0f * (float)texture.height};
    Vector2 origin{};
    float rotation{};
    DrawTexturePro(texture, source, dest , origin, rotation, WHITE);

}
int main()
{
    const int windowWidth{2000};
    const int windowHeight{2000};
    InitWindow(windowWidth, windowHeight, "My Game");

    Texture2D map = LoadTexture("C:/Users/Shadow/CLionProjects/RaylibProject2/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0, 0};
    SetTargetFPS(60);


    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);


    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, 5, WHITE);
        knight.tick(GetFrameTime());
        EndDrawing();
    }
    CloseWindow();
}
