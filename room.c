#include "raylib.h"
#include "room.h"
#include <stdlib.h>

void CreateRooms(Room **rooms){

    (*rooms)[0].texture = LoadTexture("assets/Mapa/MapaInicio.png");

    (*rooms)[0].FrontTexture = LoadTexture("assets/Mapa/MapaInicioFrente.png");
    
    (*rooms)[0].platformNmbr = 9;

    Rectangle platforms[10] = {
        {0, 350, 540, 210},         // Plataforma Cima-Esquerda
        {0, 520, 150, 130},        // Plataforma Cima-Esquerda (Complemento)
        {0, 0, 1920, 100},        //Teto
        {0, 945, 1920, 140},     //Chao 
        {1410, 545, 510, 215},  // Plataforma Direita-Cima
        {780, 550, 215, 40},   // Plataforma Meio-Esquerda
        {1060, 720, 170, 40}, // Plataforma Meio-Direita
        {0, 500, 50, 600},   // Parede Esquerda
        {1905, 0, 25, 535},  // Parede Direita
    };

    (*rooms)[0].platforms = (Rectangle *) calloc((*rooms)[0].platformNmbr, sizeof(Rectangle));

    for (int i = 0 ; i < (*rooms)[0].platformNmbr ; i++)
         (*rooms)[0].platforms[i] = platforms[i];

}

void DrawRoom(Room *rooms, int Front_Back){
    Rectangle fundo = {0 , 0, rooms[0].texture.width , rooms[0].texture.height };

    Vector2 posFundo = {0, 0};
                    
    if (Front_Back == 1)
        DrawTextureRec(rooms[0].texture, fundo, posFundo, WHITE); 
    else
        DrawTextureRec(rooms[0].FrontTexture, fundo, posFundo, WHITE);
}
