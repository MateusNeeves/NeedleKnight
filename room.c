#include "raylib.h"
#include "room.h"
#include "player.h"
#include <stdlib.h>

#define Left 0

void CreateRooms(Room **rooms){

    //ROOM 0

        (*rooms)[0].texture = LoadTexture("assets/Mapa/Mapa0.png");

        (*rooms)[0].FrontTexture = LoadTexture("assets/Mapa/Mapa0Frente.png");
        
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

        (*rooms)[0].platforms = (Rectangle *) calloc((*rooms)[0].platformNmbr, sizeof(Rectangle));

        for (int i = 0 ; i < (*rooms)[0].platformNmbr ; i++)
            (*rooms)[0].platforms[i] = platforms0[i];

        (*rooms)[0].enemyNmbr = 1;

        // ENEMY 1 ROOM 0
            (*rooms)[0].enemy.position = (Vector2) {1650, 945};
            (*rooms)[0].enemy.speed = 400.0f;
            (*rooms)[0].enemy.attacking = false;

            // -20   60   10
            (*rooms)[0].enemy.Textures[0] = LoadTexture("Assets/Inimigos/MossCharger/AppearingLeft.png");
            (*rooms)[0].enemy.Textures[1] = LoadTexture("Assets/Inimigos/MoosCharger/AppearingRight.png");
            (*rooms)[0].enemy.Textures[2] = LoadTexture("Assets/Inimigos/MossCharger/ChargeLeft.png");
            (*rooms)[0].enemy.Textures[3] = LoadTexture("Assets/Inimigos/MossCharger/ChargeRight.png");
            (*rooms)[0].enemy.Textures[4] = LoadTexture("Assets/Inimigos/MossCharger/DisappearingLeft.png");
            (*rooms)[0].enemy.Textures[5] = LoadTexture("Assets/Inimigos/MossCharger/DisappearingRight.png");


            (*rooms)[0].enemy.CurrentTexture =  (*rooms)[0].enemy.Textures[0];

            (*rooms)[0].enemy.FrameWidth = (*rooms)[0].enemy.Textures[0].width/6;
            (*rooms)[0].enemy.MaxFrames = 6;
            (*rooms)[0].enemy.CurrentFrame = 0;
            (*rooms)[0].enemy.LastSide = Left;

            (*rooms)[0].enemy.MaxLife = 5;
            (*rooms)[0].enemy.CurrentLife = 5;



    //ROOM 1

        (*rooms)[1].texture = LoadTexture("assets/Mapa/Mapa1.png");

        (*rooms)[1].FrontTexture = LoadTexture("assets/Mapa/Mapa1Frente.png");
        
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


    // ROOM 2

        (*rooms)[2].texture = LoadTexture("assets/Mapa/Mapa2.png");

        (*rooms)[2].FrontTexture = LoadTexture("assets/Mapa/Mapa2Frente.png");
        
        (*rooms)[2].platformNmbr = 4;

        Rectangle platforms2[4] = {
            {0, 0, 1920, 130},         // Teto
            {0, 975, 1920, 110},      // Chao 
            {0, 135, 65, 695},       // Parede Esquerda
            {1875,145, 50, 675}     // Parede Direita
        };

        (*rooms)[2].platforms = (Rectangle *) calloc((*rooms)[2].platformNmbr, sizeof(Rectangle));

        for (int i = 0 ; i < (*rooms)[2].platformNmbr ; i++)
            (*rooms)[2].platforms[i] = platforms2[i];

        (*rooms)[2].enemyNmbr = 0;


    //ROOM 3

        (*rooms)[3].texture = LoadTexture("assets/Mapa/Mapa3.png");

        (*rooms)[3].FrontTexture = LoadTexture("assets/Mapa/Mapa3Frente.png");
        
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

        (*rooms)[3].enemyNmbr = 0;


}

void DrawRoom(Room rooms, int Front_Back,Music ostSala,Player player){
    if(player.CurrentLife>0)
    {
        UpdateMusicStream(ostSala);
        PlayMusicStream(ostSala);
    }

    Rectangle fundo = {0 , 0, rooms.texture.width , rooms.texture.height };

    Vector2 posFundo = {0, 0};
                    
    if (Front_Back == 1)
        DrawTextureRec(rooms.texture, fundo, posFundo, WHITE); 
    else
        DrawTextureRec(rooms.FrontTexture, fundo, posFundo, WHITE);
}

void VerifyRooms(int *CurrentRoom, int *LastRoom, Player *player){
    if (player->position.x < 0 && player->position.y > 1080){ //Porta Esquerda
        *LastRoom = *CurrentRoom;
        *CurrentRoom += 1;

        if (*LastRoom == 0 && *CurrentRoom == 1){
            player->position = (Vector2) {1850, 945};
        }

        else if (*LastRoom == 1 && *CurrentRoom == 2){
            player->position = (Vector2) {1860, 975};
        }

        if (*LastRoom == 2 && *CurrentRoom == 3){
            player->position = (Vector2) {1880, 310};
        }
    }

    else if (player->position.x > 1920 && player->position.y > 1080){ // Porta Direita
        *LastRoom = *CurrentRoom;
        *CurrentRoom -= 1;

        if (*LastRoom == 1 && *CurrentRoom == 0){
            player->position = (Vector2) {50, 955};
        }
    }
}