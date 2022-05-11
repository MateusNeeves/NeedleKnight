#include "hudmenu.h"
#include "player.h"

void CreateMenuInfo(Menu *menuInfo){

    menuInfo->Texture = LoadTexture("Assets/FramesMenu/1.png");

    menuInfo->CurrentFrame = 1;
}

void CreateHud(Hud *infoHud){
    infoHud->TexturePLife = LoadTexture("Assets/HUD/Life.png");
}

void DrawPlayerLife(Player player, Hud infoHud, float counter){
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

    counter = 0;
}


