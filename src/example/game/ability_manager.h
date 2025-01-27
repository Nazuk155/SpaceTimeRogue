#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include "ability.h"
#include <vector>
#include <memory>

class AbilityManager {
public:
    void AddAbility(std::unique_ptr<Ability> ability) {
        abilities.push_back(std::move(ability));
    }

    Ability* GetAbility(AbilityID name) {
        for (const auto& ability : abilities) {
            if (ability->GetName() == name) {
                return ability.get();
            }
        }
        return nullptr; // Return nullptr if not found
    }

private:
    std::vector<std::unique_ptr<Ability>> abilities;
};

#endif // ABILITY_MANAGER_H
