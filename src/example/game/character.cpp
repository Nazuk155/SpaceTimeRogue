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
          non_item_resources(0), current_location_id(LocationID::UNASSIGNED), equipped_items({nullptr, nullptr}) {}

Character::Character(const CharacterBlueprint& blueprint)
        : name(blueprint.name), base_stamina(blueprint.base_stamina), base_sanity(blueprint.base_sanity),
          stamina(blueprint.base_stamina), sanity(blueprint.base_sanity), base_stats(blueprint.base_stats),base_stats_boundary(blueprint.base_stats_boundary),
          current_stats(blueprint.base_stats), focus(blueprint.focus), ability(blueprint.ability),
          fate_points(0), fate_refill_condition(blueprint.fate_refill_condition),
          inventory(blueprint.starting_items), player_id(-1), current_location_id(LocationID::UNASSIGNED) {}


// Getters
const std::string& Character::GetName() const { return name; }
int Character::GetStamina() const { return stamina; }
int Character::GetSanity() const { return sanity; }
const Stats& Character::GetBaseStats() const { return base_stats; }
const Stats& Character::GetCurrentStats() const { return current_stats; }
int Character::GetFocus() const { return focus; }
int Character::GetFatePoints() const { return fate_points; }
LocationID Character::GetCurrentLocationID() const { return current_location_id; }
const std::vector<Item *> & Character::GetInventory() const { return inventory; }
SDL_Rect Character::GetRect(){return rect;}

// Setters
void Character::SetCurrentLocation(LocationID location_id) { current_location_id = location_id;}
void Character::SetRect(SDL_Rect newRect){rect = newRect;}
void Character::SetPos(SDL_Rect newRect){rect.x = newRect.x;rect.y = newRect.y;}
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

void Character::AddToInventory(Item *item) { inventory.push_back((Item *const) item); }
void Character::RemoveFromInventory(ItemID item_id) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
                                   [item_id](Item *i) { return i->GetItemID() == item_id; }), inventory.end());
}

void Character::EquipItem(Item* item) {
    if (item->GetHandsNeeded() > 0) {
        if (item->GetHandsNeeded() == 2) {
            if (equipped_items.first == nullptr && equipped_items.second == nullptr) {
                equipped_items.first = item;
                LHand = item->GetItemID();
                equipped_items.second = item;
                RHand = item->GetItemID();
                RemoveFromInventory(item->GetItemID());
            }
        } else {
            if (item->GetHandsNeeded() == 1) {
                if (equipped_items.first == nullptr) {
                    equipped_items.first = item;
                    LHand = item->GetItemID();
                    RemoveFromInventory(item->GetItemID());
                }else{
                    if (equipped_items.second == nullptr) {
                        equipped_items.second = item;
                        RHand = item->GetItemID();
                        RemoveFromInventory(item->GetItemID());
                    }
                }
            }


        }
    }
    UpdateCurrentStats();
}
void Character::UnequipItem(ItemID id) {
    if (LHand != ItemID::NONE || RHand != ItemID::NONE) {
        if (id == RHand && id == LHand) {
            AddToInventory(equipped_items.first);
            RHand = ItemID::NONE;
            LHand = ItemID::NONE;
            equipped_items.first = nullptr;
            equipped_items.second = nullptr;
        } else {
            if (id == LHand) {
                AddToInventory(equipped_items.first);
                LHand = ItemID::NONE;
                equipped_items.first = nullptr;
            } else {
                AddToInventory(equipped_items.second);
                RHand = ItemID::NONE;
                equipped_items.second = nullptr;
            }
        }
    }
    UpdateCurrentStats();
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

//void Character::AddQuest(const QuestID quest) { quest_log.push_back(quest); }
//void Character::CompleteQuest(QuestID quest_id) {
//    quest_log.erase(std::remove_if(quest_log.begin(), quest_log.end(),
//                                   [quest_id](const QuestID q) { return q == quest_id; }), quest_log.end());
//}




void Character::SpendFate()
{
    fate_points--;
}
void Character::ResetToBaseStats(){
    current_stats = base_stats;
}
void Character::UpdateCurrentStats() {
    ResetToBaseStats();

    if (equipped_items.first != nullptr && equipped_items.second != nullptr) {
        if (equipped_items.first->hasStats) {
            if (equipped_items.first->GetHandsNeeded() == 2) {
                if(equipped_items.first->GetItemType() != ItemType::Ranged) {
                    current_stats += equipped_items.first->GetStats();
                }else{
                    if(equipped_items.first->isLoaded){
                        current_stats += equipped_items.first->GetStats();
                    }
                }
            }
        }
    }
    fmt::println("update past check 1");
    if (equipped_items.first != nullptr) {
        if (equipped_items.first->hasStats && equipped_items.first->GetHandsNeeded() == 1) {
            if(equipped_items.first->GetItemType() != ItemType::Ranged) {
                current_stats += equipped_items.first->GetStats();
            }else{
                if(equipped_items.first->isLoaded){
                    current_stats += equipped_items.first->GetStats();
                }
            }
        }
    }
    fmt::println("update past check 2");
    if (equipped_items.second != nullptr) {
        if (equipped_items.second->hasStats && equipped_items.second->GetHandsNeeded() == 1) {
            if (equipped_items.second->GetItemType() != ItemType::Ranged) {
                current_stats += equipped_items.second->GetStats();
            }else{
                if(equipped_items.second->isLoaded){
                    current_stats += equipped_items.second->GetStats();
                }
            }
        }
    }
    fmt::println("update past check 3");
    for(auto e : inventory){
        if(e != nullptr) {
            if (e->hasStats && e->GetHandsNeeded() == 0) {
                current_stats += e->GetStats();
            }
        }
    }
    fmt::println("update done");
}

const std::pair<Item *, Item *> Character::GetEquipment() {
    return equipped_items;
}

int Character::GetBaseSanity() const {
    return base_sanity;
}

int Character::GetBaseStamina() const {
    return base_stamina;
}

Item* Character::FindItem(ItemID id) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
                           [id](Item* item) { return item->GetItemID() == id; });

    return (it != inventory.end()) ? *it : nullptr;
}


ItemID Character::UseItem(ItemID id){
Item* target = FindItem(id);
if(target == nullptr){
    fmt::println("Item NOT found during UseItem");
    }else{
        id = target->UseItem();
        return id;
    }
}




