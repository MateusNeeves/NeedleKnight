#ifndef COLISION
#define COLISION

#include "raylib.h"
#include "player.h"

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
} EnvItem;

void ColisaoSupInf(Player *player, EnvItem *envItems, int envItemsLength, Texture2D **Texture, float delta, int *colision);

void ColisaoLateral(Player *player, EnvItem *envItems, int envItemsLength, Texture2D **Texture, float delta, 
               float *FrameWidth, short *LastSide);

void HitObstacle(Player *player, float delta, int colision);

#endif