//
// Created by max on 27.01.25.
//

#pragma once
#include "../global.hpp"
#include "ability.h"
class Monster {
public:
    const char* name = "";
    MonsterID id = MonsterID::UNASSIGNED; // Add an UNASSIGNED enum value
    MonsterType type = MonsterType::None;
    MovementType moveType = MovementType::Stalking;
    int toughness = 0;
    int horrorRating = 0;
    int horrorDamage = 0;
    int combatRating = 0;
    int combatDamage = 0;
    Ability* ability = nullptr;  // Default to null
    int spawnLimit = 0;

    // Default Constructor
    Monster() = default;

    // Parameterized Constructor
    Monster(const char* name,
            MonsterID id,
            MonsterType type,
            MovementType moveType,
            int toughness,
            int horrorRating,
            int horrorDamage,
            int combatRating,
            int combatDamage,
            Ability* ability,
            int spawnLimit)
            : name(name),
              id(id),
              type(type),
              moveType(moveType),
              toughness(toughness),
              horrorRating(horrorRating),
              horrorDamage(horrorDamage),
              combatRating(combatRating),
              combatDamage(combatDamage),
              ability(ability),
              spawnLimit(spawnLimit) {}
};
