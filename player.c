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

void CreatePlayer(Player *player){
    player->position = (Vector2){1740, 535};
    player->speed = 0;
    player->canJump = true;
    player->FrameWidth = 0;
    player->CurrentFrame = 0;
    player->MaxFrames = 0;
    player->LastSide = 0;

    player->PlayerTextures[0] = LoadTexture("assets/Personagem/RunLeft.png");
    player->PlayerTextures[1] = LoadTexture("assets/Personagem/RunRight.png");
    player->PlayerTextures[2] = LoadTexture("assets/Personagem/StandLeft.png");
    player->PlayerTextures[3] = LoadTexture("assets/Personagem/StandRight.png"); 

    player->CurrentTexture = player->PlayerTextures[2];
}


void MovePlayer(Player *player, float delta)
{

    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->speed = -PlayerJumpSpeed;
        player->canJump = false;
    }
    
    if (IsKeyDown(KEY_A)){
        player->position.x -= PlayerHorzSpeed * delta;
        player->LastSide = Left;
        player->CurrentTexture = player->PlayerTextures[RunLeft];
        player->FrameWidth = player->PlayerTextures[RunLeft].width / 8.0;
        player->MaxFrames = (int) (player->PlayerTextures[RunLeft].width / (int) player->FrameWidth);
    }

    if (IsKeyDown(KEY_D)){
        player->position.x += PlayerHorzSpeed * delta;
        player->LastSide = Right;
        player->CurrentTexture = player->PlayerTextures[RunRight];
        player->FrameWidth = player->PlayerTextures[RunRight].width / 8.0;
        player->MaxFrames = (int) (player->PlayerTextures[RunRight].width / (int) player->FrameWidth);
    }

    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && player->canJump){
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
}