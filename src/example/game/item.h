#pragma once

#include "../global.hpp"
#include "ability.h" // For the ability pointer

class Item {
public:
    Item(ItemID id, ItemType itemType, const std::string& name, uint8_t handsNeeded, bool isEquipped = false, bool isLoaded = false, bool hasStats = true)
            : id(id), itemType(itemType), name(name), handsNeeded(handsNeeded), isEquipped(isEquipped), isLoaded(isLoaded), hasStats(hasStats),
              stats(0,0,0,0,0,0) {}

    // Accessors
    ItemID GetItemID() const { return id; }
    ItemType GetItemType() const { return itemType; }
    const std::string& GetName() const { return name; }
    uint8_t GetHandsNeeded() const { return handsNeeded; }
    bool IsEquipped() const { return isEquipped; }

    // Mutators
    void Equip() { isEquipped = true; }
    void Unequip() { isEquipped = false; }
    void Load() { isLoaded = true;}
    void Fire() {isLoaded = false;}

    // Stats and ability
    Stats& GetStats()  { return stats; }
    void SetStats(const Stats& newStats) { stats = newStats; }

    Ability* GetAbility() const { return ability; }
    void SetAbility(Ability* newAbility) { ability = newAbility; }
    ItemID UseItem(){
        return id;
    }


    bool hasStats;
    bool isLoaded;

private:
    ItemID id;
    ItemType itemType;
    std::string name;
    uint8_t handsNeeded;
    bool isEquipped;


    Stats stats;
    Ability* ability = nullptr; // Pointer to an associated ability

};
