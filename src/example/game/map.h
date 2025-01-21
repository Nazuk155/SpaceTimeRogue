#pragma once

#include "../global.hpp"
#include "location.h"

struct Map_Slot {
    int id;                                      // Unique identifier
    SDL_Point position; // X, Y position
    SDL_Rect rect = {position.x,position.y,128,128};
    LocationID location_id;                             // ID of the location assigned UNASSIGNED
    //maybe change vector to unordered_map for better lookup
    std::vector<std::pair<int, bool>> connections; // Connections with status (active/inactive)

    Map_Slot(int id, SDL_Point pos);
    void AddConnection(int other_slot_id, bool is_active = true);
    void UpdateConnectionStatus(int other_slot_id, bool is_active);
};

class Map {
private:
  //  std::vector<Map_Slot> slots;

public:
    std::vector<Map_Slot> slots; // Vector of all slots

    Map();
    void AddSlot(int id, SDL_Point position);
    void ConnectSlots(int slot1, int slot2, bool is_active = true);
    void SetConnectionStatus(int slot1, int slot2, bool is_active);
    void SetLocation(int mapslotID, Location& location);
    Map_Slot* GetSlotByID(int id);
    void RandomizeForestLocations(const std::vector<int>& forest_slot_ids, const std::vector<int>& location_ids);
};
