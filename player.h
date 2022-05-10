#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump[2];
    bool attacking;
    bool DoubleJump;

    Texture2D PlayerTextures[14];
    Texture2D CurrentTexture;
    float FrameWidth;
    int MaxFrames;
    int CurrentFrame;
    int LastSide;

    int MaxLife;
    int CurrentLife;
    
} Player;

void CreatePlayer(Player *player);

void MovePlayer(Player **player, float delta);

#endif