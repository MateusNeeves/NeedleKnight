#include "raylib.h"
#include "colision.h"
#include "player.h"
#include "room.h"

#define G 2500 // 2500
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

void ColisaoSupInf(Player **player, Room rooms, float delta){

    int colision = 0;
    for (int i = 0; i < rooms.platformNmbr ; i++){
        Rectangle platform = rooms.platforms[i];
        Vector2 *p = &((*player)->position);

        if (platform.x <= p->x &&                    // Intervalo do x
            platform.x + platform.width >= p->x &&  //
            platform.y >= p->y &&                       // Personagem em cima do retangulo
            platform.y <= p->y + (*player)->speed * delta) // Proxima altura do personagem abaixo do retangulo
        {
            colision = 1;
            (*player)->speed = 0.0f;
            p->y = platform.y;
        } 
            

        else if (platform.x <= p->x &&                    // Intervalo do x
            platform.x + platform.width >= p->x &&  //
            platform.y + platform.height <= p->y - (*player)->CurrentTexture.height &&  // Personagem em baixo do retangulo
            platform.y + platform.height > p->y - (*player)->CurrentTexture.height + (*player)->speed * delta) // Proxima altura do personagem em cima do retangulo
        {
            (*player)->speed = 0.0f;
            p->y = platform.y + platform.height + (*player)->CurrentTexture.height;
        }
    }

    if (!colision){
        (*player)->position.y += (*player)->speed * delta;
        (*player)->speed += G * delta;
        if ((*player)->canJump[0])
            (*player)->CurrentFrame = 4;
            
        (*player)->canJump[0] = false;
    }
    else{
        (*player)->canJump[0] = true;
        (*player)->canJump[1] = true;
    }   

}

void ColisaoLateral(Player **player, Room rooms, float delta){
    for (int i = 0; i < rooms.platformNmbr ; i++){
        Rectangle platform = rooms.platforms[i];
        Vector2 *p = &((*player)->position);

        if (!(*player)->attacking && 
            platform.x + platform.width > p->x - ((*player)->FrameWidth)/4 &&
            platform.x + platform.width < p->x - ((*player)->FrameWidth)/4 + PlayerHorzSpeed * delta * 7 &&
            p->y - (*player)->CurrentTexture.height <= platform.y + platform.height &&
            p->y >= platform.y)
        {
            p->x += PlayerHorzSpeed * delta;
        }

        else if (!(*player)->attacking && 
            platform.x < p->x + ((*player)->FrameWidth)/4 &&
            platform.x >= p->x + ((*player)->FrameWidth)/4 - PlayerHorzSpeed * delta * 7 &&
            p->y - (*player)->CurrentTexture.height <= platform.y + platform.height &&
            p->y >= platform.y)
        {
            p->x -= PlayerHorzSpeed * delta;
        } 


    }
}

void MossChargerColision (Enemies enemy, Player *player){
    float deltaTime = GetFrameTime();
    static float InvunerableTimer;
    
    if(!player->Invulnerable && 
       !player->attacking && 
        player->CurrentLife > 0 && 
        CheckCollisionRecs(enemy.HitBox , player->HitBox))
    {
        player->CurrentLife -= 1;
        player->Invulnerable = true;
    }

    if (player->Invulnerable)
        InvunerableTimer += deltaTime;

    if (InvunerableTimer > 1.0f){
        player->Invulnerable = false;
        InvunerableTimer = 0.0f;
    }
}

void PlayerAttackColision(Player player, Enemies *enemy){
    float deltaTime = GetFrameTime();
    static float InvunerableTimerE;


    if (!enemy->Invulnerable && CheckCollisionRecs(enemy->HitBox , player.HitBox)){
        enemy->CurrentLife -= 1;
        enemy->Invulnerable = true;
    }

    if (enemy->Invulnerable)
        InvunerableTimerE += deltaTime;

    if (InvunerableTimerE > 1.0f){
        enemy->Invulnerable = false;
        InvunerableTimerE = 0.0f;
    }
}