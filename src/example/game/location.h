#pragma once

#include "../global.hpp"
#include "monster.h"

class Map_Slot;

class Location {
private:
    Map_Slot* map_slot; // Pointer to the associated Map_Slot

public:
    std::string name;
    LocationID id;
    bool first_visit;
    bool fog_of_war;
    int unique_event_id;
    std::vector<EncounterID> related_events;
    std::vector<Monster> monsters;
    int reward_icon_1, reward_icon_2;
    bool quest_marker;

    Location(std::string name, LocationID id);
    explicit Location(LocationID id);

    [[nodiscard]] std::vector<int> GetActiveConnections() const;
    void SetMapSlot(Map_Slot* m);
    void ResetConnections(bool state);
    void SetName(std::string newname);
    [[nodiscard]] LocationID GetLocationID () const;
    [[nodiscard]] std::string GetLocationString() const;

    Map_Slot* GetMapSlot();
    void AddMonster(const Monster& monster);
    void RemoveMonster(MonsterID id);

};