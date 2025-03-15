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
    PlayerState state;

    explicit playerCharacter(SDL_Point gridPos = {0,0}, SDL_Rect r = {0,0,32,32},int hp = 3, int mp = 3, int fp = 3,PlayerState state = PlayerState::Idle);
    void updatePosition(SDL_Point p,SDL_Rect r);
    void updatePosition(SDL_Rect r);
    void offsetSprite(){
        rect.y = rect.y - rect.h/4;
    }

    void scaleSize(int scale);
};

