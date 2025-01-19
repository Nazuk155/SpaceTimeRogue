#pragma once

#include <string>
#include <vector>
#include <utility>
#include "../global.hpp"
#include "item.h"
#include "location.h"
#include "character_blueprint.h"
#include "ability.h"

class Character {
public:



private:
    std::string name;                 // Character's name
    int stamina, sanity;              // Current stamina and sanity
    int base_stamina, base_sanity;    // Max stamina and sanity

    int player_id;                    // Assigned player (for multiplayer, -1 if single-player)
    Stats base_stats;                 // Base stats
    Stats base_stats_boundary;
    Stats current_stats;              // Current stats (modified by items/events)
    int focus;                        // Number of focus points available

    Ability* ability;
    // Ability active_ability; TODO implement Ability class and acivateAbility() as well as adding it to blueprint
    int fate_points;                  // Fate/Hero points
    std::string fate_refill_condition; // Condition to refill fate points
    // RefillCondition refill // TODO implement Refill_Condition class add it to blueprint
    // bool refillFate // toggle to set if condition is fulfilled and refill occurs on upkeep phase

    int non_item_resources;           // Non-item resource counter (e.g., money, energy)
    std::vector<Item*> inventory;      // Inventory of items
    std::pair<Item*, Item*> equipped_items; // Equipped items (left and right hand)
    std::vector<QuestID> quest_log;     // Quest log
    int current_location_id;          // ID of the current location

public:
    Character(const std::string& name, int base_stamina, int base_sanity, Stats base_stats, Stats base_stats_boundary,
              Ability* ability, int focus, const std::string& fate_condition);

    Character(const CharacterBlueprint& blueprint);

    // Getters
    const std::string& GetName() const;
    int GetStamina() const;
    int GetSanity() const;
    const Stats& GetBaseStats() const;
    const Stats& GetCurrentStats() const;
    int GetFocus() const;
    int GetFatePoints() const;
    int GetCurrentLocationID() const;
    const std::vector<Item *> & GetInventory() const;

    // Setters
    void SetCurrentLocation(int location_id);
    void AdjustStamina(int amount);
    void AdjustSanity(int amount);
    bool AdjustStat(StatNames stat, int amount);
    void AddToInventory(Item *item);
    void RemoveFromInventory(ItemName name);
    void EquipItem(Item* item, bool is_left_hand);

    // Gameplay Methods
    void UseFocus(StatNames statToIncrease, StatNames statToDecrease);
    void RefillFatePoints();
    void AddQuest(const QuestID quest);
    void CompleteQuest(QuestID quest_id);
};
