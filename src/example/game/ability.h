#pragma once
#include "../global.hpp"
#include "monster_manager.h"
#include "location_manager.h"



class Ability {
public:
    Ability(AbilityID name, const std::string& description)
            : name(name), description(description) {}

    virtual ~Ability() = default;

    AbilityID GetName() const { return name; }
    const std::string& GetDescription() const { return description; }

    // Pure virtual function for activation
    virtual void Activate() = 0;
    virtual void Activate(MonsterManager mManager, LocationManager lManager,Monster monster) = 0;

protected:
    AbilityID name;
    std::string description;
};
