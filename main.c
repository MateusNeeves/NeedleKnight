#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "player.h"
#include "colision.h"

#define G 2150
#define Right 1
#define Left 0

int main(void){

    InitWindow(GetScreenWidth(), GetScreenHeight(), "BACKUP");

    ToggleFullscreen();

    Player player = { 0 };
    player.position = (Vector2){ 1740, 535 };
    player.speed = 0;
    player.canJump = true;
    EnvItem envItems[] = {
        {{0, 350, 540, 210}, 1}, // Plataforma Cima-Esquerda
        {{0, 0, 1920, 100}, 1}, //Teto
        {{0, 936, 1920, 140}, 1}, //Chao Baixo //
        {{1410, 545, 510, 225}, 1}, // Plataforma Direita-Cima
        {{780, 550, 215, 40}, 1}, // Plataforma Meio-Esquerda
        {{1060, 720, 170, 50}, 1}, // Plataforma Meio-Direita
        {{0, 500, 50, 600}, 1}, // Parede Esquerda
        //{{1905, 100, 25, 535}, 1} // Parede Direita
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);


    Texture2D jogadorRunLeft = LoadTexture("assets\\Personagem\\RunLeft.png");

    Texture2D jogadorRunRight = LoadTexture("assets\\Personagem\\RunRight.png");

    Texture2D jogadorStandLeft = LoadTexture("assets\\Personagem\\StandLeft.png");

    Texture2D jogadorStandRight = LoadTexture("assets\\Personagem\\StandRight.png");

    Texture2D mapaInicio = LoadTexture("assets\\Mapa\\MapaInicio.png");


    Texture2D *WhichTexture;
    *WhichTexture = jogadorStandLeft;

    Texture2D *LastMove;
    float FrameWidth;
    int MaxFrames;
    int CurrentFrame = 0;
    float Timer = 0.0f;
    short LastSide = Left;
    int colision;

    float deltaTime;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){

        deltaTime = GetFrameTime();
        LastMove = WhichTexture;

        MovePlayer(&player, deltaTime, &WhichTexture, jogadorRunLeft, jogadorRunRight, 
                    jogadorStandLeft, jogadorStandRight, &FrameWidth, &MaxFrames, &LastSide);

        ColisaoSupInf(&player, envItems, envItemsLength, &WhichTexture, deltaTime, &colision);

        ColisaoLateral(&player, envItems, envItemsLength, &WhichTexture, deltaTime, &FrameWidth, &LastSide);

        HitObstacle(&player, deltaTime, colision);

        if (LastMove != WhichTexture)
            CurrentFrame = 0;

        Timer += GetFrameTime();

        if (Timer >= 0.1f){
            Timer = 0.0f;
            CurrentFrame += 1;
        }

        CurrentFrame = CurrentFrame % MaxFrames;

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

                Rectangle fundo = {0 , 0, mapaInicio.width , mapaInicio.height };

                Vector2 posFundo = {0, 0};
                
                DrawTextureRec(mapaInicio, fundo, posFundo, WHITE);

      /*           for (int i = 0; i < envItemsLength; i++)
                    DrawRectangleRec(envItems[i].rect, GRAY);   */

                Rectangle textureRec = {FrameWidth * CurrentFrame , 0, FrameWidth , WhichTexture->height};
                
                Vector2 position = {player.position.x - (FrameWidth/2), player.position.y - WhichTexture->height};

                DrawTextureRec(*WhichTexture, textureRec, position, WHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    UnloadTexture(jogadorRunLeft);
    UnloadTexture(jogadorRunRight);
    UnloadTexture(jogadorStandLeft);
    UnloadTexture(jogadorStandRight);
    UnloadTexture(mapaInicio);

    CloseWindow();
}