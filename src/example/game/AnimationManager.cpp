//
// Created by max on 14.03.25.
//

#include "AnimationManager.h"


AnimationManager::AnimationManager(Vector<AnimationTarget> targets){
    targets = targets;
}

void AnimationManager::addTarget(AnimationTarget target) {
    targets.push_back(target);

}
