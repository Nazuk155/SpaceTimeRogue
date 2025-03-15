//
// Created by max on 15.03.25.
//

#include "playerCharacter.h"



playerCharacter::playerCharacter(SDL_Point gridPos , SDL_Rect r , int hp , int mp , int fp ,PlayerState state):
gridPosition(gridPos),rect(r),HP(hp),MovementPoints(mp),FocusPoints(fp),state(state)
{
    //offset the sprite by 25% up
    rect.y = rect.y - rect.h/4;
}

void playerCharacter::updatePosition( SDL_Rect r) {
    updatePosition(gridPosition,r);
}
void playerCharacter::scaleSize(int scale){
    rect.x  = rect.x*scale;
    rect.x  = rect.x*scale;
    rect.w  = scale;
    rect.h  = scale;

}
void playerCharacter::updatePosition(SDL_Point newP, SDL_Rect newR) {
        gridPosition = newP;
        rect = newR;
        offsetSprite();

}
