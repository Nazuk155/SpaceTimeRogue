//
// Created by max on 27.01.25.
//
#pragma once
#include "ability.h"
#include <iostream>


class ability_WolfPackAttack : public Ability {
public:
    ability_WolfPackAttack()
            : Ability(AbilityID::WolfPackAttack, "Strength through numbers!") {}

    void Activate() override {
        std::cout << "Strength through numbers!" << std::endl;

    }
    void Activate(MonsterManager mManager, LocationManager lManager,Monster monster) override{
        mManager.getMonsterByID(MonsterID::Wolf)->combatDamage = static_cast<int>(lManager.GetItem(monster.location)->monsters_or_npcs.size());
    }
};