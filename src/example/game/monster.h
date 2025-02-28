//
// Created by max on 27.01.25.
//

#pragma once
#include "../global.hpp"
class Monster {
public:
    const char* name = "";
    LocationID location = LocationID::UNASSIGNED_LOCATION;
    MonsterID id = MonsterID::UNASSIGNED_MONSTERID; // Add an UNASSIGNED_MONSTERID enum value
    MonsterType type = MonsterType::None;
    MovementType moveType = MovementType::Stalking;
    LocationID moveTarget = LocationID::UNASSIGNED_LOCATION;
    bool alreadyMoved = false;
    int hp = 0;
    int toughness = 0;
    int awareness = 0;
    int horrorRating = 0;
    int horrorDamage = 0;
    int combatRating = 0;
    int combatDamage = 0;
    AbilityID ability = AbilityID::NONE;  // Default to null
    int spawnLimit = 0;

    Monster(const Monster& other) { //explicit copy constructor
        name = other.name;
        location = other.location;
        id = other.id;
        type = other.type;
        moveType = other.moveType;
        moveTarget = other.moveTarget;
        alreadyMoved = other.alreadyMoved;
        hp = other.hp;
        toughness = other.toughness;
        awareness = other.awareness;
        horrorRating = other.horrorRating;
        horrorDamage = other.horrorDamage;
        combatRating = other.combatRating;
        combatDamage = other.combatDamage;
        ability = other.ability;
        spawnLimit = other.spawnLimit;

    }
    // Default Constructor
    Monster() = default;

    // Parameterized Constructor
    Monster(const char* name,
            LocationID location,
            MonsterID id,
            MonsterType type,
            MovementType moveType,
            int hp,
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
              hp(hp),
              toughness(toughness),
              awareness(awareness),
              horrorRating(horrorRating),
              horrorDamage(horrorDamage),
              combatRating(combatRating),
              combatDamage(combatDamage),
              ability(ability),
              spawnLimit(spawnLimit) {}
};
