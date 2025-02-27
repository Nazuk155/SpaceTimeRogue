//
// Created by max on 27.01.25.
//

#pragma once
#include "../global.hpp"
class Monster {
public:
    const char* name = "";
    LocationID location = LocationID::UNASSIGNED;
    MonsterID id = MonsterID::UNASSIGNED; // Add an UNASSIGNED enum value
    MonsterType type = MonsterType::None;
    MovementType moveType = MovementType::Stalking;
    int toughness = 0;
    int awareness = 0;
    int horrorRating = 0;
    int horrorDamage = 0;
    int combatRating = 0;
    int combatDamage = 0;
    AbilityID ability = AbilityID::NONE;  // Default to null
    int spawnLimit = 0;

    // Default Constructor
    Monster() = default;

    // Parameterized Constructor
    Monster(const char* name,
            LocationID location,
            MonsterID id,
            MonsterType type,
            MovementType moveType,
            int toughness,
            int awareness,
            int horrorRating,
            int horrorDamage,
            int combatRating,
            int combatDamage,
            AbilityID ability,
            int spawnLimit)
            : name(name),
            location(location),
              id(id),
              type(type),
              moveType(moveType),
              toughness(toughness),
              awareness(awareness),
              horrorRating(horrorRating),
              horrorDamage(horrorDamage),
              combatRating(combatRating),
              combatDamage(combatDamage),
              ability(ability),
              spawnLimit(spawnLimit) {}
};
