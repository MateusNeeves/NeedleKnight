#include "raylib.h"
#include "player.h"
#include <stdlib.h>

#define PlayerJumpSpeed 1050.0f //1050
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

#define RunLeft 0
#define RunRight 1
#define StandLeft 2
#define StandRight 3
#define JumpLeft 4
#define JumpRight 5
#define AttackLeft 6
#define AttackRight 7
#define DeathLeft 8
#define DeathRight 9

void CreatePlayer(Player *player){
    player->position = (Vector2){1540, 545};
    player->speed = 0; 
    player->canJump[0] = true;
    player->canJump[1] = true;
    player->DoubleJump = false;
    player->attacking = false;

    player->FrameWidth = 0;
    player->CurrentFrame = 0;
    player->MaxFrames = 0;
    player->LastSide = Left;

    player->PlayerTextures[RunLeft] = LoadTexture("Assets/Personagem/RunLeft.png");
    player->PlayerTextures[RunRight] = LoadTexture("Assets/Personagem/RunRight.png");
    player->PlayerTextures[StandLeft] = LoadTexture("Assets/Personagem/StandLeft.png");
    player->PlayerTextures[StandRight] = LoadTexture("Assets/Personagem/StandRight.png"); 
    player->PlayerTextures[JumpLeft] = LoadTexture("Assets/Personagem/JumpLeft.png");
    player->PlayerTextures[JumpRight] = LoadTexture("Assets/Personagem/JumpRight.png");
    player->PlayerTextures[AttackLeft] = LoadTexture("Assets/Personagem/AttackLeft.png");
    player->PlayerTextures[AttackRight] = LoadTexture("Assets/Personagem/AttackRight.png");
    player->PlayerTextures[DeathLeft] = LoadTexture("Assets/Personagem/DeathLeft.png");
    player->PlayerTextures[DeathRight] = LoadTexture("Assets/Personagem/DeathRight.png");

    //Ao adicionar, alterar qtd na main.c e na player.h

    player->CurrentTexture = player->PlayerTextures[2];

    player->MaxLife = 10;
    player->CurrentLife = 10;
}


void MovePlayer(Player **player, float delta)
{
    //Animacao Pulando

    if (IsKeyPressed(KEY_SPACE) && (*player)->canJump[0] && !(*player)->attacking){
        (*player)->speed = -PlayerJumpSpeed;
        (*player)->canJump[0] = false;
        (*player)->CurrentFrame = 0;
    }
    else if (IsKeyPressed(KEY_SPACE) && (*player)->DoubleJump && !(*player)->canJump[0] && (*player)->canJump[1] && !(*player)->attacking){
        (*player)->speed = -(PlayerJumpSpeed/1.15);
        (*player)->canJump[1] = false;
        (*player)->CurrentFrame = 0;
    }

    
    //Animacao Andando pra Esquerda e Pulando pra Esquerda

    if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && !(*player)->attacking){
        (*player)->position.x -= PlayerHorzSpeed * delta;
        (*player)->LastSide = Left;

        if ((*player)->canJump[0]){
            (*player)->CurrentTexture = (*player)->PlayerTextures[RunLeft];
            (*player)->FrameWidth = (*player)->PlayerTextures[RunLeft].width / 8.0;
            (*player)->MaxFrames = (int) ((*player)->PlayerTextures[RunLeft].width / (int) (*player)->FrameWidth);
        }

        else{
            (*player)->CurrentTexture = (*player)->PlayerTextures[JumpLeft];
            (*player)->FrameWidth = (*player)->PlayerTextures[JumpLeft].width / 9.0;
            (*player)->MaxFrames = (int) ((*player)->PlayerTextures[JumpLeft].width / (int) (*player)->FrameWidth);
        }
    }

    //Animacao Andando pra Direita e Pulando pra Direita

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && !(*player)->attacking){
        (*player)->position.x += PlayerHorzSpeed * delta;
        (*player)->LastSide = Right;

        if ((*player)->canJump[0]){
            (*player)->CurrentTexture = (*player)->PlayerTextures[RunRight];
            (*player)->FrameWidth = (*player)->PlayerTextures[RunRight].width / 8.0;
            (*player)->MaxFrames = (int) ((*player)->PlayerTextures[RunRight].width / (int) (*player)->FrameWidth);
        }

        else{
            (*player)->CurrentTexture = (*player)->PlayerTextures[JumpRight];
            (*player)->FrameWidth = (*player)->PlayerTextures[JumpRight].width / 9.0;
            (*player)->MaxFrames = (int) ((*player)->PlayerTextures[JumpRight].width / (int) (*player)->FrameWidth);
        }
    }

    //Animacao Parado e Pulando Parado

    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_D) && IsKeyUp(KEY_RIGHT) && !(*player)->attacking)
    {
        if ((*player)->canJump[0]){
            if ((*player)->LastSide == Left){
                (*player)->CurrentTexture = (*player)->PlayerTextures[StandLeft];
                (*player)->FrameWidth = (*player)->PlayerTextures[StandLeft].width / 6.0;
                (*player)->MaxFrames = (int) ((*player)->PlayerTextures[StandLeft].width / (int) (*player)->FrameWidth);
            }
            else{
                (*player)->CurrentTexture = (*player)->PlayerTextures[StandRight];
                (*player)->FrameWidth = (*player)->PlayerTextures[StandRight].width / 6.0;
                (*player)->MaxFrames = (int) ((*player)->PlayerTextures[StandRight].width / (int) (*player)->FrameWidth);
            } 
        }

        else{
            if ((*player)->LastSide == Left){
                (*player)->CurrentTexture = (*player)->PlayerTextures[JumpLeft];
                (*player)->FrameWidth = (*player)->PlayerTextures[JumpLeft].width / 9.0;
                (*player)->MaxFrames = (int) ((*player)->PlayerTextures[JumpLeft].width / (int) (*player)->FrameWidth);
            }

            else{
                (*player)->CurrentTexture = (*player)->PlayerTextures[JumpRight];
                (*player)->FrameWidth = (*player)->PlayerTextures[JumpRight].width / 9.0;
                (*player)->MaxFrames = (int) ((*player)->PlayerTextures[JumpRight].width / (int) (*player)->FrameWidth);
            }
        }
    }

    // Animacao de Ataque

    if (IsKeyDown(KEY_Z) && (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && (*player)->canJump[0]){
        (*player)->position.x -= PlayerHorzSpeed * delta;
        (*player)->attacking = true;
        (*player)->CurrentTexture = (*player)->PlayerTextures[AttackLeft];
        (*player)->FrameWidth = (*player)->PlayerTextures[AttackLeft].width / 3.0;
        (*player)->MaxFrames = (int) ((*player)->PlayerTextures[AttackLeft].width / (int) (*player)->FrameWidth);
    } 
    
    else if (IsKeyDown(KEY_Z) && (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && (*player)->canJump[0]){
        (*player)->position.x += PlayerHorzSpeed * delta;
        (*player)->attacking = true;
        (*player)->CurrentTexture = (*player)->PlayerTextures[AttackRight];
        (*player)->FrameWidth = (*player)->PlayerTextures[AttackRight].width / 3.0;
        (*player)->MaxFrames = (int) ((*player)->PlayerTextures[AttackRight].width / (int) (*player)->FrameWidth);
    }

    else if (IsKeyDown(KEY_Z) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT) && 
            !(*player)->attacking && (*player)->canJump[0])
    {
        if ((*player)->LastSide == Left){
            (*player)->attacking = true;
            (*player)->CurrentTexture = (*player)->PlayerTextures[AttackLeft];
            (*player)->FrameWidth = (*player)->PlayerTextures[AttackLeft].width / 3.0;
            (*player)->MaxFrames = (int) ((*player)->PlayerTextures[AttackLeft].width / (int) (*player)->FrameWidth);
        }
        else{
            (*player)->attacking = true;
            (*player)->CurrentTexture = (*player)->PlayerTextures[AttackRight];
            (*player)->FrameWidth = (*player)->PlayerTextures[AttackRight].width / 3.0;
            (*player)->MaxFrames = (int) ((*player)->PlayerTextures[AttackRight].width / (int) (*player)->FrameWidth);
        }
    }
}