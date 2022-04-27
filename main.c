#include "raylib.h"
#include "player.h"
#include "colision.h"
//#include "raymath.h"

#define G 800
#define Right 1
#define Left 0

int main(void){

    InitWindow(GetScreenWidth(), GetScreenHeight(), "raylib [core] example - 2d camera");

    ToggleFullscreen();

    Player player = { 0 };
    player.position = (Vector2){ 400, 400 };
    player.speed = 0;
    player.canJump = false;
    EnvItem envItems[] = {
        {{ 0, 0, 1920, 1080 }, 0, LIGHTGRAY },
        {{ 0, 400, 1920, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);


    Texture2D jogadorRunLeft = LoadTexture("assets\\Personagem\\RunLeft.png");

    Texture2D jogadorRunRight = LoadTexture("assets\\Personagem\\RunRight.png");

    Texture2D jogadorStandLeft = LoadTexture("assets\\Personagem\\StandLeft.png");

    Texture2D jogadorStandRight = LoadTexture("assets\\Personagem\\StandRight.png");


    Texture2D *WhichTexture;
    *WhichTexture = jogadorStandLeft;

    Texture2D *LastMove;
    float FrameWidth;
    int MaxFrames;

    int CurrentFrame = 0;
    float Timer = 0.0f;
    short LastSide = Left;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){

        float deltaTime = GetFrameTime();

        int detector = 0;

        LastMove = WhichTexture;

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime, &detector, &WhichTexture, jogadorRunLeft, jogadorRunRight, 
                    jogadorStandLeft, jogadorStandRight, &FrameWidth, &MaxFrames, &LastSide);

        if (LastMove != WhichTexture)
            CurrentFrame = 0;

        if (detector == 1){
        Timer += GetFrameTime();

        if (Timer >= 0.1f){
            Timer = 0.0f;
            CurrentFrame += 1;
        }

        CurrentFrame = CurrentFrame % MaxFrames;

        }

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

                for (int i = 0; i < envItemsLength; i++)
                    DrawRectangleRec(envItems[i].rect, envItems[i].color);

                Rectangle playerRect = {FrameWidth * CurrentFrame , 0, FrameWidth , WhichTexture->height };
                
                Vector2 positionRec = {player.position.x - (FrameWidth/2), player.position.y - WhichTexture->height};

                DrawTextureRec(*WhichTexture, playerRect, positionRec, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    UnloadTexture(jogadorRunLeft);
    UnloadTexture(jogadorRunRight);
    UnloadTexture(jogadorStandLeft);
    UnloadTexture(jogadorStandRight);

    CloseWindow();
}