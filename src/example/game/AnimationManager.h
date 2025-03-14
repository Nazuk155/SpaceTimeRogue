#pragma once
#include "../global.hpp"



struct AnimationTarget {

    u64 currentSprite = 0;
    u64 frame = 0;
    u64 animationFrame = 0;

    SDL_Rect target;
    int id;
    EntityType type;
    EntityAnimations currentAnimation;
    EntityAnimations nextAnimation;
    bool loop = true;

    SDL_Rect getTarget(){return target;}

    AnimationTarget(SDL_Rect t,int id,EntityType type,EntityAnimations current, EntityAnimations next)
    :target(t), id(id),type(type),currentAnimation(current),nextAnimation(next){}

};

class AnimationManager {

public:
    AnimationManager(Vector<AnimationTarget> targets);

    Vector<AnimationTarget> targets;

    void addTarget(AnimationTarget target);


};


