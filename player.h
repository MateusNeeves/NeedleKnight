#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;

    Texture2D PlayerTextures[4];
    Texture2D CurrentTexture;
    float FrameWidth;
    int MaxFrames;
    int CurrentFrame;
    int LastSide;
} Player;

void CreatePlayer(Player *player);

void MovePlayer(Player *player, float delta);

#endif