#ifndef ROOM
#define ROOM

#include "raylib.h"
#include "player.h"

typedef struct Room {
    Texture2D texture;
    Texture2D FrontTexture;
    Rectangle *platforms;
    int platformNmbr;
} Room;

void CreateRooms(Room **rooms);

void DrawRoom(Room rooms, int Front_Back);

void VerifyRooms(int *CurrentRoom, int *LastRoom, Player *player);


#endif