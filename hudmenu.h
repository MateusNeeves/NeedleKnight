#ifndef HUDMENU
#define HUDMENU

#include "raylib.h"
#include "player.h"
#include "room.h"

typedef struct Hud {
    Texture2D TexturePLife;
} Hud;

typedef enum GameScreen{ 
    MENU = 0, GAMEPLAY, PAUSE, GAMEOVER, CREDITS
} GameScreen;

typedef struct Menu{
    Texture2D Texture;
    int CurrentFrame;
    Sound MenuMusic;
    Texture2D PauseEffect;
    Texture2D Controls;
    Texture2D GameOver;
    Texture2D Credits;
} Menu;

void CreateMenuInfo(Menu *menuInfo);

void CreateHud(Hud *infoHud);

void DrawPlayerLife(Player player, Hud infoHud, float counter);

void DamageHitEffect(Player player);

void DrawAll(Player player, Room rooms, Enemies enemy, Hud infoHud);

void ResetGame(Player *player, Room **rooms);

#endif