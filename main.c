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

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Needle Knight");
    //ToggleFullscreen();
    SetTargetFPS(60);

    InitAudioDevice();

    Player player;
    CreatePlayer(&player);

    Room *rooms = NULL;
    rooms= (Room*) realloc(rooms, 4*sizeof(Room));
    CreateRooms(&rooms);

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

    Font font = LoadFontEx("Assets/HUD/BEECH.ttf", 72, 0, 0);
    
    const char MenuTexts[5][50] = {"needle",
                                   "knight",
                                   "start",
                                   "controls",
                                   "leave game"};

    Vector2 MenuTextsPos[5] = {{90, 70},
                               {90, 135},
                               {151, 425},
                               {110, 515},
                               {55, 600}};

    const char MenuArrow[] = "X";

    Vector2 MenuArrowPos[3][2] = {{{95, 442}, {335, 442}},
                                {{60, 533}, {370, 533}},
                                {{5, 617}, {423, 617}}};

    int MenuArrowNmbr = 0;


    const char PauseTexts[3][50] = {"pause", "resume", "menu"};

    Vector2 PauseTextsPos[3] = {{750, 155},
                                {850, 450},
                                {880, 570}};

    const char PauseArrow[] = "X";

    Vector2 PauseArrowPos[2][2] = {{{790, 470}, {1097, 470}},
                                   {{818, 588}, {1070, 588}}};

    int PauseArrowNmbr = 0;

    bool InControl = false;

    int Close = 0;

    while (!Close){
        
        BeginDrawing();
        switch (CurrentScreen){
           
            case MENU:{
                    AnimMenu(&menuInfo, &Timer);
                
                if (!InControl){
                    if (IsKeyPressed(KEY_ENTER) && MenuArrowNmbr == 0)
                    {   
                        StopSound(menuInfo.MenuMusic);
                        CurrentScreen = GAMEPLAY;
                    }

                    if (IsKeyPressed(KEY_ENTER) && MenuArrowNmbr == 1){
                        InControl = true;
                    }

                    if (IsKeyPressed(KEY_ENTER) && MenuArrowNmbr == 2)
                    {
                        Close = 1;
                    }

                    for(int i = 0 ; i < 2 ; i++){
                        DrawTextEx(font, MenuTexts[i], MenuTextsPos[i], 90, 0, WHITE);
                    }

                    for(int i = 2 ; i < 5 ; i++){
                        DrawTextEx(font, MenuTexts[i], MenuTextsPos[i], 72, 0, WHITE);
                    }

                    if (IsKeyPressed(KEY_DOWN))
                        MenuArrowNmbr++;

                    if (MenuArrowNmbr > 2)
                        MenuArrowNmbr = 0;

                    if (IsKeyPressed(KEY_UP))
                        MenuArrowNmbr--;

                    if (MenuArrowNmbr < 0)
                        MenuArrowNmbr = 2;

                    DrawTextEx(font, MenuArrow, MenuArrowPos[MenuArrowNmbr][0], 44, 0, WHITE);
                    DrawTextEx(font, MenuArrow, MenuArrowPos[MenuArrowNmbr][1], 44 , 0, WHITE);

                }

                else{
                    if (IsKeyPressed(KEY_ESCAPE))
                        InControl = false;
                    
                    DrawTexture(menuInfo.Controls, 0, 0, WHITE);
                }


                break;
            }
            
            case GAMEPLAY:{
                 
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    CurrentScreen = PAUSE;
                }

                if (player.CurrentLife <= 0 && player.CurrentFrame >= 3)
                {
                    CurrentScreen = GAMEOVER;
                }

                if (rooms[3].enemy[1].CurrentLife == 0 && rooms[3].enemy[1].CurrentFrame == 5)
                {
                    CurrentScreen = CREDITS;
                }

                VerifyRooms(&CurrentEnemy, &CurrentRoom, &LastRoom, &player, rooms);

                DrawRoom(rooms[CurrentRoom], 1, player); //Printar Atras

                if (rooms[CurrentRoom].enemyNmbr > 0){
                    //DrawRectangleRec(rooms[CurrentRoom].enemy[CurrentEnemy].SwordHitBox, PURPLE);
                    //DrawRectangleRec(rooms[CurrentRoom].enemy[CurrentEnemy].HitBox, RED);
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
                    //DrawRectangleRec(player.HitBox, BLUE);
                    //DrawRectangleRec(player.SwordHitBox, PURPLE);
                    AnimPlayer(&player, &LastMove, &CurrentMove, rooms[CurrentRoom], &Timer);
                }
                
                else{
                    AnimPlayerDeath(&player, &Timer, rooms[CurrentRoom]);
                }

                if(IsKeyDown(KEY_P))  //^Funcao de Desenvolvedor
                    player.CurrentLife = 10;

                PlayerAttackColision(player, &rooms[CurrentRoom].enemy[CurrentEnemy]);

                if (CurrentRoom != 1 && rooms[CurrentRoom].enemy[1].CurrentLife < 1 ){
                    rooms[CurrentRoom].platforms[rooms[CurrentRoom].platformNmbr - 1] = (Rectangle) {0, 0, 0, 0};
                } 

                if (CurrentRoom != 1 && CurrentRoom != 3)
                    VerifyDoors(player, &rooms[CurrentRoom]);

                EnemyColision (rooms[CurrentRoom].enemy[CurrentEnemy], &player);

                DrawRoom(rooms[CurrentRoom], 0, player); // Printar na Frente

                DamageHitEffect(player);

                DrawPlayerLife(player, infoHud, counter);

                //for (int i = 0; i < rooms[CurrentRoom].platformNmbr; i++) DrawRectangleRec(rooms[CurrentRoom].platforms[i], BLUE);  

                break;
            }

            case PAUSE:{
                
                if (PauseArrowNmbr == 0 && IsKeyPressed(KEY_ENTER))  {
                    CurrentScreen = GAMEPLAY;
                    SetSoundVolume(rooms[CurrentRoom].SoundTrack, 0.07);
                }

                if (PauseArrowNmbr == 1 && IsKeyPressed(KEY_ENTER)){
                    CurrentScreen = MENU;
                    PauseArrowNmbr = 0;
                }

                SetSoundVolume(rooms[CurrentRoom].SoundTrack, 0.04);

                DrawAll(player, rooms[CurrentRoom], rooms[CurrentRoom].enemy[CurrentEnemy], infoHud);

                DrawTexture(menuInfo.PauseEffect, 0, 0, WHITE);

                DrawTextEx(font, PauseTexts[0], PauseTextsPos[0], 162, 0, WHITE);
                DrawTextEx(font, PauseTexts[1], PauseTextsPos[1], 72, 0, WHITE);
                DrawTextEx(font, PauseTexts[2], PauseTextsPos[2], 72, 0, WHITE);


                if (IsKeyPressed(KEY_DOWN))
                    PauseArrowNmbr++;

                if (PauseArrowNmbr > 1)
                    PauseArrowNmbr = 0;

                if (IsKeyPressed(KEY_UP))
                    PauseArrowNmbr--;

                if (PauseArrowNmbr < 0)
                    PauseArrowNmbr = 1;

                DrawTextEx(font, PauseArrow, PauseArrowPos[PauseArrowNmbr][0], 44, 0, WHITE);
                DrawTextEx(font, PauseArrow, PauseArrowPos[PauseArrowNmbr][1], 44 , 0, WHITE);

                break;
            }

            case GAMEOVER:{
                
                if (IsKeyPressed(KEY_ESCAPE)){  
                    Close = true;
                }

                DrawAll(player, rooms[CurrentRoom], rooms[CurrentRoom].enemy[CurrentEnemy], infoHud);

                DrawTexture(menuInfo.PauseEffect, 0, 0, WHITE);

                DrawTexture(menuInfo.GameOver, 0, 0, WHITE);

                break;
            }

            case CREDITS:{
                
                if (IsKeyPressed(KEY_ESCAPE)){   
                    Close = true;
                }

                DrawAll(player, rooms[CurrentRoom], rooms[CurrentRoom].enemy[CurrentEnemy], infoHud);

                DrawTexture(menuInfo.PauseEffect, 0, 0, WHITE);

                DrawTexture(menuInfo.Credits, 0, 0, WHITE);

                break;
            }

            default:
                break;
        }

        

        EndDrawing();
    }
    
//& UNLOAD 

  //! Player
    for (int i = 0 ; i < 13 ; i++)
        UnloadTexture(player.Textures[i]);

    free(player.Textures);

    for (int i = 0 ; i < 3 ; i++)
        UnloadSound(player.SoundEffects[i]);

    free(player.SoundEffects);


  //! Rooms

    //* Room 0
        UnloadTexture(rooms[0].texture);
        UnloadTexture(rooms[0].FrontTexture);
        UnloadSound(rooms[0].SoundTrack);
        UnloadTexture(rooms[0].doors[0].Texture);

        //^ Enemy 0

            for(int i = 0 ; i < 6 ; i++)
                UnloadTexture(rooms[0].enemy[0].Textures[i]); 

            for(int i = 0 ; i < 4 ; i++)
                UnloadSound(rooms[0].enemy[0].SoundEffects[i]); 
            
        //^ Enemy 1

            for(int i = 0 ; i < 6 ; i++)
                UnloadTexture(rooms[0].enemy[1].Textures[i]); 

            for(int i = 0 ; i < 4 ; i++)
                UnloadSound(rooms[0].enemy[1].SoundEffects[i]); 
            
        free(rooms[0].enemy[0].Textures);
        free(rooms[0].enemy[1].Textures);
        free(rooms[0].platforms);


    //* Room 1
        UnloadTexture(rooms[1].texture);
        UnloadTexture(rooms[1].FrontTexture);
        UnloadSound(rooms[1].SoundTrack);
    
    //* Room 2
        UnloadTexture(rooms[2].texture);
        UnloadTexture(rooms[2].FrontTexture);
        UnloadSound(rooms[2].SoundTrack);
        UnloadTexture(rooms[2].doors[0].Texture);
        UnloadTexture(rooms[2].doors[1].Texture);

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

        free(rooms[2].enemy[0].Textures);
        free(rooms[2].enemy[1].Textures);
        free(rooms[2].platforms);

    //* Room 3
        UnloadTexture(rooms[3].texture);
        UnloadTexture(rooms[3].FrontTexture);
        UnloadSound(rooms[3].SoundTrack);

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
        
        free(rooms[3].enemy[0].Textures);
        free(rooms[3].enemy[1].Textures);
        free(rooms[3].platforms);

    free(rooms); 
    
  //! Menu-Hud
    UnloadTexture(menuInfo.Texture);
    UnloadTexture(infoHud.TexturePLife);
    UnloadSound(menuInfo.MenuMusic);

    UnloadTexture(menuInfo.PauseEffect);
    UnloadTexture(menuInfo.Controls);
    UnloadTexture(menuInfo.GameOver);
    UnloadTexture(menuInfo.Credits);


    CloseAudioDevice();

    CloseWindow();
}
