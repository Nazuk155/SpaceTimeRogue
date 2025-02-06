#ifndef DRAW_EXTRA_ITEM_ABILITY_H
#define DRAW_EXTRA_ITEM_ABILITY_H

#include "ability.h"
#include <iostream>

class DrawExtraItemAbility : public Ability {
public:
    DrawExtraItemAbility()
            : Ability(AbilityID::DrawExtraItem, "Draw an extra item and choose one.") {}

    void Activate() override {
        std::cout << "You draw an extra item and choose one to keep!" << std::endl;
        // Implement effect logic
    }
    void Activate(MonsterManager mManager, LocationManager lManager,Monster monster) override{
        std::cout << "You draw an extra item and choose one to keep!" << std::endl;

    }
};

#endif // DRAW_EXTRA_ITEM_ABILITY_H
