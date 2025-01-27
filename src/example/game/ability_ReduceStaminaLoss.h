#pragma once
#include "ability.h"
#include <iostream>

class ReduceStaminaLossAbility : public Ability {
public:
    ReduceStaminaLossAbility()
            : Ability(AbilityID::ReduceStaminaLoss, "Reduces stamina loss by 1.") {}

    void Activate() override {
        std::cout << "Stamina loss reduced by 1!" << std::endl;
        // Implement effect logic
    }
    void Activate(MonsterManager mManager, LocationManager lManager,Monster monster) override{}
    };