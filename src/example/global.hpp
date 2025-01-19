#pragma once

#include "sor/core.hpp"
#include "sor/sdl_core.hpp"
#include "sor/sdl_shapeops.hpp"
#include <random>
//#include "sor/sdl_game.hpp"

using namespace JanSordid::Core;


enum StatNames { SPEED, SNEAK, FIGHT, WILLPOWER, KNOWLEDGE, LUCK };
enum class ItemName {Halbert,Torch,Tome};
enum class ItemType {Weapon,Magic,Unique};
enum class AbilityName {
    ReduceStaminaLoss,
    DrawExtraItem,
    // Add more abilities as needed
};
enum class QuestID {
    SlayMonsters,
    VisitChurch
    //add more as needed
};

struct Stats {
    std::unordered_map<StatNames, int> stats;

    Stats(int speed, int sneak, int fight, int willpower, int knowledge, int luck) {
        stats[SPEED] = speed;
        stats[SNEAK] = sneak;
        stats[FIGHT] = fight;
        stats[WILLPOWER] = willpower;
        stats[KNOWLEDGE] = knowledge;
        stats[LUCK] = luck;
    }

    // Get a stat value
    int GetStat(StatNames stat_name) const {
        return stats.at(stat_name);
    }

    // Modify a stat value
    void AdjustStat(StatNames stat_name, int amount) {
        stats[stat_name] += amount;
    }

    // Set a stat value directly
    void SetStat(StatNames stat_name, int value) {
        stats[stat_name] = value;
    }
};