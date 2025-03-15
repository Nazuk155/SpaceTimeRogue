//
// Created by max on 15.03.25.
//
#pragma once
#include "../global.hpp"

class playerCharacter {


public:
    SDL_Point gridPosition;
    SDL_Rect rect;
    int HP;
    int MovementPoints;
    int FocusPoints;

    playerCharacter(SDL_Point gridPos, SDL_Rect r,int hp, int mp, int fp);
    void updatePosition(SDL_Point p,SDL_Rect r);
    void offsetSprite(){
        rect.y = rect.y - rect.h/4;
    }
};

