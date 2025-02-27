//
// Created by max on 27.01.25.
//

#pragma once
#include <unordered_map>
#include "monster.h"

class MonsterManager {
private:
    std::unordered_map<MonsterID, Monster> monsterMap;

public:
    // Add a monster to the manager
    void addMonster(const Monster& monster) {
        monsterMap[monster.id] = monster;
    }

    // Get a mutable reference to a monster by ID
    Monster* getMonsterByID(MonsterID id) {
        auto it = monsterMap.find(id);
        if (it != monsterMap.end()) {
            return &(it->second); // Return a pointer to the monster
        }
        return nullptr; // Return nullptr if the monster doesn't exist
    }
    Monster GetMonster(MonsterID id) const {
        auto it = monsterMap.find(id);
        if (it != monsterMap.end()) {
            return it->second;  // Return a copy of the Monster
        }
        throw std::runtime_error("Monster ID not found!");
    }

    // Check if a monster exists
    bool hasMonster(MonsterID id) const {
        return monsterMap.find(id) != monsterMap.end();
    }
};
