#pragma once
#include "../global.hpp"
#include "item.h" // Assuming Item is another class you have



class CharacterBlueprint {
public:
    std::string name;
    int base_stamina;
    int base_sanity;
    Stats base_stats;
    Stats base_stats_boundary;
    int focus;
    Ability* ability;

    std::string fate_refill_condition;
    std::vector<Item*> starting_items;

    CharacterBlueprint(const std::string& name, int base_stamina, int base_sanity,
                       Stats base_stats,Stats base_stats_boundary, int focus, Ability* ability,
                       const std::string& fate_condition, std::vector<Item*> items);

    // character_blueprint.cpp (or equivalent .cpp file)



};
