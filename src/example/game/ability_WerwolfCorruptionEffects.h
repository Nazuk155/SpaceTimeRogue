//
// Created by max on 27.01.25.
//

#pragma once

#include "ability.h"
#include <iostream>

class ability_WerwolfCorruptionEffects : public Ability {
public:
    ability_WerwolfCorruptionEffects()
            : Ability(AbilityID::ReduceStaminaLoss, "Corruption Strengthens the Werwolf!") {}

    void Activate() override {
        std::cout << "Corruption strengthens the Werwolf!" << std::endl;
        // Implement effect logic
    }
};
