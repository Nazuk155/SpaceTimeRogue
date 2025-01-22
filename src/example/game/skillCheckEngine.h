//
// Created by Prince of Brass on 20/01/2025.
//

#pragma once
#include "../global.hpp"
#include "character.h"



class SkillChallengeEngine
{   Character* currentCharacter;   //will likely need pointer? or split WP spending and dice adding responsibility
    //todo add character into init + CONSTRUCTOR


    StatNames currentSkill = StatNames::SNEAK;//todo



    uint8_t currentDifficulty =0;
    int8_t currentModifier = 0;

    uint8_t currentSuccesses = 0;
public:
    [[nodiscard]] uint8_t getDifficulty() const
    {
        return currentDifficulty;
    }

    [[nodiscard]] uint8_t getSuccesses() const
    {
        return currentSuccesses;
    }

    std::vector<uint8_t > currentRolls {};
    void changeCharacter(Character* chara) //possibly useless
    {
        currentCharacter = chara;
    }

    void setDifficulty(uint8_t diff)
    {
        currentDifficulty = diff;
    }
    void setModifier(int8_t mod)
    {
        currentModifier = mod;
    }
    void setSkill(StatNames skill)
    {
        currentSkill = skill;
    }

    int currentSkillValue()
    {

        switch (currentSkill) {

            case StatNames::FIGHT:
                return currentCharacter->GetCurrentStats().GetStat(FIGHT);
                // return currentCharacter.Combat;
            case StatNames::SNEAK:
                return currentCharacter->GetCurrentStats().GetStat(SNEAK);
                // return currentCharacter.Stealth;
            case StatNames::SPEED:
                return currentCharacter->GetCurrentStats().GetStat(SPEED);
                //return currentCharacter.Speech;
            case StatNames::WILLPOWER:
                return currentCharacter->GetCurrentStats().GetStat(WILLPOWER);
            case StatNames::KNOWLEDGE:
                return currentCharacter->GetCurrentStats().GetStat(KNOWLEDGE);
            case StatNames::LUCK:
                return currentCharacter->GetCurrentStats().GetStat(LUCK);
                /*
            case Skills::Occult:
                //return currentCharacter.Occult;
            case Skills::Faith :
                //return currentCharacter.Faith;
                 */

        }
    }
    std::string currentSkillName()
    {
        switch (currentSkill) {

            case StatNames::FIGHT:
                return "Fight";
                // return currentCharacter.Combat;
            case StatNames::SNEAK:
                return "Sneak";
                // return currentCharacter.Stealth;
            case StatNames::SPEED:
                return "Speed";
                //return currentCharacter.Speech;
            case StatNames::WILLPOWER:
                return "Willpower";
            case StatNames::KNOWLEDGE:
                return "Knowledge";
            case StatNames::LUCK:
                return "Luck";

        }
    }

    bool checkSkill()
    {
        currentRolls.clear();
        currentSuccesses = 0;
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 seed(rd()); // mersenne_twister_engine seeded with rd()  todo move out of function
        std::uniform_int_distribution<> dice(1, 6);
        //do rolls, count successes
        fmt::println("Testing: {}",currentSkillName());
        fmt::println("Current value {}", currentSkillValue());
        for(int i = 0; i < currentSkillValue()+currentModifier;i++)
        {
            uint8_t result = dice(seed);
            //fmt::print("{} ", result); //todo to render -> figure out communication / step flags
            currentRolls.push_back(result);
            //std::cout << result << " ";
            if(result > 4)
                currentSuccesses++;
            fmt::println("loop");
        }

        if (currentSuccesses >= currentDifficulty)
            return true;
        return false;
    }
    bool addFateDice()
    {
        //todo add safety?
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 seed(rd()); // mersenne_twister_engine seeded with rd()  todo move out of function
        std::uniform_int_distribution<> dice(1, 6);
        //do rolls, count successes

        uint8_t result = dice(seed);
        fmt::println("{} ", result);
        currentRolls.push_back(result);

        if(result > 4)
            currentSuccesses++;

        if (currentSuccesses >= currentDifficulty)
            return true;
        return false;


    }


    bool bIsActive = false;


};