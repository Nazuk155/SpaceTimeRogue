//
// Created by Prince of Brass on 24/01/2025.
//

//#include <map>
#include "../global.hpp"
//#include "encounter.h"

struct
{
    //Size and scale mean the same thing - % of total screen x/y

    SDL_Point SidebarStart {80,0};
    SDL_Point SidebarEnd {100,100};
    SDL_Point SidebarSize {20,100};

    SDL_Point SidebarContentStart {82,4};
    SDL_Point SidebarContentEnd {98,100};

    SDL_Point ClassTextBox {16,4};

    //leave 1-2 free then skillsheet
    //Stamina, Sanity Skills
    SDL_Point SkillTextStart {82,10};

    SDL_Point SkillTextScale {16,3};

    SDL_Point EquippedItemsStart {82,7*SkillTextScale.y};
    SDL_Point InventoryRowScale{16,7};
    SDL_Point InventoryItemScale{8,7}; //Todo nonsense percentages do not work for square icons x!=y! -> make it so ignore x
    SDL_Point InventoryScale {16,6*InventoryRowScale.y};
    SDL_Point InventoryStart {82,EquippedItemsStart.y+InventoryRowScale.y*2};

    int EndTurnbuttonHeight = 15;

    SDL_Point EndTurnButtonStart{90,80};
    //SDL_Point EndTurnButtonSize{};

    /* 6 Skills
    speed;
    sneak;
    fight;
    willpower;
    knowledge;
    luck;
     */
}SidebarLayout;

 struct EncounterLayout
{

    //CAUTION: The Points represent Percentages of the screen, not actual pixel values!
    SDL_Point Scenestart = {0,0};
    SDL_Point SceneEnd = {80,70};

    int HorizonLine = 65; //todo figure this out, add img scaling

    SDL_Point characterMainPoint = {15,HorizonLine};
    SDL_Point enemyMainPoint = {45,HorizonLine};


    SDL_Point DialogueBoxStart = {0,70};
    SDL_Point DialogueBoxEnd = {80,100};
    SDL_Point DialogueMainTextStart = {2,72};
    SDL_Point DialogueMainTextEnd = {78,80};

    SDL_Point DialogueOptionFieldScale = {78,4};



} EncounterLayout;

struct  //TODO PLACEHOLDER for better system, encounter data etc
{
    const SDL_Point LK_IMG = {492, 700};

    const float ScalingvalueLKX = LK_IMG.x/(1920*1.4);
    const float ScalingvalueLKY = LK_IMG.y/(1080*1.4);

    const SDL_Point Garou_IMG = {336,537};
    const float ScalingValueGarouX = Garou_IMG.x*1.2/1920;
    const float ScalingValueGarouY = Garou_IMG.y*1.2/1080;


    const SDL_Point Turn_Button = {409, 1040};
}SpriteData;

//std::map<SceneCompositionEntities,std::tuple<SDL_Texture,SDL_Point>>
//This point is the scale, target defines location?
/*{
    Composition
{Sprite, target}
}*/



