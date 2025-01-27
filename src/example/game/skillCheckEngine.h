//
// Created by Prince of Brass on 20/01/2025.
//

#pragma once
#include "../global.hpp"
#include "character.h"
#include "diceRoller.h"



class SkillChallengeEngine
{
    Character * currentCharacter;

    //will likely need pointer? or split WP spending and dice adding responsibility
    //todo add character into init + CONSTRUCTOR

    DiceRoller diceRoller;
    StatNames currentSkill = StatNames::NONE;//todo



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
            case StatNames::OCCULT:
                return currentCharacter->GetCurrentStats().GetStat(OCCULT);
            case StatNames::FAITH:
                return currentCharacter->GetCurrentStats().GetStat(FAITH);
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
            case StatNames::OCCULT:
                return "Knowledge";
            case StatNames::FAITH:
                return "Luck";

            case NONE:
                return "NONE";
                break;
        }
    }

    bool checkSkill()
    {
        if(currentSkill == NONE){std::cerr << "ERROR: NO SKILL SET! RESULT WILL ALWAYS BE FALSE"; return false;}
        currentRolls.clear();
        currentSuccesses = 0;

        //do rolls, count successes
        fmt::println("Testing: {}",currentSkillName());
        fmt::println("Current value {}", currentSkillValue());

            //fmt::print("{} ", result); //todo to render -> figure out communication / step flags
            currentRolls = diceRoller.rollMultiple(currentSkillValue()+currentModifier);
            //std::cout << result << " ";
            for(auto e : currentRolls){
                if(e > 4) {
                    currentSuccesses++;
                }
            }

            fmt::println("Rolled dice");

        if (currentSuccesses >= currentDifficulty)
            return true;
        return false;
    }
    bool addFateDice()
    {


        uint8_t result = diceRoller.rollDice();
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