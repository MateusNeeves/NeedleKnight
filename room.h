#ifndef ROOM
#define ROOM

#include "raylib.h"
#include "player.h"

typedef struct Enemies {
    Vector2 position;
    Rectangle HitBox;
    Rectangle SwordHitBox;
    float speed;
    bool attacking;
    bool Invulnerable;

    Texture2D *Textures;
    Texture2D CurrentTexture;
    float FrameWidth;
    int CurrentFrame;
    int LastSide;
    int Damage;

    int MaxLife;
    int CurrentLife;
} Enemies;

typedef struct Room {
    Texture2D texture;
    Texture2D FrontTexture;
    Rectangle *platforms;
    int platformNmbr;
    Music SoundTrack;
    Enemies enemy[2];
    int enemyNmbr;
} Room;

void CreateRooms(Room **rooms);

void DrawRoom(Room rooms, int Front_Back, Player player);

void VerifyRooms(int *CurrentEnemy, int *CurrentRoom, int *LastRoom, Player *player);

#endif