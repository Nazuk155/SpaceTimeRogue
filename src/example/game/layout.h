//
// Created by Prince of Brass on 24/01/2025.
//

//#include <map>
#include "../global.hpp"
//#include "encounter.h"

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

}SpriteData;

//std::map<SceneCompositionEntities,std::tuple<SDL_Texture,SDL_Point>>
//This point is the scale, target defines location?
/*{
    Composition
{Sprite, target}
}*/



