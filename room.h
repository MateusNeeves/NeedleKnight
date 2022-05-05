#ifndef ROOM
#define ROOM

#include "raylib.h"

typedef struct Room {
    Texture2D textureRoom;
    Texture2D FrontTextureRoom;
    Rectangle *platforms;
    int platformNmbr;
} Room;

void CreateRooms(Room **rooms);


#endif