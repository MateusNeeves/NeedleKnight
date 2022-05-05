#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;

    Texture2D PlayerTextures[6];
    Texture2D CurrentTexture;
    float FrameWidth;
    int MaxFrames;
    int CurrentFrame;
    int LastSide;
} Player;

void CreatePlayer(Player *player);

void MovePlayer(Player *player, float delta, int *colision);

#endif