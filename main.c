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
        SetMusicVolume(rooms[i].SoundTrack, 0.02); 

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

    SetSoundVolume(menuInfo.MenuMusic,0.3);
    PlaySound(menuInfo.MenuMusic);

    PlaySound(player.SoundEffects[2]);
    PauseSound(player.SoundEffects[2]);

    for(int i = 0;i<4;i++) 
        SetSoundVolume(player.SoundEffects[i],0.09);
    
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

                //PlaySound(player.SoundEffects[3]);
                
                VerifyRooms(&CurrentEnemy, &CurrentRoom, &LastRoom, &player);

                DrawRoom(rooms[CurrentRoom], 1, player); //Printar Atras

                //if( ( IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT) ) && !player.attacking && player.canJump[0])
                    //PlaySound(player.SoundEffects[3]);

                
                //if( ( IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ) && !player.attacking && player.canJump[0])
                    //PlaySound(player.SoundEffects[3]);
                    
                if (rooms[CurrentRoom].enemyNmbr > 0){
                    //DrawRectangleRec(rooms[CurrentRoom].enemy[CurrentEnemy].SwordHitBox, PURPLE);
                    DrawRectangleRec(rooms[CurrentRoom].enemy[CurrentEnemy].HitBox, RED);
                    AnimEnemy(&player, &rooms[CurrentRoom].enemy[CurrentEnemy], CurrentRoom, &CurrentEnemy);
                }
                
                if (rooms[2].enemy[0].CurrentLife > 0){
                    rooms[2].enemy[1].position = rooms[2].enemy[0].position;
                    rooms[2].enemy[1].LastSide = rooms[2].enemy[0].LastSide;
                    rooms[2].enemy[1].CurrentTexture = rooms[2].enemy[1].Textures[rooms[2].enemy[1].LastSide];
                    rooms[2].enemy[1].FrameWidth = rooms[2].enemy[1].CurrentTexture.width/6.0;
                }

                if((rooms[0].enemy[1].CurrentLife < 1 && CurrentRoom == 0) ||
                   (rooms[2].enemy[1].CurrentLife < 1 && CurrentRoom == 2) ||
                   (rooms[3].enemy[1].CurrentLife < 1))
                {
                    player.DoubleJump = true;
                    player.CurrentLife = 10;
                }
                
                if (player.CurrentLife > 0){
                    //DrawRectangleRec(player.HitBox, BLUE);
                    //DrawRectangleRec(player.SwordHitBox, PURPLE);
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
    
    for (int i = 0 ; i < 13 ; i++)
        UnloadTexture(player.Textures[i]);

    free(player.Textures);

    for (int i = 0 ; i < 4 ; i++)
        UnloadSound(player.SoundEffects[i]);

    free(player.SoundEffects);

    for (int i = 0 ; i < 4 ; i++){
        UnloadTexture(rooms[i].texture);
        UnloadTexture(rooms[i].FrontTexture);
        free(rooms[i].platforms);
        
    }
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 2 ; j++){
            if (i == 0)
                for (int k = 0 ; k < 6 ; k++)
                    UnloadTexture(rooms[i].enemy[j].Textures[k]);
            if(i == 2)
                for (int k = 0 ; k < 8 ; k++)
                    UnloadTexture(rooms[i].enemy[j].Textures[k]);
        }

    free(rooms); 
    
    UnloadTexture(menuInfo.Texture);
    UnloadTexture(infoHud.TexturePLife);
    
    UnloadSound(menuInfo.MenuMusic);

    for(int i = 0 ; i < 4 ; i++)
        UnloadMusicStream(rooms[i].SoundTrack);


    CloseAudioDevice();

    CloseWindow();
}
