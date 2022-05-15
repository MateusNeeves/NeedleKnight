#ifndef ROOM
#define ROOM

#include "raylib.h"
#include "player.h"

typedef struct Door{
    Vector2 position;
    Texture2D Texture;
} Door;

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

    Sound SoundEffects[6];
} Enemies;

typedef struct Room {
    Texture2D texture;
    Texture2D FrontTexture;
    Rectangle *platforms;
    int platformNmbr;
    Sound SoundTrack;
    Enemies enemy[2];
    int enemyNmbr;
    Door doors[2];
    int doorsNmbr;
} Room;

void CreateRooms(Room **rooms);

void DrawRoom(Room rooms, int Front_Back, Player player);

void VerifyRooms(int *CurrentEnemy, int *CurrentRoom, int *LastRoom, Player *player, Room *rooms);

void VerifyDoors(Player player, Room *rooms);

#endif