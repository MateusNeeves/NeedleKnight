#include "raylib.h"
#include "room.h"
#include "player.h"
#include <stdlib.h>

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

    //ROOM 3

    (*rooms)[2].texture = LoadTexture("assets/Mapa/Mapa3.png");

    (*rooms)[2].FrontTexture = LoadTexture("assets/Mapa/Mapa3Frente.png");
    
    (*rooms)[2].platformNmbr = 7;

    Rectangle platforms2[7] = {
        {0, 0, 1920, 110},            // Teto
        {0, 965, 1920, 110},           //Chao Meio
        {0, 855, 310, 230},         // Chao Esquerda
        {1630, 860, 310, 230},     // Chao Direita
        {1710, 320, 215, 80},     // Plataforma Direita
        {0, 0, 20, 820},         // Parede Esquerda
        {1900,440, 20, 450}     // Parede Esquerda
    };

    (*rooms)[2].platforms = (Rectangle *) calloc((*rooms)[2].platformNmbr, sizeof(Rectangle));

    for (int i = 0 ; i < (*rooms)[2].platformNmbr ; i++)
         (*rooms)[2].platforms[i] = platforms2[i];

}

void DrawRoom(Room rooms, int Front_Back){
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
    }

    else if (player->position.x > 1920 && player->position.y > 1080){ // Porta Direita
        *LastRoom = *CurrentRoom;
        *CurrentRoom -= 1;

        if (*LastRoom == 1 && *CurrentRoom == 0){
            player->position = (Vector2) {50, 955};
        }
    }
}