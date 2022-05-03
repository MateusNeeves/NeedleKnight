#include "raylib.h"
#include "player.h"

#define G 2150
#define PlayerJumpSpeed 970.0f //1500
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

void MovePlayer(Player *player, float delta, Texture2D **Texture, Texture2D jogadorRunLeft, Texture2D jogadorRunRight, 
                  Texture2D jogadorStandLeft, Texture2D jogadorStandRight, float *FrameWidth, int *MaxFrames, short *LastSide)
{

    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->speed = -PlayerJumpSpeed;
        player->canJump = false;
    }
    
    if (IsKeyDown(KEY_A)){
        player->position.x -= PlayerHorzSpeed * delta;
        *LastSide = Left;
        *(*Texture) = jogadorRunLeft;
        *FrameWidth = jogadorRunLeft.width / 8.0;
        *MaxFrames = (int) (jogadorRunLeft.width / (int) * FrameWidth);
    }

    if (IsKeyDown(KEY_D)){
        player->position.x += PlayerHorzSpeed * delta;
        *LastSide = Right;
        *(*Texture) = jogadorRunRight;
        *FrameWidth = jogadorRunRight.width / 8.0;
        *MaxFrames = (int) (jogadorRunRight.width / (int) * FrameWidth);
    }

    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && player->canJump){
        if (*LastSide == Left){
            *(*Texture) = jogadorStandLeft;
            *FrameWidth = jogadorStandLeft.width / 6.0;
            *MaxFrames = (int) (jogadorStandLeft.width / (int) * FrameWidth);
        }
        else{
            *(*Texture) = jogadorStandRight;
            *FrameWidth = jogadorStandRight.width / 6.0;
            *MaxFrames = (int) (jogadorStandRight.width / (int) * FrameWidth);
        }
    }
}