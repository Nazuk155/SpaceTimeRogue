#pragma once
#include "../global.hpp"
#include "location.h"
#include <vector>
#include <memory>

class LocationManager {
public:
    void AddItem(std::unique_ptr<Location> location) {
        locations.push_back(std::move(location));
    }

    Location* GetItem(LocationID locationID) {
        for (const auto& location : locations) {
            if (location->GetLocationID() == locationID) {
                return location.get();
            }
        }
        return nullptr; // Return nullptr if not found
    }

    [[nodiscard]] const std::vector<std::unique_ptr<Location>>& GetAllItems() const {
        return locations;
    }

    EncounterID GetEncounterID(LocationID lID) {

      if(!GetItem(lID)->related_events.empty())
      {
          return GetItem(lID)->related_events.back();
      }else {std::cerr << "No Event in Vector ERROR";}
    }

private:
    std::vector<std::unique_ptr<Location>> locations;
};
