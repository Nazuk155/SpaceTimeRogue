#include "blueprint_manager.h"


void BlueprintManager::AddBlueprint(const std::shared_ptr<CharacterBlueprint>& blueprint) {
    blueprints.push_back(blueprint);
}

const std::vector<std::shared_ptr<CharacterBlueprint>>& BlueprintManager::GetBlueprints() const {
    return blueprints;
}

std::shared_ptr<CharacterBlueprint> BlueprintManager::GetBlueprintByName(const std::string& name) const {
    auto it = std::find_if(blueprints.begin(), blueprints.end(),
                           [&name](const std::shared_ptr<CharacterBlueprint>& blueprint) {
                               return blueprint->name == name;
                           });
    return (it != blueprints.end()) ? *it : nullptr;
}
