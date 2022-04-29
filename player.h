#ifndef PLAYER
#define PLAYER

#include "raylib.h"
#include "colision.h"

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
} Player;

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta, Texture2D **Texture, Texture2D jogadorRunLeft, 
                  Texture2D jogadorRunRight, Texture2D jogadorStandLeft, Texture2D jogadorStandRight, float *FrameWidth, int *MaxFrames, short *LastSide);

#endif