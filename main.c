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

    Room *rooms = (Room*) calloc (1, sizeof(Room));
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

                DrawRoom(rooms, 1); //Printar Atras

                if (player.CurrentLife > 0)
                    AnimPlayer(&player, &LastMove, &CurrentMove, rooms, &Timer);
                else  
                    AnimPlayerDeath(&player, &Timer);

                DrawRoom(rooms, 0); // Printar na Frente

                DrawPlayerLife(player, infoHud, counter);

                //for (int i = 0; i < rooms[0].platformNmbr; i++) DrawRectangleRec(rooms[0].platforms[i], WHITE);  

                break;
            }

            default:
                break;
        }

        EndDrawing();
    }
    
    for (int i = 0 ; i < 10 ; i++)
        UnloadTexture(player.PlayerTextures[i]);

    UnloadTexture(rooms[0].texture);
    UnloadTexture(rooms[0].FrontTexture);
    UnloadTexture(menuInfo.Texture);
    UnloadTexture(infoHud.TexturePLife);

    free(rooms[0].platforms);
    free(rooms); 

    CloseWindow();
}