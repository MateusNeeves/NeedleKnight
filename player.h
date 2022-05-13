#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct Player {
    Vector2 position;
    Rectangle HitBox;
    Rectangle SwordHitBox;
    float speed;
    bool canJump[2];
    bool attacking;
    bool DoubleJump;
    bool Invulnerable;

    Texture2D *Textures;
    Texture2D CurrentTexture;
    float FrameWidth;
    int MaxFrames;
    int CurrentFrame;
    int LastSide;

    int MaxLife;
    int CurrentLife;

    Sound *SoundEffects;
    
} Player;

void CreatePlayer(Player *player);

void MovePlayer(Player **player, float delta);

#endif