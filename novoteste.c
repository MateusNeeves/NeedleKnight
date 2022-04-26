#include "raylib.h"
#include "raymath.h"

#define G 800
#define PlayerJumpSpeed 400.0f
#define PlayerHorzSpeed 200.0f
#define Right 1
#define Left 0

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;


void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta, int *detector, Texture2D **Texture, Texture2D jogadorRunLeft, 
                  Texture2D jogadorRunRight, Texture2D jogadorStandLeft, Texture2D jogadorStandRight, float *FrameWidth, int *MaxFrames, short *LastSide)
{
    if (IsKeyDown(KEY_A)){
        player->position.x -= PlayerHorzSpeed * delta;
        *(*Texture) = jogadorRunLeft;
        *FrameWidth = jogadorRunLeft.width / 8.0;
        *MaxFrames = (int) (jogadorRunLeft.width / (int) * FrameWidth);
        *detector = 1;
        *LastSide = Left;
    }
    else if (IsKeyDown(KEY_D)){
        player->position.x += PlayerHorzSpeed * delta;
        *(*Texture) = jogadorRunRight;
        *FrameWidth = jogadorRunRight.width / 8.0;
        *MaxFrames = (int) (jogadorRunRight.width / (int) * FrameWidth);
        *detector = 1;
        *LastSide = Right;
    }
    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->speed = -PlayerJumpSpeed;
        player->canJump = false;
    }
    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && player->canJump == true){
        if (*LastSide == Left){
            *(*Texture) = jogadorStandLeft;
            *FrameWidth = jogadorStandLeft.width / 6.0;
            *MaxFrames = (int) (jogadorStandLeft.width / (int) * FrameWidth);
            *detector = 1;
        }
        else{
            *(*Texture) = jogadorStandRight;
            *FrameWidth = jogadorStandRight.width / 6.0;
            *MaxFrames = (int) (jogadorStandRight.width / (int) * FrameWidth);
            *detector = 1;
        }
    }

    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed*delta)
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    Player player = { 0 };
    player.position = (Vector2){ 400, 400 };
    player.speed = 0;
    player.canJump = false;
    EnvItem envItems[] = {
        {{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);


    Texture2D jogadorRunLeft = LoadTexture("D:\\Aprendendo\\assets\\Personagem\\RunLeft.png");

    Texture2D jogadorRunRight = LoadTexture("D:\\Aprendendo\\assets\\Personagem\\RunRight.png");

    Texture2D jogadorStandLeft = LoadTexture("D:\\Aprendendo\\assets\\Personagem\\StandLeft.png");

    Texture2D jogadorStandRight = LoadTexture("D:\\Aprendendo\\assets\\Personagem\\StandRight.png");


    Texture2D *WhichTexture;
    *WhichTexture = jogadorStandLeft;

    Texture2D *LastMove;
    float FrameWidth;
    int MaxFrames;

    int CurrentFrame = 0;
    float Timer = 0.0f;
    short LastSide = Left;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){

        float deltaTime = GetFrameTime();

        int detector = 0;

        LastMove = WhichTexture;

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime, &detector, &WhichTexture, jogadorRunLeft, jogadorRunRight, 
                    jogadorStandLeft, jogadorStandRight, &FrameWidth, &MaxFrames, &LastSide);

        if (LastMove != WhichTexture)
            CurrentFrame = 0;

        if (detector == 1){
        Timer += GetFrameTime();

        if (Timer >= 0.1f){
            Timer = 0.0f;
            CurrentFrame += 1;
        }

        CurrentFrame = CurrentFrame % MaxFrames;

        }

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

                for (int i = 0; i < envItemsLength; i++)
                    DrawRectangleRec(envItems[i].rect, envItems[i].color);

                Rectangle playerRect = {FrameWidth * CurrentFrame , 0, FrameWidth , WhichTexture->height };
                
                Vector2 positionRec = {player.position.x - (FrameWidth/2), player.position.y - WhichTexture->height};

                DrawTextureRec(*WhichTexture, playerRect, positionRec, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    UnloadTexture(jogadorRunLeft);
    UnloadTexture(jogadorRunRight);
    UnloadTexture(jogadorStandLeft);
    UnloadTexture(jogadorStandRight);

    CloseWindow();
}