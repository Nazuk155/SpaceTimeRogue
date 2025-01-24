#pragma once

#include "../global.hpp"
#include "ability.h" // For the ability pointer

class Item {
public:
    Item(ItemName itemName, ItemType itemType, const std::string& name, uint8_t handsNeeded, bool isEquipped = false)
            : itemName(itemName), itemType(itemType), name(name), handsNeeded(handsNeeded), isEquipped(isEquipped),
              stats(0,0,0,0,0,0) {}

    // Accessors
    ItemName GetItemName() const { return itemName; }
    ItemType GetItemType() const { return itemType; }
    const std::string& GetName() const { return name; }
    uint8_t GetHandsNeeded() const { return handsNeeded; }
    bool IsEquipped() const { return isEquipped; }

    // Mutators
    void Equip() { isEquipped = true; }
    void Unequip() { isEquipped = false; }

    // Stats and ability
    const Stats& GetStats() const { return stats; }
    void SetStats(const Stats& newStats) { stats = newStats; }

    Ability* GetAbility() const { return ability; }
    void SetAbility(Ability* newAbility) { ability = newAbility; }

private:
    ItemName itemName;
    ItemType itemType;
    std::string name;
    uint8_t handsNeeded;
    bool isEquipped;
    Stats stats;
    Ability* ability = nullptr; // Pointer to an associated ability
};
