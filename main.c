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
    //ToggleFullscreen();
    SetTargetFPS(60);

    InitAudioDevice();

    Player player;
    CreatePlayer(&player);

    Room *rooms = NULL;
    rooms= (Room*) realloc(rooms, 4*sizeof(Room));
    CreateRooms(&rooms);

    for(int i = 0; i < 4; i++)
        SetMusicVolume(rooms[i].SoundTrack, 0.07); 

    Texture2D *LastMove, *CurrentMove;
    float Timer = 0.0f;

    GameScreen CurrentScreen = MENU;
    
    Menu menuInfo;
    CreateMenuInfo(&menuInfo);

    Hud infoHud;
    CreateHud(&infoHud);
    
    float counter = 0;
    int CurrentRoom = 1;
    int CurrentEnemy = 0;
    int LastRoom = 1;

    PlaySound(menuInfo.MenuMusic);

    while (!WindowShouldClose()){
        
        BeginDrawing();
        switch (CurrentScreen){
           
            case MENU:{
                
                if (IsKeyPressed(KEY_ENTER))
                {   
                    StopSound(menuInfo.MenuMusic);
                    CurrentScreen = GAMEPLAY;
                }

                AnimMenu(&menuInfo, &Timer);
                break;
            }
            
            case GAMEPLAY:{
                 
                if (IsKeyPressed(KEY_ENTER))
                {
                    PlaySound(menuInfo.MenuMusic);
                    CurrentScreen = MENU;
                }

                VerifyRooms(&CurrentEnemy, &CurrentRoom, &LastRoom, &player);

                DrawRoom(rooms[CurrentRoom], 1, player); //Printar Atras

                if (rooms[CurrentRoom].enemyNmbr > 0){
                    DrawRectangleRec(rooms[CurrentRoom].enemy[CurrentEnemy].SwordHitBox, PURPLE);
                    DrawRectangleRec(rooms[CurrentRoom].enemy[CurrentEnemy].HitBox, RED);
                    AnimEnemy(&player, &rooms[CurrentRoom].enemy[CurrentEnemy], CurrentRoom, &CurrentEnemy);
                }

                if ((CurrentRoom == 2 && rooms[2].enemy[0].CurrentLife > 0) ||
                    (CurrentRoom == 3 && rooms[3].enemy[0].CurrentLife > 0))
                {
                    rooms[CurrentRoom].enemy[1].position = rooms[CurrentRoom].enemy[0].position;
                    rooms[CurrentRoom].enemy[1].LastSide = rooms[CurrentRoom].enemy[0].LastSide;
                    rooms[CurrentRoom].enemy[1].CurrentTexture = rooms[CurrentRoom].enemy[1].Textures[rooms[CurrentRoom].enemy[1].LastSide];
                    if (CurrentRoom == 2)
                        rooms[CurrentRoom].enemy[1].FrameWidth = rooms[CurrentRoom].enemy[1].CurrentTexture.width/6.0;
                    else
                        rooms[CurrentRoom].enemy[1].FrameWidth = rooms[CurrentRoom].enemy[1].CurrentTexture.width/9.0;

                } 

                if((rooms[0].enemy[1].CurrentLife < 1 && CurrentRoom == 0) ||
                   (rooms[2].enemy[1].CurrentLife < 1 && CurrentRoom == 2) ||
                   (rooms[3].enemy[1].CurrentLife < 1))
                {
                    player.DoubleJump = true;
                    player.CurrentLife = 10;
                }

                if (player.CurrentLife > 0){
                    DrawRectangleRec(player.HitBox, BLUE);
                    DrawRectangleRec(player.SwordHitBox, PURPLE);
                    AnimPlayer(&player, &LastMove, &CurrentMove, rooms[CurrentRoom], &Timer);
                }
                
                else
                {
                    AnimPlayerDeath(&player, &Timer, rooms[CurrentRoom]);
                }

                if(IsKeyDown(KEY_P))  //^Funcao de Desenvolvedor
                    player.CurrentLife = 10;

                PlayerAttackColision(player, &rooms[CurrentRoom].enemy[CurrentEnemy]);
                
                EnemyColision (rooms[CurrentRoom].enemy[CurrentEnemy], &player);

                DrawRoom(rooms[CurrentRoom], 0, player); // Printar na Frente

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
    
    //Player
    for (int i = 0 ; i < 13 ; i++)
        UnloadTexture(player.Textures[i]);

    free(player.Textures);

    for (int i = 0 ; i < 4 ; i++)
        UnloadSound(player.SoundEffects[i]);

    free(player.SoundEffects);


    //Rooms

    for (int i = 0 ; i < 4 ; i++){
        UnloadTexture(rooms[i].texture);
        UnloadTexture(rooms[i].FrontTexture);
        free(rooms[i].platforms);
    }

    for(int i = 0 ; i < 4 ; i++)
        UnloadMusicStream(rooms[i].SoundTrack);

    //* Room 0
        //^ Enemy 0 e 1
            for (int i = 0 ; i < 2 ; i++){
                for(int j = 0 ; j < 6 ; j++){
                    UnloadTexture(rooms[0].enemy[i].Textures[j]); 
                }
                for(int j = 0 ; j < 4 ; j++){
                    UnloadSound(rooms[0].enemy[i].SoundEffects[j]);
                }
            }
    
    //* Room 2
        //^ Enemy 0
            for (int i = 0 ; i < 8 ; i++)
                UnloadTexture(rooms[2].enemy[0].Textures[i]); 

            for (int i = 0 ; i < 3 ; i++)
                UnloadSound(rooms[2].enemy[0].SoundEffects[i]);

        //^ Enemy 1
            for (int i = 0 ; i < 6 ; i++)
                UnloadTexture(rooms[2].enemy[1].Textures[i]);

            for (int i = 0 ; i < 4 ; i++)
                UnloadSound(rooms[2].enemy[1].SoundEffects[i]);

    //* Room 3
        //^ Enemy 0
            for (int i = 0 ; i < 9 ; i++)
                UnloadTexture(rooms[3].enemy[0].Textures[i]);

            for (int i = 0 ; i < 5 ; i++)
                UnloadSound(rooms[3].enemy[0].SoundEffects[i]);

        //^ Enemy 1
            for (int i = 0 ; i < 10 ; i++)
                UnloadTexture(rooms[3].enemy[1].Textures[i]);
            
            for (int i = 0 ; i < 6 ; i++)
                UnloadSound(rooms[3].enemy[1].SoundEffects[i]);


    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 2 ; j++)
            free(rooms[i].enemy[j].Textures);


    free(rooms); 
    
    //Menu-Hud
    UnloadTexture(menuInfo.Texture);
    UnloadTexture(infoHud.TexturePLife);
    UnloadSound(menuInfo.MenuMusic);


    CloseAudioDevice();

    CloseWindow();
}
