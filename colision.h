#ifndef COLISION
#define COLISION

#include "raylib.h"
#include "player.h"
#include "room.h"


void ColisaoSupInf(Player **player, Room rooms, float delta);

void ColisaoLateral(Player **player, Room rooms, float delta);

#endif