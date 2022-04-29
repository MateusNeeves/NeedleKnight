#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "player.h"

#define G 2150
#define PlayerJumpSpeed 950.0f //1500
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta, Texture2D **Texture, Texture2D jogadorRunLeft, 
                  Texture2D jogadorRunRight, Texture2D jogadorStandLeft, Texture2D jogadorStandRight, float *FrameWidth, int *MaxFrames, short *LastSide)
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
    
    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
         if (ei->blocking &&
            ei->rect.x <= p->x &&                    // Intervalo do x
            ei->rect.x + ei->rect.width >= p->x &&  //
            ei->rect.y >= p->y &&                       // Personagem em cima do retangulo
            ei->rect.y < p->y + player->speed * delta) // Proxima altura do personagem abaixo do retangulo
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        } 

        else if (ei->blocking &&
            ei->rect.x <= p->x &&                    // Intervalo do x
            ei->rect.x + ei->rect.width >= p->x &&  //
            ei->rect.y + ei->rect.height <= p->y - (*Texture)->height &&  // Personagem em baixo do retangulo
            ei->rect.y + ei->rect.height > p->y - (*Texture)->height + player->speed * delta) // Proxima altura do personagem em cima do retangulo
        {
            player->speed = 0.0f;
            p->y = ei->rect.y + ei->rect.height + (*Texture)->height;
        } 
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed * delta;
        player->speed += G * delta;
        player->canJump = false;
    }
    else
        player->canJump = true;
}