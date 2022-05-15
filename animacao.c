#include "raylib.h"
#include "player.h"
#include "room.h"
#include "colision.h"
#include "hudmenu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Left 0
#define Right 1
#define DJumpLeftEffect 10
#define DJumpRightEffect 11
#define DamageEffect 12


void AnimMenu(Menu *menuInfo, float *Timer){
    (*Timer) += GetFrameTime();
    char diretorio[27];

    DrawTextureV(menuInfo->Texture, (Vector2) {0, 0}, WHITE);

    if ((*Timer) >= 0.08f){
        (*Timer) = 0.0f;
        menuInfo->CurrentFrame = menuInfo->CurrentFrame % 101;
        menuInfo->CurrentFrame += 1;

        UnloadTexture(menuInfo->Texture);
        sprintf(diretorio, "Assets/FramesMenu/%d.png", menuInfo->CurrentFrame);
        menuInfo->Texture = LoadTexture(diretorio);

    }  
}

void AnimPlayer(Player *player, Texture2D **LastMove, Texture2D **CurrentMove, Room rooms, float *Timer){
    static int cont = 0;
    float deltaTime = GetFrameTime();

    (*LastMove) = &player->CurrentTexture;

    MovePlayer(&player, deltaTime);

    ColisaoSupInf(&player, rooms, deltaTime);

    ColisaoLateral(&player, rooms, deltaTime);

    player->HitBox = (Rectangle) {player->position.x - player->FrameWidth/4,
                                  player->position.y - player->CurrentTexture.height,
                                  player->FrameWidth/2, 
                                  player->CurrentTexture.height};
                                
    player->SwordHitBox = (Rectangle) {0, 0, 0, 0};
 
    if (player->attacking){        
        if (player->LastSide == Left){
            player->SwordHitBox = (Rectangle) {player->position.x - player->FrameWidth/2 + 40,
                                               player->position.y - player->CurrentTexture.height + 40,
                                               170, 250};

            player->HitBox = (Rectangle) {player->position.x - player->FrameWidth/2 + 208,
                                          player->position.y - player->CurrentTexture.height + 163,
                                          100, 120};
        }
        else{
            player->SwordHitBox = (Rectangle) {player->position.x - player->FrameWidth/2 + 252,
                                               player->position.y - player->CurrentTexture.height + 40,
                                               160, 230};

            player->HitBox = (Rectangle) {player->position.x - player->FrameWidth/2 + 150,
                                          player->position.y - player->CurrentTexture.height + 163,
                                          100, 120};
        }
    }


    (*CurrentMove) = &player->CurrentTexture;

    if (player->CurrentFrame == 2 && player->attacking &&
        (*Timer) > 0.1 - 2 * GetFrameTime() && *Timer < 0.1 - GetFrameTime())
    {
        player->attacking = false;
    }

    if (*LastMove != *CurrentMove){
        player->CurrentFrame = 0;
    }

//^ SOM DE ANDAR
/*     if (player->Walking)
        PlaySound(player->SoundEffects[3]);
    else
        StopSound(player->SoundEffects[3]); */

    if (!player->canJump[1] && player->CurrentFrame < 1){
        if (player->LastSide == Left)
            DrawTextureV(player->Textures[DJumpLeftEffect], (Vector2) {player->position.x, player->position.y - 20} , WHITE);
        else
            DrawTextureV(player->Textures[DJumpRightEffect], (Vector2) {(player->position.x - 90), player->position.y - 20} , WHITE);
    }

    (*Timer) += deltaTime;

    if ((*Timer) >= 0.1f){
        (*Timer) = 0.0f;
        player->CurrentFrame += 1;
    } 

    if (player->canJump && !player->attacking && (player->CurrentFrame == 2 || player->CurrentFrame == 6))
        PlaySound(player->SoundEffects[3]);

    player->CurrentFrame = player->CurrentFrame % player->MaxFrames; 

    Rectangle playerRec = {player->FrameWidth * player->CurrentFrame , 0, player->FrameWidth , player->CurrentTexture.height};
                    
    Vector2 playerRecPosition = {player->position.x - player->FrameWidth/2 , player->position.y - player->CurrentTexture.height};

    if (player->Invulnerable && cont % 10 < 8){
        DrawTextureRec(player->CurrentTexture, playerRec, playerRecPosition, RED); 
        cont++;
    }   
    else{
        DrawTextureRec(player->CurrentTexture, playerRec, playerRecPosition, WHITE); 
        cont++;
    }

}

void AnimPlayerDeath(Player *player, float *Timer, Room rooms){
    float deltaTime = GetFrameTime();
    static int flag = 1;

    ColisaoSupInf(&player, rooms, deltaTime);

    if (player->LastSide == 0 && flag == 1){
        player->CurrentTexture = player->Textures[8];
        player->FrameWidth = player->Textures[8].width / 4.0;
        player->MaxFrames = (int) (player->Textures[8].width / (int) player->FrameWidth);
        player->CurrentFrame = 0;
        flag = 0;
        PlaySound(player->SoundEffects[2]);
    }

    else if (player->LastSide == 1 && flag == 1){
        player->CurrentTexture = player->Textures[9];
        player->FrameWidth = player->Textures[9].width / 4.0;
        player->MaxFrames = (int) (player->Textures[9].width / (int) player->FrameWidth);
        player->CurrentFrame = 0;
        flag = 0;
        PlaySound(player->SoundEffects[2]);
    }

    *Timer += GetFrameTime();

    if (*Timer >= 0.2f){
        *Timer = 0.0f;

        if(player->CurrentFrame < 3)
            player->CurrentFrame += 1;
    }

    Rectangle playerRec = {player->FrameWidth * player->CurrentFrame , 0, player->FrameWidth , player->CurrentTexture.height};
                    
    Vector2 playerRecPosition = {player->position.x - player->FrameWidth/2 , player->position.y - player->CurrentTexture.height + 10};

    DrawTextureRec(player->CurrentTexture, playerRec, playerRecPosition, WHITE);
}

void AnimMossCharger(Enemies **enemy, int CurrentEnemy){
    float deltaTime = GetFrameTime();
    static int cont = 0;
    static int action = 1;
    static float Timer = 0.0f;
    static int distance = 0;
    static int next = 0;
    static Vector2 savePosition;

    Timer += deltaTime;

    if (CurrentEnemy == 1 && next == 0){
        next = 1;
        cont = 1;
        action = 1;
        Timer = 0.0f;
        distance = 0;
    }

    if (action != 4 && Timer >= 0.09f){
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }

    if (action == 1 && (*enemy)->CurrentFrame == 0)
        PlaySound((*enemy)->SoundEffects[1]);


    if (action == 1 && (*enemy)->CurrentFrame == 6){
        (*enemy)->CurrentTexture =  (*enemy)->Textures[2 +  (*enemy)->LastSide];
        (*enemy)->FrameWidth =  (*enemy)->CurrentTexture.width/4.0;
        (*enemy)->CurrentFrame = 0;
        action = 2;
        PlaySound((*enemy)->SoundEffects[2]);
    }


    if (action == 3){
        if ((*enemy)->CurrentFrame == 0){
            StopSound((*enemy)->SoundEffects[2]);
            PlaySound((*enemy)->SoundEffects[3]);
        }
        else if ((*enemy)->CurrentFrame == 12){
            action = 4;
            savePosition = (*enemy)->position;
            (*enemy)->position = (Vector2) {-1000,-1000};
        }
    }

    if (action == 2){
        distance += ((*enemy)->speed * deltaTime);
        if ((*enemy)->LastSide == Left)
            (*enemy)->position.x -= ((*enemy)->speed * deltaTime);
        else
            (*enemy)->position.x += ((*enemy)->speed * deltaTime);

        if (distance > 1200){
            (*enemy)->CurrentTexture = (*enemy)->Textures[4 + (*enemy)->LastSide];
            (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/12.0;
            (*enemy)->CurrentFrame = 0;
            action = 3;
        }
    }


    if (action == 4){
        if (Timer >= 2.0f){
            action = 1;
            Timer = 0.0f;
            distance = 0;
            (*enemy)->LastSide = abs((*enemy)->LastSide - 1);
            (*enemy)->CurrentTexture = (*enemy)->Textures[(*enemy)->LastSide];
            (*enemy)->CurrentFrame = 0;
            (*enemy)->FrameWidth = (*enemy)->Textures[(*enemy)->LastSide].width/6;
            (*enemy)->position = savePosition;
        }
    }

    else{
        Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 15};

        if ((*enemy)->Invulnerable && cont % 10 < 8){
            DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, BLACK); 
            cont++;
        }
        else{
            DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
            cont++;
        }
    }
}

void AnimMossChargerDeath(Enemies **enemy, int **CurrentEnemy, float *Timer){
    static int flag = 0;
    static float Timer2 = 0.0f;
    float deltaTime = GetFrameTime();

    Timer2 += deltaTime;
    
    if (flag == 0){
        if ((*enemy)->LastSide == Left)
            (*enemy)->CurrentTexture = (*enemy)->Textures[4];
        else
            (*enemy)->CurrentTexture = (*enemy)->Textures[5];

        (*enemy)->FrameWidth = (*enemy)->Textures[4].width/12;
        (*enemy)->CurrentFrame = 0;
        flag = 1;
        StopSound((*enemy)->SoundEffects[2]);
        PlaySound((*enemy)->SoundEffects[3]);
    }

    if (Timer2 >= 0.09f){ 
        Timer2 = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }

    if ((*enemy)->CurrentFrame < 12){
        Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 15};

        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
    }
    else{
        if (*(*CurrentEnemy) == 0)
            flag = 0;

        (*enemy)->position = (Vector2) {0, 0};
        *(*CurrentEnemy) = 1;
        *Timer = 0;
        (*enemy)->CurrentFrame = 0;
    }

}

void AnimKingsMould(Enemies **enemy, Player **player){
    float deltaTime = GetFrameTime();
    static int cont = 0;
    static int action = 0;
    static float Timer = 0.0f;
    static int loopCounter = 0;

    Timer += deltaTime;

    if (Timer >= 0.1f){
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    } 

    if ((*player)->position.x < 1250 && action == 0){
        action = 1;
        (*enemy)->CurrentTexture = (*enemy)->Textures[1];
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/6.0;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 1 && (*enemy)->CurrentFrame == 6){
        loopCounter += 1;
        (*enemy)->CurrentFrame = 1;
        PlaySound((*enemy)->SoundEffects[1]);
    }

    if (action == 1 && loopCounter == 3){
        action = 2;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 3 && (*enemy)->CurrentFrame == 15){
        (*enemy)->attacking = false;
        action = 2;
    }
    
    if (action == 2 && abs((*player)->position.x - (*enemy)->position.x) > 155){

        if ((*player)->position.x >= (*enemy)->position.x){ // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[3];
            (*enemy)->position.x += (*enemy)->speed * deltaTime;
            (*enemy)->LastSide = Right;
        }
        else{                                                // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[2];
            (*enemy)->position.x -= (*enemy)->speed * deltaTime;
            (*enemy)->LastSide = Left;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/8.0;
    }

    else if (action == 2 && abs((*player)->position.x - (*enemy)->position.x) <= 155){
        if ((*player)->position.x >= (*enemy)->position.x){    // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[5];
            (*enemy)->LastSide = Right;
        }
        else{                                                 // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[4];
            (*enemy)->LastSide = Left;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/15.0;
        (*enemy)->attacking = true;
        (*enemy)->CurrentFrame = 0;
        action = 3;
    }


    if (action == 3 && ((*enemy)->CurrentFrame == 7 || (*enemy)->CurrentFrame == 13))
        PlaySound((*enemy)->SoundEffects[2]);

    Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                    
    Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 15};

     if ((*enemy)->Invulnerable && cont % 10 < 8){
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, BLACK); 
        cont++;
    }
    else{ 
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
        cont++;
    }
}

void AnimKingsMouldDeath(Enemies **enemy, int **CurrentEnemy){
    static int flag = 0;
    static float Timer = 0.0f;
    float deltaTime = GetFrameTime();

    Timer += deltaTime;
    
    if (flag == 0){
        if ((*enemy)->LastSide == Left)
            (*enemy)->CurrentTexture = (*enemy)->Textures[6];
        else
            (*enemy)->CurrentTexture = (*enemy)->Textures[7];

        (*enemy)->FrameWidth = (*enemy)->Textures[6].width/3;
        (*enemy)->CurrentFrame = 0;
        flag = 1;
    }
    if (Timer >= 0.1f){ 
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }

    if ((*enemy)->CurrentFrame < 3){
        Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 20};

        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
    }
    else{
        (*enemy)->position = (Vector2) {0, 0};
        *(*CurrentEnemy) = 1;
    }
}

void AnimTheCollector(Enemies **enemy, Player **player, int *inAnim){
    float deltaTime = GetFrameTime();
    static int action = 0;
    static int loopCounter = 0;
    static int cont = 0;
    static float Timer = 0.0f;

    Timer += deltaTime;

    if (Timer >= 0.1f){
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }
    if (action == 0)
        *inAnim = 1;

    if (action == 0 && (*enemy)->CurrentFrame == 2)
        PlaySound((*enemy)->SoundEffects[1]);

    if (action == 0 && (*enemy)->CurrentFrame == 6){
        loopCounter++;
        (*enemy)->CurrentFrame = 3;
    }

    if (loopCounter == 12 && action == 0){
        action = 1;
        (*enemy)->CurrentTexture = (*enemy)->Textures[2 + (*enemy)->LastSide];
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/10.0;
        (*enemy)->CurrentFrame = 0;
    } 

    if ((*enemy)->CurrentFrame == 0 && (*enemy)->position.y != 975)
        (*enemy)->position.y = 975;

    if (action == 1){
        if  ((*enemy)->CurrentFrame == 10){
            (*enemy)->CurrentFrame = 0;
            Timer = 0.0f;
        }

        if ((*enemy)->CurrentFrame == 3){
            (*enemy)->position.y -= 10;
            PlaySound((*enemy)->SoundEffects[2]);
        }
        else if ((*enemy)->CurrentFrame == 4)
            (*enemy)->position.y -= 5;
        else if ((*enemy)->CurrentFrame == 5)
            (*enemy)->position.y += 5;
        else if ((*enemy)->CurrentFrame == 6)
            (*enemy)->position.y += 10;

        if ((*enemy)->CurrentFrame > 2 && (*enemy)->CurrentFrame < 7){
            if ((*player)->position.x >= (*enemy)->position.x){ // Right
                (*enemy)->CurrentTexture = (*enemy)->Textures[3];
                (*enemy)->position.x += (*enemy)->speed * deltaTime;
                (*enemy)->LastSide = Right;
            }

            else{                                                // Left
                (*enemy)->position.x -= (*enemy)->speed * deltaTime;
                (*enemy)->CurrentTexture = (*enemy)->Textures[2];
                (*enemy)->LastSide = Left;
            }
        }
    }

       if (action == 2 && abs((*player)->position.x - (*enemy)->position.x) > 155 && !(*enemy)->attacking){

        if ((*player)->position.x >= (*enemy)->position.x){ // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[3];
            (*enemy)->position.x += (*enemy)->speed * deltaTime;
            (*enemy)->LastSide = Right;
        }
        else{                                                // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[2];
            (*enemy)->position.x -= (*enemy)->speed * deltaTime;
            (*enemy)->LastSide = Left;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/8.0;
    }

    Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                    
    Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height};

    if ((*enemy)->Invulnerable && cont % 10 < 8){
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, BLACK); 
        cont++;
    }
    else{ 
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
        cont++;
    }

}

void AnimTheCollectorDeath(Enemies **enemy){
    static int flag = 0;
    static float Timer = 0.0f;
    float deltaTime = GetFrameTime();

    Timer += deltaTime;
    
    if (flag == 0){
        if ((*enemy)->LastSide == Left)
            (*enemy)->CurrentTexture = (*enemy)->Textures[4];
        else
            (*enemy)->CurrentTexture = (*enemy)->Textures[5];

        (*enemy)->FrameWidth = (*enemy)->Textures[4].width/10;
        (*enemy)->CurrentFrame = 0;
        flag = 1;
        PlaySound((*enemy)->SoundEffects[3]);
    }
    if (Timer >= 0.1f){ 
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }

    if ((*enemy)->CurrentFrame < 10){
        Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , 695};

        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
    }
 
    else{
        Rectangle enemyRec = {(*enemy)->FrameWidth * 9 , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , 695};

        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
    }
}

void AnimNightmareKing(Enemies **enemy, Player **player){
    float deltaTime = GetFrameTime();
    static int cont = 0;
    static int action = 0;
    static float Timer = 0.0f;

    Timer += deltaTime;

    if (action == 0 && Timer >= 0.1f){
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    } 

    if ((action == 1 || action == 2 || action == 3) && Timer >= 0.07f){
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    } 

    if (action == 0 && (*player)->position.y > 850){
        action = 1;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 1 && (*enemy)->CurrentFrame == 0)
        PlaySound((*enemy)->SoundEffects[1]);

    if (action == 1 && (*enemy)->CurrentFrame == 6){
        action = 2;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 1){ //~ Desaparecendo
        if ((*player)->position.x >= (*enemy)->position.x){    // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[2];
            (*enemy)->LastSide = Right;
        }
        else{                                                 // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[1];
            (*enemy)->LastSide = Left;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/6.0;
    }

    if (action == 2 && (*enemy)->CurrentFrame == 0)
        PlaySound((*enemy)->SoundEffects[2]);

    if (action == 2 && (*enemy)->CurrentFrame == 7){
        action = 3;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 2 && (*enemy)->CurrentFrame == 0){ //~ Reaparecendo
        if ((*player)->position.x >= (*enemy)->position.x){    // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[4];
            (*enemy)->LastSide = Right;
            (*enemy)->position.y = (*player)->position.y;
            (*enemy)->position.x = (*player)->position.x - 155;
        }
        else{                                                 // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[3];
            (*enemy)->LastSide = Left;
            (*enemy)->position.y = (*player)->position.y;
            (*enemy)->position.x = (*player)->position.x + 155;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/7.0;
    }

    if ((*enemy)->position.x < 310 && (*enemy)->position.y > 850){
        (*enemy)->position.x = 510;
    }
    else if ((*enemy)->position.x > 1630 && (*enemy)->position.y > 850){
        (*enemy)->position.x = 1410;
    }

    if (action == 3 && (*enemy)->CurrentFrame == 0)
        PlaySound((*enemy)->SoundEffects[3]);

    if (action == 3 && (*enemy)->CurrentFrame == 9){
        action = 1;
        (*enemy)->attacking = false;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 3){  //~ Atacando
        if ((*player)->position.x >= (*enemy)->position.x){    // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[6];
            (*enemy)->LastSide = Right;
            (*enemy)->attacking = true;
        }
        else{                                                 // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[5];
            (*enemy)->LastSide = Left;
            (*enemy)->attacking = true;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/9.0;
    }

    Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                    
    Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 15};

     if ((*enemy)->Invulnerable && cont % 10 < 8){
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, BLACK); 
        cont++;
    }
    else{ 
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
        cont++;
    }
}

void AnimNightmareKingDeath(Enemies **enemy, int **CurrentEnemy){
    static int flag = 0;
    static float Timer = 0.0f;
    float deltaTime = GetFrameTime();

    Timer += deltaTime;
    
    if (flag == 0){
        if ((*enemy)->LastSide == Left)
            (*enemy)->CurrentTexture = (*enemy)->Textures[7];
        else
            (*enemy)->CurrentTexture = (*enemy)->Textures[8];

        (*enemy)->FrameWidth = (*enemy)->Textures[7].width/5;
        (*enemy)->CurrentFrame = 0;
        flag = 1;
        PlaySound((*enemy)->SoundEffects[4]);
    }
    if (Timer >= 0.1f){ 
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }

    if ((*enemy)->CurrentFrame < 5){
        Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 20};

        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
    }
    else{
        (*enemy)->position = (Vector2) {0, 0};
        *(*CurrentEnemy) = 1;
    }
}

void AnimGrimm(Enemies **enemy, Player **player){
    float deltaTime = GetFrameTime();
    static int cont = 0;
    static int action = 0;
    static float Timer = 0.0f;
    static int loopCounter = 0;

    Timer += deltaTime;

    if (action != 3 && Timer >= 0.08f){
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    } 

    if (action == 3 && Timer >= 0.05f){
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }

    if (action == 0 && (*enemy)->CurrentFrame == 5)
        PlaySound((*enemy)->SoundEffects[1]);

    if (action == 0 && (*enemy)->CurrentFrame == 9){
        loopCounter++;
        (*enemy)->CurrentFrame = 6;
    }

    if (action == 0 && loopCounter == 4){
        //StopSound((*enemy)->SoundEffects[0]);
        (*enemy)->CurrentFrame = 0;
        action = 1;
    }

    if (action == 1 && (*enemy)->CurrentFrame == 0)
        PlaySound((*enemy)->SoundEffects[2]);

    if (action == 1 && (*enemy)->CurrentFrame == 5){
        //StopSound((*enemy)->SoundEffects[1]);
        action = 2;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 1){ //~ Desaparecendo
        if ((*player)->position.x >= (*enemy)->position.x){    // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[3];
            (*enemy)->LastSide = Right;
        }
        else{                                                 // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[2];
            (*enemy)->LastSide = Left;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/5.0;
    }

    if (action == 2 && (*enemy)->CurrentFrame == 5){
        action = 3;
        //StopSound((*enemy)->SoundEffects[2]);
        (*enemy)->CurrentFrame = 0;
    }



    if (action == 2 && (*enemy)->CurrentFrame == 0){ //~ Reaparecendo
        if ((*player)->position.x >= (*enemy)->position.x){    // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[5];
            (*enemy)->LastSide = Right;
            (*enemy)->position.y = (*player)->position.y;
            (*enemy)->position.x = (*player)->position.x - 155;
        }
        else{                                                 // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[4];
            (*enemy)->LastSide = Left;
            (*enemy)->position.y = (*player)->position.y;
            (*enemy)->position.x = (*player)->position.x + 155;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/5.0;
        PlaySound((*enemy)->SoundEffects[3]);
    }

    //NAO ENTRAR NA PAREDE vvv
    if ((*enemy)->position.x < 310 && (*enemy)->position.y > 850){
        (*enemy)->position.x = 510;
    }
    else if ((*enemy)->position.x > 1630 && (*enemy)->position.y > 850){
        (*enemy)->position.x = 1410;
    }

    if (action == 3 && (*enemy)->CurrentFrame == 0)
        PlaySound((*enemy)->SoundEffects[4]);

    if (action == 3 && (*enemy)->CurrentFrame == 10){
        action = 1;
        (*enemy)->attacking = false;
        (*enemy)->CurrentFrame = 0;
    }

    if (action == 3){  //~ Atacando
        if ((*player)->position.x >= (*enemy)->position.x){    // Right
            (*enemy)->CurrentTexture = (*enemy)->Textures[7];
            (*enemy)->LastSide = Right;
            (*enemy)->attacking = true;
        }
        else{                                                 // Left
            (*enemy)->CurrentTexture = (*enemy)->Textures[6];
            (*enemy)->LastSide = Left;
            (*enemy)->attacking = true;
        }
        (*enemy)->FrameWidth = (*enemy)->CurrentTexture.width/10.0;
    }

    Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                    
    Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 15};

     if ((*enemy)->Invulnerable && cont % 10 < 8){
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, BLACK); 
        cont++;
    }
    else{ 
        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
        cont++;
    }
}

void AnimGrimmDeath(Enemies **enemy){
    static int flag = 0;
    static float Timer = 0.0f;
    float deltaTime = GetFrameTime();

    Timer += deltaTime;
    
    if (flag == 0){
        if ((*enemy)->LastSide == Left)
            (*enemy)->CurrentTexture = (*enemy)->Textures[8];
        else
            (*enemy)->CurrentTexture = (*enemy)->Textures[9];

        (*enemy)->FrameWidth = (*enemy)->Textures[8].width/6.0;
        (*enemy)->CurrentFrame = 0;
        flag = 1;
        PlaySound((*enemy)->SoundEffects[5]);
    }
    if (Timer >= 0.1f){ 
        Timer = 0.0f;
        (*enemy)->CurrentFrame += 1;
    }

    if ((*enemy)->CurrentFrame < 6){
        Rectangle enemyRec = {(*enemy)->FrameWidth * (*enemy)->CurrentFrame , 0, (*enemy)->FrameWidth , (*enemy)->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {(*enemy)->position.x - (*enemy)->FrameWidth/2 , (*enemy)->position.y - (*enemy)->CurrentTexture.height + 20};

        DrawTextureRec((*enemy)->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
    }
    else{
        (*enemy)->position = (Vector2) {0, 0};
    }
}

void AnimEnemy(Player *player, Enemies *enemy, int CurrentRoom, int *CurrentEnemy){
    static float Timer = 0.0f;
    static int flag = 0;


    if (CurrentRoom == 0){ // ^MAPA 0
        Timer += GetFrameTime();

        if (Timer > 2.0f && (player->position.x > 300 || flag == 1)){
            flag = 1;
            if(enemy->CurrentLife > 0){
                AnimMossCharger(&enemy, *CurrentEnemy);
                if(*CurrentEnemy == 0){
                    enemy->HitBox = (Rectangle) {enemy->position.x - enemy->FrameWidth/2,
                                                 enemy->position.y - enemy->CurrentTexture.height + 50,
                                                 enemy->FrameWidth, 
                                                 enemy->CurrentTexture.height};
                }
                else{
                    if (enemy->LastSide == Left){
                        enemy->HitBox = (Rectangle) {enemy->position.x - enemy->FrameWidth/2,
                                                     enemy->position.y - enemy->CurrentTexture.height + 100,
                                                     enemy->FrameWidth * 3/4, 
                                                     enemy->CurrentTexture.height};
                    } 
                    else{
                        enemy->HitBox = (Rectangle) {enemy->position.x - enemy->FrameWidth/4,
                                                     enemy->position.y - enemy->CurrentTexture.height + 100,
                                                     enemy->FrameWidth * 3/4, 
                                                     enemy->CurrentTexture.height};
                    }
                }
            }
            else{
                AnimMossChargerDeath(&enemy, &CurrentEnemy, &Timer);
                enemy->HitBox = (Rectangle) {0, 0, 0, 0};

            }
        }
    }

    if (CurrentRoom == 2){ // ^MAPA 2

        if(*CurrentEnemy == 0){  //^ ARMADURA
            if(enemy->CurrentLife > 0){
                AnimKingsMould(&enemy, &player); 

                if (enemy->LastSide == Left){
                    if (enemy->attacking){

                        enemy->SwordHitBox = (Rectangle) {0, 0, 0, 0};

                        if(enemy->CurrentFrame == 7 || enemy->CurrentFrame == 13){
                            enemy->SwordHitBox = (Rectangle) {enemy->position.x - enemy->FrameWidth/2,
                                                              enemy->position.y - enemy->CurrentTexture.height + 100,
                                                              260, 250};
                        }
                        enemy->HitBox = (Rectangle) {enemy->position.x - 50,
                                                     enemy->position.y - 170,
                                                     125, 145};
                    }
                    else{
                        enemy->HitBox = (Rectangle) {enemy->position.x,
                                                    enemy->position.y - enemy->CurrentTexture.height + 120,
                                                    130, 150};
                    }
                }
                else{
                    if (enemy->attacking){

                        enemy->SwordHitBox = (Rectangle) {0, 0, 0, 0};

                        if (enemy->CurrentFrame == 7 || enemy->CurrentFrame == 13){
                            enemy->SwordHitBox = (Rectangle) {enemy->position.x,
                                                              enemy->position.y - enemy->CurrentTexture.height + 100,
                                                              260, 250};
                        }
                        enemy->HitBox = (Rectangle) {enemy->position.x - 50,
                                                     enemy->position.y - 170,
                                                     125, 145};
                    }
                    else{
                        enemy->HitBox = (Rectangle) {enemy->position.x - enemy->FrameWidth/2,
                                                     enemy->position.y - enemy->CurrentTexture.height + 120,
                                                     130, 150}; 
                    }
                }
            }
            else{
                AnimKingsMouldDeath(&enemy, &CurrentEnemy);
                enemy->HitBox = (Rectangle) {0, 0, 0, 0};

            }
        }

        else{ //^ SOMBRA
            if(enemy->CurrentLife > 0){
                int inAnim = 0;
                AnimTheCollector(&enemy, &player, &inAnim);

                if (inAnim == 0)
                    enemy->HitBox = (Rectangle) {enemy->position.x - 50,
                                                enemy->position.y - 150,
                                                100, 150};
                else
                    enemy->HitBox = (Rectangle) {0, 0, 0, 0};
            }
            else{
                AnimTheCollectorDeath(&enemy);
                enemy->HitBox = (Rectangle) {0, 0, 0, 0};
            }
        }
                
    }

    if (CurrentRoom == 3){ // ^MAPA 3

        if (*CurrentEnemy == 0){
            if (enemy->CurrentLife > 0){
                AnimNightmareKing(&enemy, &player); 
                
                enemy->SwordHitBox = (Rectangle) {0, 0, 0, 0};
        
                enemy->HitBox = (Rectangle) {enemy->position.x - 60,
                                             enemy->position.y - 240,
                                             100, 230};

                if (enemy->LastSide == Left && enemy->attacking){
                    if (enemy->CurrentFrame >= 4 && enemy->CurrentFrame <= 6){
                        enemy->SwordHitBox = (Rectangle) {enemy->position.x - enemy->FrameWidth/2,
                                                          enemy->position.y - enemy->CurrentTexture.height + 100,
                                                          200, 230};
                    }
                    enemy->HitBox = (Rectangle) {enemy->position.x - 50,
                                                  enemy->position.y - 170,
                                                  125, 145};
                }
                else if (enemy->LastSide == Right && enemy->attacking){
                    if (enemy->CurrentFrame >= 4 && enemy->CurrentFrame <= 6){
                        enemy->SwordHitBox = (Rectangle) {enemy->position.x,
                                                          enemy->position.y - enemy->CurrentTexture.height + 100,
                                                          200, 230};
                    }
                    enemy->HitBox = (Rectangle) {enemy->position.x - 50,
                                                 enemy->position.y - 170,
                                                 125, 145};
                }
            }
             else{
                AnimNightmareKingDeath(&enemy, &CurrentEnemy);
                enemy->HitBox = (Rectangle) {0, 0, 0, 0};
            } 
        }
        
        else{
            if (enemy->CurrentLife > 0){
                AnimGrimm(&enemy, &player); 
                
                enemy->SwordHitBox = (Rectangle) {0, 0, 0, 0};
        
                enemy->HitBox = (Rectangle) {enemy->position.x - 60,
                                             enemy->position.y - 240,
                                             100, 230};

                if (enemy->LastSide == Left && enemy->attacking){
                    if (enemy->CurrentFrame >= 5 && enemy->CurrentFrame <= 8){
                        enemy->SwordHitBox = (Rectangle) {enemy->position.x - enemy->FrameWidth/2,
                                                          enemy->position.y - enemy->CurrentTexture.height + 100,
                                                          200, 230};
                    }
                    enemy->HitBox = (Rectangle) {enemy->position.x - 50,
                                                  enemy->position.y - 170,
                                                  125, 145};
                }
                else if (enemy->LastSide == Right && enemy->attacking){
                    if (enemy->CurrentFrame >= 5 && enemy->CurrentFrame <= 8){
                        enemy->SwordHitBox = (Rectangle) {enemy->position.x,
                                                          enemy->position.y - enemy->CurrentTexture.height + 100,
                                                          200, 230};
                    }
                    enemy->HitBox = (Rectangle) {enemy->position.x - 50,
                                                 enemy->position.y - 170,
                                                 125, 145};
                } 
            }
             else{
                AnimGrimmDeath(&enemy);
                enemy->HitBox = (Rectangle) {0, 0, 0, 0};
            } 
        } 
    }
} 