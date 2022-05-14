#include "raylib.h"
#include "room.h"
#include "player.h"
#include <stdlib.h>

#define Left 0
#define Right 1

void CreateRooms(Room **rooms){

    //^ ROOM 0

        (*rooms)[0].texture = LoadTexture("Assets/Mapa/Mapa0.png");

        (*rooms)[0].FrontTexture = LoadTexture("Assets/Mapa/Mapa0Frente.png");

        (*rooms)[0].SoundTrack = LoadMusicStream("Assets/Musicas/ST-Room0.mp3");
        
        (*rooms)[0].platformNmbr = 7;

        Rectangle platforms0[7] = {   
            {0, 0, 50, 745},            // Parede Esquerda
            {1880, 0, 36, 1080},       // Parede Direita
            {0, 955, 1920, 126},      // Chao
            {0, 0, 1920, 120},       // Teto
            {570, 730, 190, 40},    // Plataforma Esquerda
            {1160, 730, 190, 40},  // Plataforma Direita
            {880, 530, 190, 40}   // Plataforma Meio
        };

        (*rooms)[0].platforms = (Rectangle*) calloc((*rooms)[0].platformNmbr, sizeof(Rectangle));

        for (int i = 0 ; i < (*rooms)[0].platformNmbr ; i++)
            (*rooms)[0].platforms[i] = platforms0[i];

        (*rooms)[0].enemyNmbr = 2;

        //^ ENEMY 0 

            (*rooms)[0].enemy[0].position = (Vector2) {1650, 945};
            (*rooms)[0].enemy[0].speed = 400.0f;
            (*rooms)[0].enemy[0].attacking = false;
            (*rooms)[0].enemy[0].Invulnerable = false;

            // -20   60   10

            (*rooms)[0].enemy[0].Textures = (Texture2D*) calloc (6, sizeof(Texture2D));

            (*rooms)[0].enemy[0].Textures[0] = LoadTexture("Assets/Inimigos/MossCharger/AppearingLeft.png");
            (*rooms)[0].enemy[0].Textures[1] = LoadTexture("Assets/Inimigos/MossCharger/AppearingRight.png");
            (*rooms)[0].enemy[0].Textures[2] = LoadTexture("Assets/Inimigos/MossCharger/ChargeLeft.png");
            (*rooms)[0].enemy[0].Textures[3] = LoadTexture("Assets/Inimigos/MossCharger/ChargeRight.png");
            (*rooms)[0].enemy[0].Textures[4] = LoadTexture("Assets/Inimigos/MossCharger/DisappearingLeft.png");
            (*rooms)[0].enemy[0].Textures[5] = LoadTexture("Assets/Inimigos/MossCharger/DisappearingRight.png");


            (*rooms)[0].enemy[0].CurrentTexture =  (*rooms)[0].enemy[0].Textures[0];

            (*rooms)[0].enemy[0].FrameWidth = (*rooms)[0].enemy[0].Textures[0].width/6;
            (*rooms)[0].enemy[0].CurrentFrame = 0;
            (*rooms)[0].enemy[0].LastSide = Left;

            (*rooms)[0].enemy[0].MaxLife = 5;
            (*rooms)[0].enemy[0].CurrentLife = 5;
            (*rooms)[0].enemy[0].Damage = 1;

        //^ ENEMY 1
            (*rooms)[0].enemy[1].position = (Vector2) {1650, 945};
            (*rooms)[0].enemy[1].speed = 400.0f;
            (*rooms)[0].enemy[1].attacking = false;
            (*rooms)[0].enemy[1].Invulnerable = false;


            (*rooms)[0].enemy[1].Textures = (Texture2D*) calloc (6, sizeof(Texture2D));

            (*rooms)[0].enemy[1].Textures[0] = LoadTexture("Assets/Inimigos/MassiveMossCharger/AppearingLeft.png");
            (*rooms)[0].enemy[1].Textures[1] = LoadTexture("Assets/Inimigos/MassiveMossCharger/AppearingRight.png");
            (*rooms)[0].enemy[1].Textures[2] = LoadTexture("Assets/Inimigos/MassiveMossCharger/ChargeLeft.png");
            (*rooms)[0].enemy[1].Textures[3] = LoadTexture("Assets/Inimigos/MassiveMossCharger/ChargeRight.png");
            (*rooms)[0].enemy[1].Textures[4] = LoadTexture("Assets/Inimigos/MassiveMossCharger/DisappearingLeft.png");
            (*rooms)[0].enemy[1].Textures[5] = LoadTexture("Assets/Inimigos/MassiveMossCharger/DisappearingRight.png");


            (*rooms)[0].enemy[1].CurrentTexture =  (*rooms)[0].enemy[1].Textures[0];

            (*rooms)[0].enemy[1].FrameWidth = (*rooms)[0].enemy[1].Textures[0].width/6;
            (*rooms)[0].enemy[1].CurrentFrame = 0;
            (*rooms)[0].enemy[1].LastSide = Left;

            (*rooms)[0].enemy[1].MaxLife = 10;
            (*rooms)[0].enemy[1].CurrentLife = 10;
            (*rooms)[0].enemy[1].Damage = 1;


    //^ ROOM 1

        (*rooms)[1].texture = LoadTexture("Assets/Mapa/Mapa1.png");

        (*rooms)[1].FrontTexture = LoadTexture("Assets/Mapa/Mapa1Frente.png");

        (*rooms)[1].SoundTrack = LoadMusicStream("Assets/Musicas/ST-Room1.mp3");
        
        (*rooms)[1].platformNmbr = 9;

        Rectangle platforms1[10] = {
            {0, 350, 520, 210},         // Plataforma Cima-Esquerda
            {0, 520, 150, 130},        // Plataforma Cima-Esquerda (Complemento)
            {0, 0, 1920, 100},        //Teto
            {0, 945, 1920, 140},     //Chao 
            {1410, 545, 510, 215},  // Plataforma Direita-Cima
            {780, 550, 215, 40},   // Plataforma Meio-Esquerda
            {1060, 720, 170, 40}, // Plataforma Meio-Direita
            {0, 500, 50, 600},   // Parede Esquerda
            {1905, 0, 25, 535},  // Parede Direita
        };

        (*rooms)[1].platforms = (Rectangle *) calloc((*rooms)[1].platformNmbr, sizeof(Rectangle));

        for (int i = 0 ; i < (*rooms)[1].platformNmbr ; i++)
            (*rooms)[1].platforms[i] = platforms1[i];
        
        (*rooms)[1].enemyNmbr = 0;


    //^ ROOM 2

        (*rooms)[2].texture = LoadTexture("Assets/Mapa/Mapa2.png");

        (*rooms)[2].FrontTexture = LoadTexture("Assets/Mapa/Mapa2Frente.png");

        (*rooms)[2].SoundTrack = LoadMusicStream("Assets/Musicas/ST-Room2.mp3");

        (*rooms)[2].platformNmbr = 4;

        Rectangle platforms2[4] = {
            {0, 0, 1920, 130},         // Teto
            {0, 975, 1920, 110},      // Chao 
            {0, 135, 50, 655},       // Parede Esquerda
            {1875,145, 50, 655}     // Parede Direita
        };

        (*rooms)[2].platforms = (Rectangle *) calloc((*rooms)[2].platformNmbr, sizeof(Rectangle));

        for (int i = 0 ; i < (*rooms)[2].platformNmbr ; i++)
            (*rooms)[2].platforms[i] = platforms2[i];

        (*rooms)[2].enemyNmbr = 2;

        //^ ENEMY 0 
            (*rooms)[2].enemy[0].position = (Vector2) {135, 975};
            (*rooms)[2].enemy[0].speed = 330.0f;
            (*rooms)[2].enemy[0].attacking = false;
            (*rooms)[2].enemy[0].Invulnerable = false;


            (*rooms)[2].enemy[0].Textures = (Texture2D*) calloc (8, sizeof(Texture2D));


            (*rooms)[2].enemy[0].Textures[0] = LoadTexture("Assets/Inimigos/KingsMould/Sleeping.png");
            (*rooms)[2].enemy[0].Textures[1] = LoadTexture("Assets/Inimigos/KingsMould/Waking.png");
            (*rooms)[2].enemy[0].Textures[2] = LoadTexture("Assets/Inimigos/KingsMould/RunLeft.png");
            (*rooms)[2].enemy[0].Textures[3] = LoadTexture("Assets/Inimigos/KingsMould/RunRight.png");
            (*rooms)[2].enemy[0].Textures[4] = LoadTexture("Assets/Inimigos/KingsMould/AttackLeft.png");
            (*rooms)[2].enemy[0].Textures[5] = LoadTexture("Assets/Inimigos/KingsMould/AttackRight.png");
            (*rooms)[2].enemy[0].Textures[6] = LoadTexture("Assets/Inimigos/KingsMould/DeathLeft.png");
            (*rooms)[2].enemy[0].Textures[7] = LoadTexture("Assets/Inimigos/KingsMould/DeathRight.png");

            (*rooms)[2].enemy[0].CurrentTexture =  (*rooms)[2].enemy[0].Textures[0];

            (*rooms)[2].enemy[0].FrameWidth = (*rooms)[2].enemy[0].Textures[0].width;
            (*rooms)[2].enemy[0].CurrentFrame = 0;
            (*rooms)[2].enemy[0].LastSide = Right;

            (*rooms)[2].enemy[0].MaxLife = 7;
            (*rooms)[2].enemy[0].CurrentLife = 1;
            (*rooms)[2].enemy[0].Damage = 2;

        //^ ENEMY 1 
            (*rooms)[2].enemy[1].position = (Vector2) {0, 0};
            (*rooms)[2].enemy[1].speed = 500.0f;
            (*rooms)[2].enemy[1].attacking = false;
            (*rooms)[2].enemy[1].Invulnerable = false;


            (*rooms)[2].enemy[1].Textures = (Texture2D*) calloc (6, sizeof(Texture2D));


            (*rooms)[2].enemy[1].Textures[0] = LoadTexture("Assets/Inimigos/TheCollector/AppearingLeft.png");
            (*rooms)[2].enemy[1].Textures[1] = LoadTexture("Assets/Inimigos/TheCollector/AppearingRight.png");
            (*rooms)[2].enemy[1].Textures[2] = LoadTexture("Assets/Inimigos/TheCollector/JumpLeft.png");
            (*rooms)[2].enemy[1].Textures[3] = LoadTexture("Assets/Inimigos/TheCollector/JumpRight.png");
            (*rooms)[2].enemy[1].Textures[4] = LoadTexture("Assets/Inimigos/TheCollector/DeathLeft.png");
            (*rooms)[2].enemy[1].Textures[5] = LoadTexture("Assets/Inimigos/TheCollector/DeathRight.png");

            (*rooms)[2].enemy[1].CurrentFrame = 0;

            (*rooms)[2].enemy[1].MaxLife = 10;
            (*rooms)[2].enemy[1].CurrentLife = 10;
            (*rooms)[2].enemy[1].Damage = 2;

    //^ ROOM 3

        (*rooms)[3].texture = LoadTexture("Assets/Mapa/Mapa3.png");

        (*rooms)[3].FrontTexture = LoadTexture("Assets/Mapa/Mapa3Frente.png");
        
        (*rooms)[3].SoundTrack = LoadMusicStream("Assets/Musicas/ST-Room3.mp3");

        (*rooms)[3].platformNmbr = 7;

        Rectangle platforms3[7] = {
            {0, 0, 1920, 110},            // Teto
            {0, 980, 1920, 110},         //Chao Meio
            {0, 850, 310, 230},         // Chao Esquerda
            {1630, 850, 310, 230},     // Chao Direita
            {1710, 310, 215, 80},     // Plataforma Direita
            {0, 0, 20, 820},         // Parede Esquerda
            {1900,440, 20, 450}     // Parede Direita
        };

        (*rooms)[3].platforms = (Rectangle *) calloc((*rooms)[3].platformNmbr, sizeof(Rectangle));

        for (int i = 0 ; i < (*rooms)[3].platformNmbr ; i++)
            (*rooms)[3].platforms[i] = platforms3[i];

        (*rooms)[3].enemyNmbr = 2;

        //^ ENEMY 0 
            (*rooms)[3].enemy[0].position = (Vector2) {185, 850};
            (*rooms)[3].enemy[0].attacking = false;
            (*rooms)[3].enemy[0].Invulnerable = false;


            (*rooms)[3].enemy[0].Textures = (Texture2D*) calloc (9, sizeof(Texture2D));


            (*rooms)[3].enemy[0].Textures[0] = LoadTexture("Assets/Inimigos/NightmareKing/Idle.png");
            (*rooms)[3].enemy[0].Textures[1] = LoadTexture("Assets/Inimigos/NightmareKing/DisappearingLeft.png");
            (*rooms)[3].enemy[0].Textures[2] = LoadTexture("Assets/Inimigos/NightmareKing/DisappearingRight.png");
            (*rooms)[3].enemy[0].Textures[3] = LoadTexture("Assets/Inimigos/NightmareKing/AppearingLeft.png");
            (*rooms)[3].enemy[0].Textures[4] = LoadTexture("Assets/Inimigos/NightmareKing/AppearingRight.png");
            (*rooms)[3].enemy[0].Textures[5] = LoadTexture("Assets/Inimigos/NightmareKing/AttackLeft.png");
            (*rooms)[3].enemy[0].Textures[6] = LoadTexture("Assets/Inimigos/NightmareKing/AttackRight.png");
            (*rooms)[3].enemy[0].Textures[7] = LoadTexture("Assets/Inimigos/NightmareKing/DeathLeft.png");
            (*rooms)[3].enemy[0].Textures[8] = LoadTexture("Assets/Inimigos/NightmareKing/DeathRight.png");


            (*rooms)[3].enemy[0].CurrentTexture =  (*rooms)[3].enemy[0].Textures[0];

            (*rooms)[3].enemy[0].FrameWidth = (*rooms)[3].enemy[0].Textures[0].width/4.0;
            (*rooms)[3].enemy[0].CurrentFrame = 0;
            (*rooms)[3].enemy[0].LastSide = Right;

            (*rooms)[3].enemy[0].MaxLife = 10;
            (*rooms)[3].enemy[0].CurrentLife = 1;
            (*rooms)[3].enemy[0].Damage = 2;


        //^ ENEMY 1 
            (*rooms)[3].enemy[1].position = (Vector2) {0, 0};
            (*rooms)[3].enemy[1].attacking = false;
            (*rooms)[3].enemy[1].Invulnerable = false;


            (*rooms)[3].enemy[1].Textures = (Texture2D*) calloc (10, sizeof(Texture2D));


            (*rooms)[3].enemy[1].Textures[0] = LoadTexture("Assets/Inimigos/Grimm/BegginingLeft.png");
            (*rooms)[3].enemy[1].Textures[1] = LoadTexture("Assets/Inimigos/Grimm/BegginingRight.png");
            (*rooms)[3].enemy[1].Textures[2] = LoadTexture("Assets/Inimigos/Grimm/DisappearingLeft.png");
            (*rooms)[3].enemy[1].Textures[3] = LoadTexture("Assets/Inimigos/Grimm/DisappearingRight.png");
            (*rooms)[3].enemy[1].Textures[4] = LoadTexture("Assets/Inimigos/Grimm/AppearingLeft.png");
            (*rooms)[3].enemy[1].Textures[5] = LoadTexture("Assets/Inimigos/Grimm/AppearingRight.png");
            (*rooms)[3].enemy[1].Textures[6] = LoadTexture("Assets/Inimigos/Grimm/AttackLeft.png");
            (*rooms)[3].enemy[1].Textures[7] = LoadTexture("Assets/Inimigos/Grimm/AttackRight.png");
            (*rooms)[3].enemy[1].Textures[8] = LoadTexture("Assets/Inimigos/Grimm/DeathLeft.png");
            (*rooms)[3].enemy[1].Textures[9] = LoadTexture("Assets/Inimigos/Grimm/DeathRight.png");
            
            (*rooms)[3].enemy[1].CurrentFrame = 0;

            (*rooms)[3].enemy[1].MaxLife = 10;
            (*rooms)[3].enemy[1].CurrentLife = 1;
            (*rooms)[3].enemy[1].Damage = 2;
}

void DrawRoom(Room rooms, int Front_Back,Player player){
    if(player.CurrentLife>0)
    {
        UpdateMusicStream(rooms.SoundTrack);
        PlayMusicStream(rooms.SoundTrack);
    }

    Rectangle fundo = {0 , 0, rooms.texture.width , rooms.texture.height };

    Vector2 posFundo = {0, 0};
                    
    if (Front_Back == 1)
        DrawTextureRec(rooms.texture, fundo, posFundo, WHITE); 
    else
        DrawTextureRec(rooms.FrontTexture, fundo, posFundo, WHITE);
}

void VerifyRooms(int *CurrentEnemy, int *CurrentRoom, int *LastRoom, Player *player){
    if (player->position.x < 0){ //Porta Esquerda
        *LastRoom = *CurrentRoom;
        *CurrentRoom += 1;
        *CurrentEnemy = 0;

        if (*LastRoom == 0 && *CurrentRoom == 1){
            player->position = (Vector2) {1850, 945};
        }

        if (*LastRoom == 1 && *CurrentRoom == 2){
            player->position = (Vector2) {1860, 975};
        }

        if (*LastRoom == 2 && *CurrentRoom == 3){
            player->position = (Vector2) {1880, 310};
        }
    }

    else if (player->position.x > 1920){ // Porta Direita
        *LastRoom = *CurrentRoom;
        *CurrentRoom -= 1;
        *CurrentEnemy = 0;

        if (*LastRoom == 3 && *CurrentRoom == 2){
            player->position = (Vector2) {50, 975};
        }

        if (*LastRoom == 2 && *CurrentRoom == 1){
            player->position = (Vector2) {60, 350};
        }

        if (*LastRoom == 1 && *CurrentRoom == 0){
            player->position = (Vector2) {50, 955};
        }
    }
}