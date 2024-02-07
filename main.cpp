#include "raylib.h"
#include "raymath.h"
int main()
{
    const int windowWidth{2000};
    const int windowHeight{2000};
    InitWindow(windowWidth, windowHeight, "My Game");

    Texture2D map = LoadTexture("C:/Users/Shadow/CLionProjects/RaylibProject2/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0, 0};
    SetTargetFPS(60);

    Texture2D knight = LoadTexture("C:/Users/Shadow/CLionProjects/RaylibProject2/characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
            (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width/6),
        (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)
    };
    float speed{4};
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);


        Vector2 direction{};
        if(IsKeyDown(KEY_A))direction.x -= 1.0;
        if(IsKeyDown(KEY_D))direction.x += 1.0;
        if(IsKeyDown(KEY_W))direction.y -= 1.0;
        if(IsKeyDown(KEY_S))direction.y += 1.0;
        if(Vector2Length(direction)!= 0.0)
        {
            // set mappos
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }
        DrawTextureEx(map, mapPos, 0.0, 5, WHITE);
        Rectangle source{0.f, 0.f, (float)knight.width/6.0f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        Vector2 origin{};
        float rotation{};
        DrawTexturePro(knight, source, dest , origin, rotation, WHITE);
        EndDrawing();
    }
    CloseWindow();
}
