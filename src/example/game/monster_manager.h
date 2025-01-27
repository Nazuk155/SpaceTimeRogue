//
// Created by max on 27.01.25.
//

#pragma once
#include <unordered_map>
#include "example/global.hpp"
#include "monster.h"

class MonsterManager {
private:
    std::unordered_map<MonsterID, Monster> monsterMap;

public:
    // Add a monster to the manager
    void addMonster(const Monster& monster) {
        monsterMap[monster.id] = monster;
    }

    // Retrieve a monster by ID
    const Monster* getMonsterByID(MonsterID id) const {
        auto it = monsterMap.find(id);
        if (it != monsterMap.end()) {
            return &it->second;
        }
        return nullptr;
    }

    // Check if a monster exists
    bool hasMonster(MonsterID id) const {
        return monsterMap.find(id) != monsterMap.end();
    }
};
