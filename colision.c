#include "raylib.h"
#include "colision.h"
#include "player.h"

#define G 2150
#define PlayerJumpSpeed 970.0f //1500
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

void ColisaoSupInf(Player *player, EnvItem *envItems, int envItemsLength, Texture2D **Texture, float delta, int *colision){
    (*colision) = 0;
    for (int i = 0; i < envItemsLength; i++){
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&                    // Intervalo do x
            ei->rect.x + ei->rect.width >= p->x &&  //
            ei->rect.y >= p->y &&                       // Personagem em cima do retangulo
            ei->rect.y < p->y + player->speed * delta) // Proxima altura do personagem abaixo do retangulo
        {
            (*colision) = 1;
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
}

void ColisaoLateral(Player *player, EnvItem *envItems, int envItemsLength, Texture2D **Texture, float delta, float *FrameWidth, short *LastSide){
    for (int i = 0; i < envItemsLength; i++){
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (*LastSide == Left && 
            ei->rect.x + ei->rect.width <= p->x - (*FrameWidth)/3 + PlayerHorzSpeed * delta &&
            ei->rect.x + ei->rect.width > p->x - (*FrameWidth)/3 &&
            ((p->y > ei->rect.y && p->y - (*Texture)->height < ei->rect.y) || // Metade-Cima Retangulo
            (p->y - (*Texture)->height > ei->rect.y && p->y < ei->rect.y + ei->rect.height) || // Todo Entre-Retangulo
            (p->y - (*Texture)->height < ei->rect.y + ei->rect.height && p->y > ei->rect.y + ei->rect.height))) // Metade-Baixo Retangulo
        {

                p->x += PlayerHorzSpeed * delta;

        }

        else if (*LastSide == Right && 
            ei->rect.x >= p->x + (*FrameWidth)/4 - PlayerHorzSpeed * delta &&
            ei->rect.x < p->x + (*FrameWidth)/4 &&
            ((p->y > ei->rect.y && p->y - (*Texture)->height < ei->rect.y) || // Metade-Cima Retangulo
            (p->y - (*Texture)->height > ei->rect.y && p->y < ei->rect.y + ei->rect.height) || // Todo Entre-Retangulo
            (p->y - (*Texture)->height < ei->rect.y + ei->rect.height && p->y > ei->rect.y + ei->rect.height))) // Metade-Baixo Retangulo
        {
            p->x -= PlayerHorzSpeed * delta;
        } 
    }
}

void HitObstacle(Player *player, float delta, int colision){
    if (!colision){
        player->position.y += player->speed * delta;
        player->speed += G * delta;
        player->canJump = false;
    }
    else
        player->canJump = true;
}