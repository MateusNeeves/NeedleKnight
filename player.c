#include <stdio.h>
#include "raylib.h"
#include "player.h"

#define G 800
#define PlayerJumpSpeed 400.0f
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta, int *detector, Texture2D **Texture, Texture2D jogadorRunLeft, 
                  Texture2D jogadorRunRight, Texture2D jogadorStandLeft, Texture2D jogadorStandRight, float *FrameWidth, int *MaxFrames, short *LastSide)
{
    if (IsKeyDown(KEY_A)){
        player->position.x -= PlayerHorzSpeed * delta;
        *(*Texture) = jogadorRunLeft;
        *FrameWidth = jogadorRunLeft.width / 8.0;
        *MaxFrames = (int) (jogadorRunLeft.width / (int) * FrameWidth);
        *detector = 1;
        *LastSide = Left;
    }
    else if (IsKeyDown(KEY_D)){
        player->position.x += PlayerHorzSpeed * delta;
        *(*Texture) = jogadorRunRight;
        *FrameWidth = jogadorRunRight.width / 8.0;
        *MaxFrames = (int) (jogadorRunRight.width / (int) * FrameWidth);
        *detector = 1;
        *LastSide = Right;
    }
    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->speed = -PlayerJumpSpeed;
        player->canJump = false;
    }
    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && player->canJump == true){
        if (*LastSide == Left){
            *(*Texture) = jogadorStandLeft;
            *FrameWidth = jogadorStandLeft.width / 6.0;
            *MaxFrames = (int) (jogadorStandLeft.width / (int) * FrameWidth);
            *detector = 1;
        }
        else{
            *(*Texture) = jogadorStandRight;
            *FrameWidth = jogadorStandRight.width / 6.0;
            *MaxFrames = (int) (jogadorStandRight.width / (int) * FrameWidth);
            *detector = 1;
        }
    }

    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed*delta)
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;
}