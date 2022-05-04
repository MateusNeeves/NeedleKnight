#ifndef COLISION
#define COLISION

#include "raylib.h"
#include "player.h"
#include "room.h"


void ColisaoSupInf(Player *player, Room rooms, float delta, int *colision);

void ColisaoLateral(Player *player, Room rooms, float delta);

void HitObstacle(Player *player, float delta, int colision);

#endif