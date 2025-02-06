#include "map.h"
#include <iostream>

// Constructor for Map_Slot
Map_Slot::Map_Slot(int id, SDL_Point pos)
        : id(id), position(pos), locationRect({pos.x, pos.y, 128, 128}), location_id(LocationID::UNASSIGNED) {initializeRects();}

// Adds a connection to another slot
void Map_Slot::AddConnection(int other_slot_id, bool is_active) {
    connections.push_back({other_slot_id, is_active});
}

// Updates the connection status
void Map_Slot::UpdateConnectionStatus(int other_slot_id, bool is_active) {
    for (auto& connection : connections) {
        if (connection.first == other_slot_id) {
            connection.second = is_active;
            return;
        }
    }
}

// Constructor for Map
Map::Map() {}

// Adds a new map slot
void Map::AddSlot(int id, SDL_Point position) {
    slots.push_back(Map_Slot(id,position));
}

// Connects two slots
void Map::ConnectSlots(int slot1, int slot2, bool is_active) {
    slots[slot1 ].AddConnection(slot2, is_active);
    slots[slot2 ].AddConnection(slot1, is_active);
}

// Sets the connection status between two slots
void Map::SetConnectionStatus(int slot1, int slot2, bool is_active) {
    slots[slot1 ].UpdateConnectionStatus(slot2, is_active);
    slots[slot2 ].UpdateConnectionStatus(slot1, is_active);
}

// Gets a slot by its ID
Map_Slot* Map::GetSlotByID(int id) {
    if (id >= 0 && static_cast<size_t>(id) <= slots.size()) {
        return &slots[id];
    }
    return nullptr;
}

// Randomizes forest locations
void Map::RandomizeForestLocations(const std::vector<int>& forest_slot_ids, const std::vector<int>& location_ids) {
    std::vector<int> shuffled_ids = location_ids;

    // Shuffle the location IDs
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(shuffled_ids.begin(), shuffled_ids.end(), rng);

    // Assign the shuffled IDs to the forest slots
    size_t index = 0;
    for (int slot_id : forest_slot_ids) {
        if (index < shuffled_ids.size()) {
            slots[slot_id].location_id = static_cast<LocationID>(shuffled_ids[index++]);
        }
    }
}
// Assign a Location to a Slot and set Pointer to Slot in Location
void Map::SetLocation(int mapslotID, Location& location) {
    if (GetSlotByID(mapslotID)) {
        GetSlotByID(mapslotID)->location_id = location.id;   // Set location ID in the Map_Slot
        location.SetMapSlot(GetSlotByID(mapslotID));        // Link the Location to the Map_Slot
    } else {
        std::cerr << "Error: Map_Slot with ID " << mapslotID << " does not exist.\n";
    }
}
std::array<SDL_Rect, 5> Map::generateMonsterRects(SDL_Point position, int textureSize) {
    std::array<SDL_Rect, 5> monsterRects;

    // Define static offsets relative to the top-left corner
    int offset = textureSize + 10; // Spacing between the location and monster textures

    monsterRects[0] = {position.x - offset, position.y - offset, textureSize, textureSize}; // Top-left
    monsterRects[1] = {position.x + offset, position.y - offset, textureSize, textureSize}; // Top-right
    monsterRects[2] = {position.x - offset, position.y + offset, textureSize, textureSize}; // Bottom-left
    monsterRects[3] = {position.x + offset, position.y + offset, textureSize, textureSize}; // Bottom-right
    monsterRects[4] = {position.x, position.y + 2 * offset, textureSize, textureSize};      // Below the location texture

    return monsterRects;
}

