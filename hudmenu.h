#ifndef HUDMENU
#define HUDMENU

#include "raylib.h"
#include "player.h"

typedef struct Hud {
    Texture2D TexturePLife;
} Hud;

typedef enum GameScreen{ 
    MENU = 0, GAMEPLAY
} GameScreen;

typedef struct Menu{
    Texture2D Texture;
    int CurrentFrame;
} Menu;

void CreateMenuInfo(Menu *menuInfo);

void CreateHud(Hud *infoHud);

void DrawPlayerLife(Player player, Hud infoHud, float counter);


#endif