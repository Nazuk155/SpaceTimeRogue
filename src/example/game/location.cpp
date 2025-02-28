#include "location.h"
#include "map.h"

// Constructor
Location::Location(std::string name, LocationID id)
        : name(name), id(id), map_slot(nullptr), first_visit(true),
          fog_of_war(true), unique_event_id(-1), reward_icon_1(-1), reward_icon_2(-1),
          quest_marker(false) {}

Location::Location( LocationID id)
        : name("Dummy"), id(id), map_slot(nullptr), first_visit(true),
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
LocationID Location::GetLocationID() const { return id;}
std::string Location::GetLocationString() const {return name;}

Map_Slot* Location::GetMapSlot() {
    if(!map_slot) {
        std::cerr << "Error: Map_Slot " << map_slot << " does not exist.\n";
        return nullptr;
    }else{
        return map_slot;
    }
}

void Location::SetName(std::string newname) {
    name = std::move(newname);
}

void Location::AddMonster(const Monster& monster) {
    monsters.push_back(monster);  // Copy the Monster into the location
}
void Location::RemoveMonster(MonsterID id) {
    auto it = std::find_if(monsters.begin(), monsters.end(),
                           [id](const Monster& m) { return m.id == id; });
    if (it != monsters.end()) {
        monsters.erase(it);  // Only removes the first matching monster
    }
}
