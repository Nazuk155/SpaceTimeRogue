#pragma once
#include "../global.hpp"



struct AnimationTarget {

    u64 currentSprite = 0;
    u64 frame = 0;
    u64 animationFrame = 0;

    SDL_Rect target;
    SDL_Point gridPos;
    int id;
    CharacterIDs type;
    CharacterAnimations currentAnimation;
    CharacterAnimations nextAnimation;
    bool loop = true;

    SDL_Rect getTarget(){return target;}
    void updatePosition(SDL_Rect newPos){ target = newPos;}

    AnimationTarget(SDL_Rect t, SDL_Point gridPos, int id, CharacterIDs type, CharacterAnimations current, CharacterAnimations next)
    :target(t),gridPos(gridPos), id(id),type(type),currentAnimation(current),nextAnimation(next){}

};

class AnimationManager {

public:
    AnimationManager(Vector<AnimationTarget> targets);

    Vector<AnimationTarget> targets;

    void addTarget(AnimationTarget target);


};


