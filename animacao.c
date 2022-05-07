#include "raylib.h"
#include "player.h"
#include "room.h"
#include "colision.h"
#include "hudmenu.h"
#include <stdio.h>
#include <string.h>

void AnimMenu(Menu *menuInfo, float *Timer, char *diretorio){
    (*Timer) += GetFrameTime();

    if ((*Timer) >= 0.1f){
        (*Timer) = 0.0f;

        menuInfo->CurrentFrame = menuInfo->CurrentFrame % 101;
        menuInfo->CurrentFrame += 1;

        UnloadTexture(menuInfo->Texture);
        sprintf(diretorio, "Assets/FramesMenu/%d.png", menuInfo->CurrentFrame);
        menuInfo->Texture = LoadTexture(diretorio);
    }

        DrawTextureV(menuInfo->Texture, (Vector2) {0, 0}, WHITE);

}

void AnimPlayer(Player *player, Texture2D **LastMove, Texture2D **CurrentMove, Room *rooms, float *Timer){
    float deltaTime = GetFrameTime();
    (*LastMove) = &player->CurrentTexture;

    MovePlayer(&player, deltaTime);

    ColisaoSupInf(&player, rooms[0], deltaTime);

    ColisaoLateral(&player, rooms[0], deltaTime);

    (*CurrentMove) = &player->CurrentTexture;

    if (player->CurrentFrame == 2 && player->attacking &&
        (*Timer) > 0.1 - 2 * GetFrameTime() && *Timer < 0.1 - GetFrameTime())
    {
        player->attacking = false;
    }

    if (*LastMove != *CurrentMove)
        player->CurrentFrame = 0;

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
        player->CurrentTexture = player->PlayerTextures[8];
        player->FrameWidth = player->PlayerTextures[8].width / 4.0;
        player->MaxFrames = (int) (player->PlayerTextures[8].width / (int) player->FrameWidth);
    }

    else if (player->LastSide == 1){
        player->CurrentTexture = player->PlayerTextures[9];
        player->FrameWidth = player->PlayerTextures[9].width / 4.0;
        player->MaxFrames = (int) (player->PlayerTextures[9].width / (int) player->FrameWidth);
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