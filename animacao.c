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

void AnimMenu(Menu *menuInfo, float *Timer, char *diretorio){
    (*Timer) += GetFrameTime();

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
    float deltaTime = GetFrameTime();
    (*LastMove) = &player->CurrentTexture;

    MovePlayer(&player, deltaTime);

    ColisaoSupInf(&player, rooms, deltaTime);

    ColisaoLateral(&player, rooms, deltaTime);

    (*CurrentMove) = &player->CurrentTexture;

    if (player->CurrentFrame == 2 && player->attacking &&
        (*Timer) > 0.1 - 2 * GetFrameTime() && *Timer < 0.1 - GetFrameTime())
    {
        player->attacking = false;
    }

    if (*LastMove != *CurrentMove)
        player->CurrentFrame = 0;

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

    player->CurrentFrame = player->CurrentFrame % player->MaxFrames; 

    Rectangle playerRec = {player->FrameWidth * player->CurrentFrame , 0, player->FrameWidth , player->CurrentTexture.height};
                    
    Vector2 playerRecPosition = {player->position.x - player->FrameWidth/2 , player->position.y - player->CurrentTexture.height};

    DrawTextureRec(player->CurrentTexture, playerRec, playerRecPosition, WHITE); 

}

void AnimPlayerDeath(Player *player, float *Timer){
    
    if (player->LastSide == 0){
        player->CurrentTexture = player->Textures[8];
        player->FrameWidth = player->Textures[8].width / 4.0;
        player->MaxFrames = (int) (player->Textures[8].width / (int) player->FrameWidth);
    }

    else if (player->LastSide == 1){
        player->CurrentTexture = player->Textures[9];
        player->FrameWidth = player->Textures[9].width / 4.0;
        player->MaxFrames = (int) (player->Textures[9].width / (int) player->FrameWidth);
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

void AnimMossCharger(Enemies *enemy){
    float deltaTime = GetFrameTime();

    static int action = 1;
    static float Timer = 0.0f;
    static int distance = 0;

    Timer += deltaTime;

    if (action != 4 && Timer >= 0.09f){ //0.13
        Timer = 0.0f;
        enemy->CurrentFrame += 1;
    } 

    if (enemy->CurrentFrame == 6 && action == 1){
        enemy->CurrentTexture = enemy->Textures[2 + enemy->LastSide];
        enemy->FrameWidth = enemy->CurrentTexture.width/4.0;
        enemy->CurrentFrame = 0;
        action = 2;
    }

    if ( distance > 1200 && action == 2){
        enemy->CurrentTexture = enemy->Textures[4 + enemy->LastSide];
        enemy->FrameWidth = enemy->CurrentTexture.width/12.0;
        enemy->CurrentFrame = 0;
        action = 3;
    }

    if (enemy->CurrentFrame == 11 && action == 3){
        action = 4;
    }

    if (action == 2){
        distance += (enemy->speed * deltaTime);
        if (enemy->LastSide == Left)
            enemy->position.x -= (enemy->speed * deltaTime);
        else
            enemy->position.x += (enemy->speed * deltaTime);
    }


    if (action == 4){
        if (Timer >= 2.0f){
            action = 1;
            Timer = 0.0f;
            distance = 0;
            enemy->LastSide = abs(enemy->LastSide - 1);
            enemy->CurrentTexture = enemy->Textures[enemy->LastSide];
            enemy->CurrentFrame = 0;
            enemy->FrameWidth = enemy->Textures[enemy->LastSide].width/6;
        }
    }

    else{
        Rectangle enemyRec = {enemy->FrameWidth * enemy->CurrentFrame , 0, enemy->FrameWidth , enemy->CurrentTexture.height};
                        
        Vector2 enemyRecPosition = {enemy->position.x - enemy->FrameWidth/2 , enemy->position.y - enemy->CurrentTexture.height + 15};

        DrawTextureRec(enemy->CurrentTexture, enemyRec, enemyRecPosition, WHITE); 
    }
}

void AnimEnemy(Room *rooms, int CurrentRoom){

    if (CurrentRoom == 0){
        AnimMossCharger(&(rooms->enemy));
    }
} 