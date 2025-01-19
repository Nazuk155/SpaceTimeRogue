#include "character.h"
#include <iostream>
#include <utility>

// Constructor
Character::Character(const std::string& name, int base_stamina, int base_sanity, Stats base_stats,Stats base_stats_boundary,
                     Ability* ability, int focus, const std::string& fate_condition)
        : name(name), base_stamina(base_stamina), base_sanity(base_sanity),
          stamina(base_stamina), sanity(base_sanity), base_stats(base_stats),base_stats_boundary(std::move(base_stats_boundary)),
          current_stats(base_stats), focus(focus), ability(ability),
          fate_points(0), fate_refill_condition(fate_condition),
          non_item_resources(0), current_location_id(-1), equipped_items({nullptr, nullptr}) {}

Character::Character(const CharacterBlueprint& blueprint)
        : name(blueprint.name), base_stamina(blueprint.base_stamina), base_sanity(blueprint.base_sanity),
          stamina(blueprint.base_stamina), sanity(blueprint.base_sanity), base_stats(blueprint.base_stats),base_stats_boundary(blueprint.base_stats_boundary),
          current_stats(blueprint.base_stats), focus(blueprint.focus), ability(blueprint.ability),
          fate_points(0), fate_refill_condition(blueprint.fate_refill_condition),
          inventory(blueprint.starting_items), player_id(-1), current_location_id(-1) {}


// Getters
const std::string& Character::GetName() const { return name; }
int Character::GetStamina() const { return stamina; }
int Character::GetSanity() const { return sanity; }
const Stats& Character::GetBaseStats() const { return base_stats; }
const Stats& Character::GetCurrentStats() const { return current_stats; }
int Character::GetFocus() const { return focus; }
int Character::GetFatePoints() const { return fate_points; }
int Character::GetCurrentLocationID() const { return current_location_id; }
const std::vector<Item *> & Character::GetInventory() const { return inventory; }

// Setters
void Character::SetCurrentLocation(int location_id) { current_location_id = location_id; }
void Character::AdjustStamina(int amount) { stamina = std::max(0, std::min(base_stamina, stamina + amount)); }
void Character::AdjustSanity(int amount) { sanity = std::max(0, std::min(base_sanity, sanity + amount)); }
//checks if adjustment is in bounds, then uses structs own method to set the new value and returns success/fail to caller
bool Character::AdjustStat(StatNames stat, int amount) {
    int current_value = base_stats.GetStat(stat);
    int max_value = base_stats_boundary.GetStat(stat);

    if (current_value + amount <= max_value) {
        base_stats.AdjustStat(stat, amount);
        return true;
    } else {
        return false;
    }
}

void Character::AddToInventory(const Item& item) { inventory.push_back(item); }
void Character::RemoveFromInventory(ItemName item_id) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
                                   [item_id](const Item& i) { return i.GetItemName() == item_id; }), inventory.end());
}

void Character::EquipItem(Item* item, bool is_left_hand) {
    if (is_left_hand) equipped_items.first = item;
    else equipped_items.second = item;
}

// Gameplay Methods
// increases one stat of a pair and decreases the other, if stat boundary would be breached it sends a error
void Character::UseFocus(StatNames statToIncrease, StatNames statToDecrease) {
    if (focus > 0) {
        if(!AdjustStat(statToIncrease, 1)) {
            std::cerr << "Stat already at maximum!\n";
        }else {
            AdjustStat(statToDecrease, -1);
            focus--;
        }
    } else {
        std::cerr << "Not enough focus points!\n";
    }
}

void Character::RefillFatePoints() {
    // Logic to refill fate points based on the fate condition
    fate_points = std::max(fate_points, 3); // Example logic
}

void Character::AddQuest(const Quest& quest) { quest_log.push_back(quest); }
void Character::CompleteQuest(int quest_id) {
    quest_log.erase(std::remove_if(quest_log.begin(), quest_log.end(),
                                   [quest_id](const Quest& q) { return q.GetID() == quest_id; }), quest_log.end());
}
