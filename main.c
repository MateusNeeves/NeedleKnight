#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "player.h"
#include "colision.h"
#include "room.h"

int main(void){

    InitWindow(GetScreenWidth(), GetScreenHeight(), "GAMEZIN");

    ToggleFullscreen();

    Player player;
    CreatePlayer(&player);

    Room *rooms = (Room*) calloc (1, sizeof(Room));
    CreateRooms(&rooms);

    Texture2D *LastMove, *CurrentMove;
    
    float deltaTime;
    float Timer = 0.0f;
    int colision; 


    SetTargetFPS(60);

    while (!WindowShouldClose()){

        deltaTime = GetFrameTime();
        LastMove = &player.CurrentTexture;

        MovePlayer(&player, deltaTime);

        ColisaoSupInf(&player, rooms[0], deltaTime, &colision);

        ColisaoLateral(&player, rooms[0], deltaTime);

        HitObstacle(&player, deltaTime, colision);

        CurrentMove = &player.CurrentTexture;

        if (LastMove != CurrentMove)
            player.CurrentFrame = 0;

         Timer += GetFrameTime();

        if (Timer >= 0.1f){
            Timer = 0.0f;
            player.CurrentFrame += 1;
        }

        player.CurrentFrame = player.CurrentFrame % player.MaxFrames;  

        BeginDrawing();

                Rectangle fundo = {0 , 0, rooms[0].textureRoom.width , rooms[0].textureRoom.height };

                Vector2 posFundo = {0, 0};
                
                DrawTextureRec(rooms[0].textureRoom, fundo, posFundo, WHITE);  

                /* for (int i = 0; i < rooms[0].platformNmbr; i++)
                    DrawRectangleRec(rooms[0].platforms[i], WHITE);   */ 

                 Rectangle textureRec = {player.FrameWidth * player.CurrentFrame , 0, player.FrameWidth , player.CurrentTexture.height};
                
                Vector2 position = {player.position.x - player.FrameWidth/2 , player.position.y - player.CurrentTexture.height};

                DrawTextureRec(player.CurrentTexture, textureRec, position, WHITE); 


        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    for (int i = 0 ; i < 4 ; i++)
        UnloadTexture(player.PlayerTextures[i]);

    UnloadTexture(rooms[0].textureRoom);

    free(rooms[0].platforms);
    free(rooms); 

    CloseWindow();
}