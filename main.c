#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    InitAudioDevice();

    Music menuMusic = LoadMusicStream("Assets/Musicas/MenuMusic.mp3"); // OST menu

    Music *musicas = calloc(4, sizeof(Music));

    char diretorioMenu[30];

    for(int i = 0; i < 4 ; i++){
        sprintf(diretorioMenu, "Assets/Musicas/OST-Room%d.mp3", i);
        musicas[i] = LoadMusicStream(diretorioMenu);
    } 

    for(int i = 0;i<4;i++)
        SetMusicVolume(musicas[i], 0.07); 

    Sound *efeitos =NULL;
    efeitos = (Sound*) realloc(efeitos, 3 * sizeof(Sound));
    
    efeitos[0] = LoadSound("Assets/EfeitosSonoros/PlayerAttack.mp3");
    efeitos[1] = LoadSound("Assets/EfeitosSonoros/PlayerJump.mp3");
    efeitos[2] = LoadSound("Assets/EfeitosSonoros/Hornet_Fight_Death_01.mp3");

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

    PlayMusicStream(menuMusic);
    
    while (!WindowShouldClose()){
        
        BeginDrawing();
        switch (CurrentScreen){
           
            case MENU:{
                
                if (IsKeyPressed(KEY_ENTER))
                {   
                    StopMusicStream(menuMusic);
                    CurrentScreen = GAMEPLAY;
                }
                UpdateMusicStream(menuMusic);

                AnimMenu(&menuInfo, &Timer, diretorio);
                break;
            }
            
            case GAMEPLAY:{
                 
                if (IsKeyPressed(KEY_ENTER))
                {
                    PlayMusicStream(menuMusic);
                    CurrentScreen = MENU;
                }
                
                if(IsKeyDown(KEY_Z) && CurrentScreen != MENU && player.canJump[0])
                    PlaySound(efeitos[0]);

                if(IsKeyDown(KEY_SPACE) && CurrentScreen!=MENU && player.canJump[1])
                    PlaySound(efeitos[1]);

                VerifyRooms(&CurrentRoom, &LastRoom, &player);

                DrawRoom(rooms[CurrentRoom], 1,musicas[CurrentRoom],player); //Printar Atras

                if (rooms[CurrentRoom].enemyNmbr > 0){
                    //DrawRectangleRec(rooms[0].enemy.HitBox, RED);
                    AnimEnemy(&rooms[CurrentRoom], CurrentRoom);
                }

                if (player.CurrentLife > 0){
                    //DrawRectangleRec(player.HitBox, BLUE);
                    AnimPlayer(&player, &LastMove, &CurrentMove, rooms[CurrentRoom], &Timer);
                }
                
                else
                {
                    AnimPlayerDeath(&player, &Timer, rooms[CurrentRoom]);
                    PlaySound(efeitos[2]);
                }

                if(IsKeyDown(KEY_P))  //^Funcao de Desenvolvedor
                    player.CurrentLife = 2;

                if (player.attacking)
                    PlayerAttackColision(player, &rooms[CurrentRoom].enemy);
                
                MossChargerColision (rooms[CurrentRoom].enemy, &player);

                DrawRoom(rooms[CurrentRoom], 0,musicas[CurrentRoom],player); // Printar na Frente

                DamageHitEffect(player);

                DrawPlayerLife(player, infoHud, counter);

                //for (int i = 0; i < rooms[CurrentRoom].platformNmbr; i++) DrawRectangleRec(rooms[CurrentRoom].platforms[i], BLUE);  

                break;
            }

            default:
                break;
        }

        EndDrawing();
    }
    
    for (int i = 0 ; i < 13 ; i++)
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