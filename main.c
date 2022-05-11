#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "player.h"
#include "colision.h"
#include "room.h"
#include "hudmenu.h"
#include "animacao.h"

int main(void){

    InitWindow(GetScreenWidth(), GetScreenHeight(), "GAMEZIN");
    ToggleFullscreen();
    SetTargetFPS(60);

    Player player;
    CreatePlayer(&player);

    Room *rooms = (Room*) calloc (4, sizeof(Room));
    CreateRooms(&rooms);

    Texture2D *LastMove, *CurrentMove;
    float Timer = 0.0f;

    GameScreen CurrentScreen = MENU;
    char diretorio[27];
    
    Menu menuInfo;
    CreateMenuInfo(&menuInfo);

    Hud infoHud;
    CreateHud(&infoHud);

    float counter = 0;
    int CurrentRoom = 1;
    int LastRoom = 1;

    while (!WindowShouldClose()){
        
        BeginDrawing();

        switch (CurrentScreen){
            case MENU:{

                if (IsKeyPressed(KEY_ENTER))
                    CurrentScreen = GAMEPLAY;

                AnimMenu(&menuInfo, &Timer, diretorio);

                break;
            }
            
            case GAMEPLAY:{

                if (IsKeyPressed(KEY_ENTER))
                    CurrentScreen = MENU;

                VerifyRooms(&CurrentRoom, &LastRoom, &player);

                DrawRoom(rooms[CurrentRoom], 1); //Printar Atras
                if (rooms[CurrentRoom].enemyNmbr > 0)
                    AnimEnemy(&rooms[CurrentRoom], CurrentRoom);

                if (player.CurrentLife > 0)
                    AnimPlayer(&player, &LastMove, &CurrentMove, rooms[CurrentRoom], &Timer);
                else  
                    AnimPlayerDeath(&player, &Timer);

                DrawRoom(rooms[CurrentRoom], 0); // Printar na Frente

                DrawPlayerLife(player, infoHud, counter);

                //for (int i = 0; i < rooms[CurrentRoom].platformNmbr; i++) DrawRectangleRec(rooms[CurrentRoom].platforms[i], WHITE);  

                break;
            }

            default:
                break;
        }

        EndDrawing();
    }
    
    for (int i = 0 ; i < 12 ; i++)
        UnloadTexture(player.Textures[i]);

    for (int i = 0 ; i < 4 ; i++){
        UnloadTexture(rooms[i].texture);
        UnloadTexture(rooms[i].FrontTexture);
        free(rooms[i].platforms);
    }
    free(rooms); 

    for (int i = 0 ; i < 6 ; i++)
        UnloadTexture(rooms[0].enemy.Textures[i]);
    


    UnloadTexture(menuInfo.Texture);
    UnloadTexture(infoHud.TexturePLife);

    CloseWindow();
}