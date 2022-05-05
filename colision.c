#include "raylib.h"
#include "colision.h"
#include "player.h"
#include "room.h"

#define G 2500 // 2500
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

void ColisaoSupInf(Player *player, Room rooms, float delta, int *colision){

    (*colision) = 0;
    for (int i = 0; i < rooms.platformNmbr ; i++){
        Rectangle platform = rooms.platforms[i];
        Vector2 *p = &(player->position);

        if (platform.x <= p->x &&                    // Intervalo do x
            platform.x + platform.width >= p->x &&  //
            platform.y >= p->y &&                       // Personagem em cima do retangulo
            platform.y <= p->y + player->speed * delta) // Proxima altura do personagem abaixo do retangulo
        {
            (*colision) = 1;
            player->speed = 0.0f;
            p->y = platform.y;
        } 
            

        else if (platform.x <= p->x &&                    // Intervalo do x
            platform.x + platform.width >= p->x &&  //
            platform.y + platform.height <= p->y - player->CurrentTexture.height &&  // Personagem em baixo do retangulo
            platform.y + platform.height > p->y - player->CurrentTexture.height + player->speed * delta) // Proxima altura do personagem em cima do retangulo
        {
            player->speed = 0.0f;
            p->y = platform.y + platform.height + player->CurrentTexture.height;
        }
    }

}

void ColisaoLateral(Player *player, Room rooms, float delta){
    for (int i = 0; i < rooms.platformNmbr ; i++){
        Rectangle platform = rooms.platforms[i];
        Vector2 *p = &(player->position);

        if (player->LastSide == Left && 
            platform.x + platform.width > p->x - (player->FrameWidth)/3 &&
            platform.x + platform.width < p->x - (player->FrameWidth)/3 + PlayerHorzSpeed * delta * 5 &&
            ((p->y > platform.y && p->y - player->CurrentTexture.height < platform.y) || // Metade-Cima Retangulo
            (p->y - player->CurrentTexture.height > platform.y && p->y < platform.y + platform.height) || // Todo Entre-Retangulo
            (p->y - player->CurrentTexture.height < platform.y + platform.height && p->y > platform.y + platform.height))) // Metade-Baixo Retangulo
        {
            p->x += PlayerHorzSpeed * delta;
        }

        else if (player->LastSide == Right && 
            platform.x < p->x + (player->FrameWidth)/4 &&
            platform.x >= p->x + (player->FrameWidth)/4 - PlayerHorzSpeed * delta * 5 &&
            ((p->y > platform.y && p->y - player->CurrentTexture.height < platform.y) || // Metade-Cima Retangulo
            (p->y - player->CurrentTexture.height > platform.y && p->y < platform.y + platform.height) || // Todo Entre-Retangulo
            (p->y - player->CurrentTexture.height < platform.y + platform.height && p->y > platform.y + platform.height))) // Metade-Baixo Retangulo
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