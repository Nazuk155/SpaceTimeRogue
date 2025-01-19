#include "location.h"
#include "map.h"

// Constructor
Location::Location(std::string name, int id)
        : name(name), id(id), map_slot(nullptr), first_visit(true),
          fog_of_war(true), unique_event_id(-1), reward_icon_1(-1), reward_icon_2(-1),
          quest_marker(false) {}

// Gets active connections from the Map_Slot
std::vector<int> Location::GetActiveConnections() const {
    std::vector<int> active_connections;
    for (const auto& connection : map_slot->connections) {
        if (connection.second) {
            active_connections.push_back(connection.first);
        }
    }
    return active_connections;
}

// Resets all connections to desired state
void Location::ResetConnections(bool state) {
    if(map_slot) {
        for (auto &connection: map_slot->connections) {
            connection.second = state;
        }
    }
}

void Location::SetMapSlot(Map_Slot* slot) {
    map_slot = slot;
}

Map_Slot* Location::GetMapSlot() {
    return map_slot;
}
