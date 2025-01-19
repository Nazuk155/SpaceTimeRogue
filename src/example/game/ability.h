#pragma once
#include "../global.hpp"



class Ability {
public:
    Ability(AbilityName name, const std::string& description)
            : name(name), description(description) {}

    virtual ~Ability() = default;

    AbilityName GetName() const { return name; }
    const std::string& GetDescription() const { return description; }

    // Pure virtual function for activation
    virtual void Activate() = 0;

protected:
    AbilityName name;
    std::string description;
};
