#ifndef ANIMACAO
#define ANIMACAO

#include "raylib.h"
#include "animacao.h"
#include "player.h"
#include "room.h"
#include "hudmenu.h"

void AnimMenu(Menu *menuInfo, float *Timer);

void AnimPlayer(Player *player, Texture2D **LastMove, Texture2D **CurrentMove, Room rooms, float *Timer);

void AnimPlayerDeath(Player *player, float *Timer, Room rooms);

void AnimMossCharger(Enemies **enemy, int CurrentEnemy);

void AnimMossChargerDeath(Enemies **enemy, int **CurrentEnemy, float *Timer2);

void AnimKingsMould(Enemies **enemy, Player **player);

void AnimKingsMouldDeath(Enemies **enemy, int **CurrentEnemy);

void AnimTheCollector(Enemies **enemy, Player **player, int *inAnim);

void AnimNightmareKing(Enemies **enemy, Player **player);

void AnimNightmareKingDeath(Enemies **enemy, int **CurrentEnemy);

void AnimGrimm(Enemies **enemy, Player **player);

void AnimGrimmDeath(Enemies **enemy, int **CurrentEnemy);

void AnimEnemy(Player *player, Enemies *enemy, int CurrentRoom, int *CurrentEnemy);

#endif