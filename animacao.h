#ifndef ANIMACAO
#define ANIMACAO

#include "raylib.h"
#include "animacao.h"
#include "player.h"
#include "room.h"
#include "hudmenu.h"

void AnimMenu(Menu *menuInfo, float *Timer, char *diretorio);

void AnimPlayer(Player *player, Texture2D **LastMove, Texture2D **CurrentMove, Room rooms, float *Timer);

void AnimPlayerDeath(Player *player, float *Timer, Room rooms);

void AnimMossCharger(Enemies *enemy);

void AnimMossChargerDeath(Enemies *enemy);

void AnimEnemy(Room *rooms, int CurrentRoom);

#endif