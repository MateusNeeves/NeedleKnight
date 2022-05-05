#include "raylib.h"
#include "room.h"
#include <stdlib.h>

void CreateRooms(Room **rooms){

    (*rooms)[0].textureRoom = LoadTexture("assets/Mapa/MapaInicio.png");

    (*rooms)[0].FrontTextureRoom = LoadTexture("assets/Mapa/MapaInicioFrente.png");
    
    (*rooms)[0].platformNmbr = 9;

    Rectangle platforms[9] = {
        {0, 350, 540, 210},         // Plataforma Cima-Esquerda
        {0, 520, 150, 130},        // Plataforma Cima-Esquerda (Complemento)
        {0, 0, 1920, 100},        //Teto
        {0, 936, 1920, 140},     //Chao Baixo 
        {1410, 545, 510, 225},  // Plataforma Direita-Cima
        {780, 550, 215, 40},   // Plataforma Meio-Esquerda
        {1060, 720, 170, 50}, // Plataforma Meio-Direita
        {0, 500, 50, 600},   // Parede Esquerda
        {1905, 0, 25, 535}  // Parede Direita
    };

    (*rooms)[0].platforms = (Rectangle *) calloc(8, sizeof(Rectangle));

    for (int i = 0 ; i < (*rooms)[0].platformNmbr ; i++)
         (*rooms)[0].platforms[i] = platforms[i];

}
