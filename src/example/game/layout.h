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

    SDL_Point SidebarContentStart {81,4};
    SDL_Point SidebarContentEnd {98,100};

    SDL_Point ClassTextBox {16,4};

    //leave 1-2 free then skillsheet
    //Stamina, Sanity Skills
    SDL_Point SkillTextStart {82,10};

    SDL_Point SkillTextScale {16,3};

    SDL_Point EquippedItemsStart {81,7*SkillTextScale.y};
    SDL_Point InventoryRowScale{18,7};

    SDL_Point InventoryScale {18,6*InventoryRowScale.y};
    SDL_Point InventoryStart {81,EquippedItemsStart.y+InventoryRowScale.y*2};

    SDL_Point InventoryItemScale{8,8};

    SDL_Point InventoryIconStart{81,InventoryStart.y+2};
    SDL_Point InventoryIconScale {8,8};
    SDL_Point JournalIconStart{EquippedItemsStart.x+InventoryScale.x-InventoryItemScale.x,InventoryIconStart.y};
    SDL_Point JournalIconScale {8,8};

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

struct {
    SDL_Rect QL_Layout {0,0,SidebarLayout.SidebarStart.x,100};
    SDL_Point QL_ContentStart {5,7};
    SDL_Point QL_ContentEnd {SidebarLayout.SidebarStart.x-5,95};
}QuestlogLayout;

 struct EncounterLayout
{

    //CAUTION: The Points represent Percentages of the screen, not actual pixel values!
    SDL_Point Scenestart = {0,0};
    SDL_Point SceneEnd = {80,70};

    int HorizonLine = 65; //todo figure this out, add img scaling

    SDL_Point overlayMainPoint = {0,0}; //used to avoid difficult manual placement of items in BG -> things on trees, flowers etc
    SDL_Point characterMainPoint = {15,HorizonLine};
    SDL_Point characterBottomPoint = {15,70};
    SDL_Point enemyMainPoint = {45,HorizonLine};
    SDL_Point npcBottomPoint = {45,70};

    SDL_Point HealthBarTitleStart {10,62};
     SDL_FPoint HealthbarTitleScale{4,1.4};
    SDL_FPoint HealthbarBorderStart{9.5,66.5};
    SDL_FPoint HealthbarBorderScale{61,2};
    SDL_Point HealthBarStart {10,67};
    SDL_Point HealthBarScale {60,1};

    SDL_Point DialogueBoxStart = {0,70};
    SDL_Point DialogueBoxEnd = {80,100};
    SDL_Point DialogueMainTextStart = {2,72};
    SDL_Point DialogueMainTextEnd = {78,80};

    SDL_Point DialogueOptionFieldScale = {78,4};


    SDL_Point DiceFieldStart {15,0};
    SDL_Point DiceFieldEnd {45,10};



} EncounterLayout;

struct  //TODO PLACEHOLDER for better system, encounter data etc
{
    const SDL_Point LK_IMG = {492, 700};

    const float ScalingvalueLKX = LK_IMG.x/(1920*1.4);
    const float ScalingvalueLKY = LK_IMG.y/(1080*1.4);

    const SDL_Point Garou_IMG = {336,537};
    const float ScalingValueGarouX = Garou_IMG.x*1.5/1920;
    const float ScalingValueGarouY = Garou_IMG.y*1.5/1080;


    const SDL_Point Monk_IMG = {512,1228};
    const float ScalingvalueMKNX = Monk_IMG.x/(1920*2.5);
    const float ScalingvalueMNKY = Monk_IMG.y/(1080*2.5);

    const SDL_Point Abbot_IMG = {652,1220};
    const float ScalingvalueABBTX = Abbot_IMG.x/(1920*2.5);
    const float ScalingvalueABBTY = Abbot_IMG.y/(1080*2.5);

    const SDL_Point Wolf_IMG = {1139,1016};
    const float ScalingvalueWolfX = Wolf_IMG.x/(1920*2.1);
    const float ScalingvalueWolfY = Wolf_IMG.y/(1080*2.1);

    const SDL_Point Bear_IMG {998,1406};
    const float ScalingvalueBearX = Bear_IMG.x/(1920*2.1);
    const float ScalingvalueBearY = Bear_IMG.y/(1080*2.1);

    SDL_Point Anthony_IMG {1032,750};
    const float ScalingvalueAnthonyX = Anthony_IMG.x/(1920*2.5);
    const float ScalingvalueAnthonyY = Anthony_IMG.y/(1080*2.5);

    SDL_Point Hunter_IMG {1033,1250};
    const float ScalingvalueHunterX = Hunter_IMG.x/(1920*2.5);
    const float ScalingvalueHunterY = Hunter_IMG.y/(1080*2.5);

    SDL_Point Peasant1_IMG {795,1250};
    const float ScalingvaluePSNT1X = Peasant1_IMG.x/(1920*2.5);
    const float ScalingvaluePSNT1Y = Peasant1_IMG.y/(1080*2.5);

    SDL_Point PeasantCouple_IMG {795,1250};
    const float ScalingvaluePSNTCoupleX = Peasant1_IMG.x/(1920*2.5);
    const float ScalingvaluePSNTCoupleY = Peasant1_IMG.y/(1080*2.5);

    SDL_Point Peasant2_IMG {463,1250};
    const float ScalingvaluePSNT2X = Peasant2_IMG.x/(1920*2.5);
    const float ScalingvaluePSNT2Y = Peasant2_IMG.y/(1080*2.5);


    SDL_Point woman1_IMG {570,1250};
    const float ScalingvalueWoman1X = woman1_IMG.x/(1920*2.5);
    const float ScalingvalueWoman1Y = woman1_IMG.y/(1080*2.5);

    SDL_Point skeleton_spear_IMG {1636,1250};
    const float ScalingvalueSkeletonSpearX = skeleton_spear_IMG.x/(1920*2.7);
    const float ScalingvalueSkeletonSpearY = skeleton_spear_IMG.y/(1080*2.7);

    SDL_Point mercenary_IMG {660,1799};
    const float ScalingvalueMercX = mercenary_IMG.x/(1920*2.7);
    const float ScalingvalueMercY = mercenary_IMG.y/(1080*2.7);
    SDL_Point veteran_IMG {462,1250};
    const float ScalingvalueVeteranX = veteran_IMG.x/(1920*2.7);
    const float ScalingvalueVeteranY = veteran_IMG.y/(1080*2.7);


    const SDL_Point Turn_Button = {409, 1040};

    const SDL_Rect BagIconScale {0,0,512,512};

}SpriteData;

//std::map<SceneCompositionEntities,std::tuple<SDL_Texture,SDL_Point>>
//This point is the scale, target defines location?
/*{
    Composition
{Sprite, target}
}*/



