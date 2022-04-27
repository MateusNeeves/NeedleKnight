#ifndef COLISION
#define COLISION

#include "raylib.h"

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

void DetectarColisao();

#endif