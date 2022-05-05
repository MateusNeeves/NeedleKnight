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

void CreatePlayer(Player *player){
    player->position = (Vector2){1740, 535};
    player->speed = 0;
    player->canJump = true;
    player->FrameWidth = 0;
    player->CurrentFrame = 0;
    player->MaxFrames = 0;
    player->LastSide = 0;

    player->PlayerTextures[RunLeft] = LoadTexture("assets/Personagem/RunLeft.png");
    player->PlayerTextures[RunRight] = LoadTexture("assets/Personagem/RunRight.png");
    player->PlayerTextures[StandLeft] = LoadTexture("assets/Personagem/StandLeft.png");
    player->PlayerTextures[StandRight] = LoadTexture("assets/Personagem/StandRight.png"); 
    player->PlayerTextures[JumpLeft] = LoadTexture("assets/Personagem/JumpLeft.png");
    player->PlayerTextures[JumpRight] = LoadTexture("assets/Personagem/JumpRight.png");

    player->CurrentTexture = player->PlayerTextures[2];
}


void MovePlayer(Player *player, float delta, int *colision)
{

    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->speed = -PlayerJumpSpeed;
        player->canJump = false;
        player->CurrentFrame = 0;
        (*colision) = 0;
    }
    
    if (IsKeyDown(KEY_A)){
        player->position.x -= PlayerHorzSpeed * delta;
        player->LastSide = Left;

        if (player->canJump){
            player->CurrentTexture = player->PlayerTextures[RunLeft];
            player->FrameWidth = player->PlayerTextures[RunLeft].width / 8.0;
            player->MaxFrames = (int) (player->PlayerTextures[RunLeft].width / (int) player->FrameWidth);
        }

        else{
            player->CurrentTexture = player->PlayerTextures[JumpLeft];
            player->FrameWidth = player->PlayerTextures[JumpLeft].width / 9.0;
            player->MaxFrames = (int) (player->PlayerTextures[JumpLeft].width / (int) player->FrameWidth);
        }
    }

    if (IsKeyDown(KEY_D)){
        player->position.x += PlayerHorzSpeed * delta;
        player->LastSide = Right;

        if (player->canJump){
            player->CurrentTexture = player->PlayerTextures[RunRight];
            player->FrameWidth = player->PlayerTextures[RunRight].width / 8.0;
            player->MaxFrames = (int) (player->PlayerTextures[RunRight].width / (int) player->FrameWidth);
        }

        else{
            player->CurrentTexture = player->PlayerTextures[JumpRight];
            player->FrameWidth = player->PlayerTextures[JumpRight].width / 9.0;
            player->MaxFrames = (int) (player->PlayerTextures[JumpRight].width / (int) player->FrameWidth);
        }
    }

    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D)){
        if (player->canJump){
            if (player->LastSide == Left){
                player->CurrentTexture = player->PlayerTextures[StandLeft];
                player->FrameWidth = player->PlayerTextures[StandLeft].width / 6.0;
                player->MaxFrames = (int) (player->PlayerTextures[StandLeft].width / (int) player->FrameWidth);
            }
            else{
                player->CurrentTexture = player->PlayerTextures[StandRight];
                player->FrameWidth = player->PlayerTextures[StandRight].width / 6.0;
                player->MaxFrames = (int) (player->PlayerTextures[StandRight].width / (int) player->FrameWidth);
            } 
        }

        else{
            if (player->LastSide == Left){
                player->CurrentTexture = player->PlayerTextures[JumpLeft];
                player->FrameWidth = player->PlayerTextures[JumpLeft].width / 9.0;
                player->MaxFrames = (int) (player->PlayerTextures[JumpLeft].width / (int) player->FrameWidth);
            }

            else{
                player->CurrentTexture = player->PlayerTextures[JumpRight];
                player->FrameWidth = player->PlayerTextures[JumpRight].width / 9.0;
                player->MaxFrames = (int) (player->PlayerTextures[JumpRight].width / (int) player->FrameWidth);
            }
        }
    }
}