#ifndef ROOM
#define ROOM

#include "raylib.h"
#include "player.h"

typedef struct Enemies {
    Vector2 position;
    float speed;
    bool attacking;

    Texture2D Textures[6];
    Texture2D CurrentTexture;
    float FrameWidth;
    int MaxFrames;
    int CurrentFrame;
    int LastSide;

    int MaxLife;
    int CurrentLife;
} Enemies;

typedef struct Room {
    Texture2D texture;
    Texture2D FrontTexture;
    Rectangle *platforms;
    int platformNmbr;
    Enemies enemy;
    int enemyNmbr;
} Room;

void CreateRooms(Room **rooms);

void DrawRoom(Room rooms, int Front_Back);

void VerifyRooms(int *CurrentRoom, int *LastRoom, Player *player);

#endif