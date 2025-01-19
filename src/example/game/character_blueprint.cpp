#include "character_blueprint.h" // Include the header for CharacterBlueprint

// Constructor definition
CharacterBlueprint::CharacterBlueprint(const std::string& name, int base_stamina, int base_sanity,
                                       Stats base_stats, Stats base_stats_boundary, int focus, Ability* ability,
                                       const std::string& fate_condition, const std::vector<Item*> items)
        : name(name), base_stamina(base_stamina), base_sanity(base_sanity),
          base_stats(base_stats), base_stats_boundary(base_stats_boundary), focus(focus),
          ability(ability), fate_refill_condition(fate_condition), starting_items(items) {
    // Any additional logic can be added here if needed
}
