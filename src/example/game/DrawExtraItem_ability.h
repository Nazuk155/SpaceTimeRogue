#ifndef DRAW_EXTRA_ITEM_ABILITY_H
#define DRAW_EXTRA_ITEM_ABILITY_H

#include "ability.h"
#include <iostream>

class DrawExtraItemAbility : public Ability {
public:
    DrawExtraItemAbility()
            : Ability(AbilityName::DrawExtraItem, "Draw an extra item and choose one.") {}

    void Activate() override {
        std::cout << "You draw an extra item and choose one to keep!" << std::endl;
        // Implement effect logic
    }
};

#endif // DRAW_EXTRA_ITEM_ABILITY_H
