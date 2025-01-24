//
// Created by max on 22.01.25.
//
#pragma once
#include "../global.hpp"


class DiceRoller{


public:
    DiceRoller()= default;

    std::random_device rd;  // a seed source for the random number engine


    u8 rollDice(){
        std::mt19937 seed(rd()); // mersenne_twister_engine seeded with rd()  todo move out of function
        std::uniform_int_distribution<> dice(1, 6);

        return dice(seed);
    }
    Vector<u8> rollMultiple(int amount){
        Vector<u8> result;
        for(int i = 0; i< amount;i++){
            result.push_back(rollDice());
        }
        return result;
    }
};
