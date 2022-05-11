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
    //ToggleFullscreen();
    SetTargetFPS(60);

    InitAudioDevice();

    Music menuMusic = LoadMusicStream("musicas/TESTE.mp3"); // OST menu

    Music *musicas = calloc(4, sizeof(Music));

    
    //for(int i = 0;i<4;i++)
        //musicas[i] = LoadMusicStream("musicas/OST-Room%d.mp3",i+1);

    musicas[0] = LoadMusicStream("musicas/OST-Room1.mp3"); //Sala 0
    musicas[1] = LoadMusicStream("musicas/OST-Room2.mp3"); //Sala 1
    musicas[2] = LoadMusicStream("musicas/OST-Room3.mp3"); //Sala 2
    musicas[3] = LoadMusicStream("musicas/OST-Room4.mp3"); //Sala 3

    for(int i = 0;i<4;i++)
        SetMusicVolume(musicas[i], 0.07); 

    Sound *efeitos =NULL;
    efeitos = (Sound*) realloc(efeitos, 3 * sizeof(Sound));
    
    efeitos[0] = LoadSound("musicas/PlayerAttack.mp3");
    efeitos[1] = LoadSound("musicas/PlayerJump.mp3");
    efeitos[2] = LoadSound("musicas/Hornet_Fight_Death_01.mp3");

    Player player;
    CreatePlayer(&player);

    Room *rooms = NULL;
    rooms= (Room*) realloc(rooms, 4*sizeof(Room));
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
                
                UpdateMusicStream(menuMusic);
                if (IsKeyPressed(KEY_ENTER))
                {   
                    //PauseMusicStream(menuMusic);
                    CurrentScreen = GAMEPLAY;
                }
                AnimMenu(&menuInfo, &Timer, diretorio);
                break;
            }
            
            case GAMEPLAY:{
                 
                if (IsKeyPressed(KEY_ENTER))
                {
                    //ResumeMusicStream(menuMusic);
                    CurrentScreen = MENU;
                }
                
                if(IsKeyDown(KEY_Z) && CurrentScreen != MENU && player.canJump[0])
                    PlaySound(efeitos[0]);

                if(IsKeyDown(KEY_SPACE) && CurrentScreen!=MENU && player.canJump[1])
                    PlaySound(efeitos[1]);

                VerifyRooms(&CurrentRoom, &LastRoom, &player);

                DrawRoom(rooms[CurrentRoom], 1,musicas[CurrentRoom],player); //Printar Atras
                if (rooms[CurrentRoom].enemyNmbr > 0)
                    AnimEnemy(&rooms[CurrentRoom], CurrentRoom);

                if (player.CurrentLife > 0)
                    AnimPlayer(&player, &LastMove, &CurrentMove, rooms[CurrentRoom], &Timer);
                else
                {
                    AnimPlayerDeath(&player, &Timer);
                    PlaySound(efeitos[2]);
                }

                DrawRoom(rooms[CurrentRoom], 0,musicas[CurrentRoom],player); // Printar na Frente

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
    
    UnloadMusicStream(menuMusic);

    for(int i = 0;i<3;i++)
        UnloadSound(efeitos[i]);

    for(int i = 0;i<3;i++)
        UnloadMusicStream(musicas[i]);

    CloseAudioDevice();

    CloseWindow();
}