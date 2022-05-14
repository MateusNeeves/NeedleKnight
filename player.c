#include "raylib.h"
#include "player.h"
#include <stdlib.h>

#define PlayerJumpSpeed 1050.0f //1050
#define PlayerHorzSpeed 400.0f
#define Right 1
#define Left 0

#define RunLeft 0
#define RunRight 1
#define StandLeft 2
#define StandRight 3
#define JumpLeft 4
#define JumpRight 5
#define AttackLeft 6
#define AttackRight 7
#define DeathLeft 8
#define DeathRight 9
#define DJumpLeftEffect 10
#define DJumpRightEffect 11
#define DamageEffect 12

void CreatePlayer(Player *player){
    player->position = (Vector2){1540, 545};
    player->speed = 0; 
    player->canJump[0] = true;
    player->canJump[1] = true;
    player->DoubleJump = true;
    player->attacking = false;
    player->Invulnerable = false;

    player->FrameWidth = 0;
    player->CurrentFrame = 0;
    player->MaxFrames = 0;
    player->LastSide = Left;

    player->Textures = (Texture2D*) calloc (13, sizeof(Texture2D));

    player->Textures[RunLeft] = LoadTexture("Assets/Personagem/RunLeft.png");
    player->Textures[RunRight] = LoadTexture("Assets/Personagem/RunRight.png");
    player->Textures[StandLeft] = LoadTexture("Assets/Personagem/StandLeft.png");
    player->Textures[StandRight] = LoadTexture("Assets/Personagem/StandRight.png"); 
    player->Textures[JumpLeft] = LoadTexture("Assets/Personagem/JumpLeft.png");
    player->Textures[JumpRight] = LoadTexture("Assets/Personagem/JumpRight.png");
    player->Textures[AttackLeft] = LoadTexture("Assets/Personagem/AttackLeft.png");
    player->Textures[AttackRight] = LoadTexture("Assets/Personagem/AttackRight.png");
    player->Textures[DeathLeft] = LoadTexture("Assets/Personagem/DeathLeft.png");
    player->Textures[DeathRight] = LoadTexture("Assets/Personagem/DeathRight.png");
    player->Textures[DJumpLeftEffect] = LoadTexture("Assets/Personagem/DJumpLeftEffect.png");
    player->Textures[DJumpRightEffect] = LoadTexture("Assets/Personagem/DJumpRightEffect.png");
    player->Textures[DamageEffect] = LoadTexture("Assets/Personagem/DamageEffect.png");

    //Ao adicionar, alterar qtd na main.c e na player.h

    player->CurrentTexture = player->Textures[2];
    player->MaxLife = 10;
    player->CurrentLife = 10;

    player->SoundEffects = (Sound *) calloc (4, sizeof(Sound));

    player->SoundEffects[0] = LoadSound("Assets/Personagem/EfeitosSonoros/PlayerAttack.wav");
    player->SoundEffects[1] = LoadSound("Assets/Personagem/EfeitosSonoros/PlayerJump.wav");
    player->SoundEffects[2] = LoadSound("Assets/Personagem/EfeitosSonoros/PlayerDeath.wav");
    player->SoundEffects[3] = LoadSound("Assets/Personagem/EfeitosSonoros/PlayerWalk.wav");

}


void MovePlayer(Player **player, float delta)
{
    //Animacao Pulando

    if (IsKeyPressed(KEY_SPACE) && (*player)->canJump[0] && !(*player)->attacking){
        (*player)->speed = -PlayerJumpSpeed;
        (*player)->canJump[0] = false;
        (*player)->CurrentFrame = 0;
        PlaySound((*player)->SoundEffects[1]);

    }
    else if (IsKeyPressed(KEY_SPACE) && (*player)->DoubleJump && !(*player)->canJump[0] && (*player)->canJump[1] && !(*player)->attacking){
        (*player)->speed = -(PlayerJumpSpeed/1.15);
        (*player)->canJump[1] = false;
        (*player)->CurrentFrame = 0;
        PlaySound((*player)->SoundEffects[1]);
    }

    
    //Animacao Andando pra Esquerda e Pulando pra Esquerda

    if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && !(*player)->attacking){
        (*player)->position.x -= PlayerHorzSpeed * delta;
        (*player)->LastSide = Left;
        PlaySound((*player)->SoundEffects[3]);

        if ((*player)->canJump[0]){
            (*player)->CurrentTexture = (*player)->Textures[RunLeft];
            (*player)->FrameWidth = (*player)->Textures[RunLeft].width / 8.0;
            (*player)->MaxFrames = (int) ((*player)->Textures[RunLeft].width / (int) (*player)->FrameWidth);
        }

        else{
            (*player)->CurrentTexture = (*player)->Textures[JumpLeft];
            (*player)->FrameWidth = (*player)->Textures[JumpLeft].width / 9.0;
            (*player)->MaxFrames = (int) ((*player)->Textures[JumpLeft].width / (int) (*player)->FrameWidth);
        }
    }

    //Animacao Andando pra Direita e Pulando pra Direita

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && !(*player)->attacking){
        (*player)->position.x += PlayerHorzSpeed * delta;
        (*player)->LastSide = Right;
        PlaySound((*player)->SoundEffects[3]);

        if ((*player)->canJump[0]){
            (*player)->CurrentTexture = (*player)->Textures[RunRight];
            (*player)->FrameWidth = (*player)->Textures[RunRight].width / 8.0;
            (*player)->MaxFrames = (int) ((*player)->Textures[RunRight].width / (int) (*player)->FrameWidth);
        }

        else{
            (*player)->CurrentTexture = (*player)->Textures[JumpRight];
            (*player)->FrameWidth = (*player)->Textures[JumpRight].width / 9.0;
            (*player)->MaxFrames = (int) ((*player)->Textures[JumpRight].width / (int) (*player)->FrameWidth);
        }
    }

    //Animacao Parado e Pulando Parado

    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_D) && IsKeyUp(KEY_RIGHT) && !(*player)->attacking)
    {
        PauseSound((*player)->SoundEffects[3]);

        if ((*player)->canJump[0]){
            if ((*player)->LastSide == Left){
                (*player)->CurrentTexture = (*player)->Textures[StandLeft];
                (*player)->FrameWidth = (*player)->Textures[StandLeft].width / 6.0;
                (*player)->MaxFrames = (int) ((*player)->Textures[StandLeft].width / (int) (*player)->FrameWidth);
            }
            else{
                (*player)->CurrentTexture = (*player)->Textures[StandRight];
                (*player)->FrameWidth = (*player)->Textures[StandRight].width / 6.0;
                (*player)->MaxFrames = (int) ((*player)->Textures[StandRight].width / (int) (*player)->FrameWidth);
            } 
        }

        else{
            if ((*player)->LastSide == Left){
                (*player)->CurrentTexture = (*player)->Textures[JumpLeft];
                (*player)->FrameWidth = (*player)->Textures[JumpLeft].width / 9.0;
                (*player)->MaxFrames = (int) ((*player)->Textures[JumpLeft].width / (int) (*player)->FrameWidth);
            }

            else{
                (*player)->CurrentTexture = (*player)->Textures[JumpRight];
                (*player)->FrameWidth = (*player)->Textures[JumpRight].width / 9.0;
                (*player)->MaxFrames = (int) ((*player)->Textures[JumpRight].width / (int) (*player)->FrameWidth);
            }
        }
    }

    // Animacao de Ataque

    if (IsKeyPressed(KEY_Z) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT) && 
        !(*player)->attacking && (*player)->canJump[0])
    {
        PlaySound((*player)->SoundEffects[0]);
        (*player)->CurrentFrame = 0;
        (*player)->attacking = true;
        if ((*player)->LastSide == Left){
            (*player)->CurrentTexture = (*player)->Textures[AttackLeft];
            (*player)->FrameWidth = (*player)->Textures[AttackLeft].width / 3.0;
            (*player)->MaxFrames = (int) ((*player)->Textures[AttackLeft].width / (int) (*player)->FrameWidth);
        }
        else{
            (*player)->CurrentTexture = (*player)->Textures[AttackRight];
            (*player)->FrameWidth = (*player)->Textures[AttackRight].width / 3.0;
            (*player)->MaxFrames = (int) ((*player)->Textures[AttackRight].width / (int) (*player)->FrameWidth);
        }
    }
}