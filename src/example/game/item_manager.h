#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "item.h"
#include <vector>
#include <memory>

class ItemManager {
public:
    void AddItem(std::unique_ptr<Item> item) {
        items.push_back(std::move(item));
    }

    Item* GetItem(ItemName itemName) {
        for (const auto& item : items) {
            if (item->GetItemName() == itemName) {
                return item.get();
            }
        }
        return nullptr; // Return nullptr if not found
    }

    const std::vector<std::unique_ptr<Item>>& GetAllItems() const {
        return items;
    }

private:
    std::vector<std::unique_ptr<Item>> items;
};

#endif // ITEM_MANAGER_H
