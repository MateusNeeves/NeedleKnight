#include "hudmenu.h"
#include "player.h"

void CreateMenuInfo(Menu *menuInfo){

    menuInfo->Texture = LoadTexture("Assets/FramesMenu/1.png");

    menuInfo->CurrentFrame = 1;

    menuInfo->MenuMusic = LoadSound("Assets/Musicas/Menu-ST/MenuMusic.mp3");
}

void CreateHud(Hud *infoHud){
    infoHud->TexturePLife = LoadTexture("Assets/HUD/Life.png");
}

void DrawPlayerLife(Player player, Hud infoHud, float counter){
    static float Timer = 0.0f;


    if (player.Invulnerable)
        Timer += GetFrameTime();
    else
        Timer = 0.0f;
    
    for(int i = 0 ; i < player.CurrentLife ; i++){
        Rectangle pLifeRec = {0, 0 , infoHud.TexturePLife.width/3, infoHud.TexturePLife.height}; 

        Vector2 pLifeRecPosition = {25 + counter, -30};

        DrawTextureRec(infoHud.TexturePLife, pLifeRec, pLifeRecPosition, WHITE);

        counter += infoHud.TexturePLife.width/3;
    }

    for(int i = 0 ; i < player.MaxLife - player.CurrentLife ; i++){

        Rectangle pLostLifeRec = {2 * infoHud.TexturePLife.width/3, 0, infoHud.TexturePLife.width/3, infoHud.TexturePLife.height}; 

        Vector2 pLostLifeRecPosition = {25 + counter, -30};

        DrawTextureRec(infoHud.TexturePLife, pLostLifeRec, pLostLifeRecPosition, WHITE);

        counter += infoHud.TexturePLife.width/3;
    }

    if (player.Invulnerable && Timer < 0.2f){
        Rectangle pAnimLostLifeRec = {infoHud.TexturePLife.width/3, 0, infoHud.TexturePLife.width/3, infoHud.TexturePLife.height}; 

        Vector2 pAnimLostLifeRecPosition = {25 + (player.CurrentLife * infoHud.TexturePLife.width/3), -30};

        DrawTextureRec(infoHud.TexturePLife, pAnimLostLifeRec, pAnimLostLifeRecPosition, WHITE);
    }
    

    counter = 0;
}

void DamageHitEffect(Player player){
    static float InvunTimer = 0.0f;

    if (player.Invulnerable)
        InvunTimer += GetFrameTime();
    if (InvunTimer > 0.4f)
        InvunTimer = 0.0f;

    if (player.Invulnerable && InvunTimer < 0.2f)
        DrawTextureV(player.Textures[12], (Vector2) {0,0}, WHITE); 
}
