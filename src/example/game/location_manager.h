#pragma once

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

    const std::vector<std::unique_ptr<Location>>& GetAllItems() const {
        return locations;
    }

private:
    std::vector<std::unique_ptr<Location>> locations;
};
