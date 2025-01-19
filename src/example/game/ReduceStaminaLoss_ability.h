#ifndef REDUCE_STAMINA_LOSS_ABILITY_H
#define REDUCE_STAMINA_LOSS_ABILITY_H

#include "ability.h"
#include <iostream>

class ReduceStaminaLossAbility : public Ability {
public:
    ReduceStaminaLossAbility()
            : Ability(AbilityName::ReduceStaminaLoss, "Reduces stamina loss by 1.") {}

    void Activate() override {
        std::cout << "Stamina loss reduced by 1!" << std::endl;
        // Implement effect logic
    }
};

#endif // REDUCE_STAMINA_LOSS_ABILITY_H
