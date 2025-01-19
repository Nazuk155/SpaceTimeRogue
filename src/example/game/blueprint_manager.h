#pragma once
#include "../global.hpp"
#include "character_blueprint.h" // Include the header where CharacterBlueprint is defined

class BlueprintManager {
private:
    std::vector<std::shared_ptr<CharacterBlueprint>> blueprints;

public:
    void AddBlueprint(const std::shared_ptr<CharacterBlueprint>& blueprint);
    [[nodiscard]] const std::vector<std::shared_ptr<CharacterBlueprint>>& GetBlueprints() const;
    [[nodiscard]] std::shared_ptr<CharacterBlueprint> GetBlueprintByName(const std::string& name) const;
};
