#pragma once

#include "../global.hpp"
#include "location.h"

struct Map_Slot {
    int id;                                      // Unique identifier
    SDL_Point position; // X, Y position
    SDL_Rect locationRect = {position.x, position.y, 128, 128};
    LocationID location_id;                             // ID of the location assigned UNASSIGNED
    //maybe change vector to unordered_map for better lookup
    std::vector<std::pair<int, bool>> connections; // Connections with status (active/inactive)
    std::vector<SDL_Rect> playerRects; // Up to 3 player character positions
    std::vector<SDL_Rect> enemyRects;  // Up to 3 enemy positions



    // Initialize player and enemy rects
    void initializeRects() {
        // Constants for offsets
        const int rectSize = 32;  // Size of each player/enemy rect
        const int radius = 72;    // Distance from the center of the location icon to the player/enemy rects

        // Calculate the center of the location icon
        int centerX = position.x + locationRect.w / 2;
        int centerY = position.y + locationRect.h / 2;

        // Player positions (left side)
        for (int i = 0; i < 3; ++i) {
            int angle = 180 + i * 60; // Angles: 180°, 240°, 300° (left semi-circle)
            int x = centerX + static_cast<int>(radius * cos(angle * M_PI / 180.0)) - rectSize / 2;
            int y = centerY + static_cast<int>(radius * sin(angle * M_PI / 180.0)) - rectSize / 2;
            playerRects.push_back({x, y, rectSize, rectSize});
        }

        // Enemy positions (right side)
        for (int i = 0; i < 3; ++i) {
            int angle = 0 + i * 60; // Angles: 0°, 60°, 120° (right semi-circle)
            int x = centerX + static_cast<int>(radius * cos(angle * M_PI / 180.0)) - rectSize / 2;
            int y = centerY + static_cast<int>(radius * sin(angle * M_PI / 180.0)) - rectSize / 2;
            enemyRects.push_back({x, y, rectSize, rectSize});
        }
    }




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

    std::array<SDL_Rect, 5> generateMonsterRects(SDL_Point position, int textureSize);
};
