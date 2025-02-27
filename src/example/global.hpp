#pragma once

#include "sor/core.hpp"
#include "sor/sdl_core.hpp"
#include "sor/sdl_shapeops.hpp"
#include <random>
//#include "sor/sdl_game.hpp"
#include <iostream>



using namespace JanSordid::Core;

enum class ExecuteFlags {
    NONE,
    Wound,
    SanityLoss,
    Heal,
    RegainSan,
    GainItem,
    StartQuest,
    AdvanceQuestStage,
    StartCombat,
    FinishedCombatWIN,
    FinishedCombatLOSS,
    SpawnMonster
};

enum class GamePhases
        {
    UPKEEP,
    MOVEMENT,
    ENCOUNTER,
    DISASTER
        };


enum StatNames { SPEED, SNEAK, FIGHT, WILLPOWER, OCCULT, FAITH ,NONE};

/*
std::unordered_map<StatNames, std::string> StatNamesStringMap //can likely be done more elegantly?
        {
                {StatNames::SPEED, "Speed"},
                {StatNames::SNEAK, "Sneak"},
                {StatNames::FIGHT, "Fight"},
                {StatNames:WILLPOWER, "Willpower"},
                {StatNames::OCCULT, "Knowledge"},
                {StatNames::FAITH, "Luck"}
        };
        */
enum class EncounterID{
    NO_ENCOUNTER_ASSIGNED, // never assign this to a event. Only output when a location has no events in vector
    Combat_Encounter,
    Forest_Thievery,
    Testing_Combat,
    Generic_FindSurvivor,
    Church_HolyWaterConversation,
    //use recognizable names
    MonasteryMain
};
enum class EncounterTypeID{
    Tutorial,
    Fight,
    Trade,
    Trap,
    Unique,
    //etc add as needed
};
enum class ItemID {
    NONE,
    Halberd,
    Sword,
    BetterSword,
    Torch,
    PrayerBook,
    Honorius,
    Clavicule,
    Icon,
    Candle,
    HandOfGlory,
    GUN,
    Talisman,
    Tome,

    RitualSkull};

enum class ItemType {Melee,Ranged,Magic,Unique};

enum class LocationID {
    Forest,
    Church,
    River,
    Smith,
    Windmill,
    Crossroads,
    Cave,
    Monastery,
    Farm,
    Clearing,
    Townhall,
    Thicket,
    UNASSIGNED
};

enum class AbilityID {
    NONE,   //signifier for empty ability
    WerwolfCorruptionEffects,
    WolfPackAttack,
    ReduceStaminaLoss,
    DrawExtraItem,
    // Add more abilities as needed
};
/*
enum class QuestID {
    SlayMonsters,
    VisitChurch
    //add more as needed
};*/


enum class MonsterID {
    UNASSIGNED,
    Wolf,
    Bear,
    Ghoul,
    Werewolf,
    Vampire,
    // Add other monsters here
};

enum class MonsterType {
    None,
    Undead,
    Beast,
    Spirit,
    // Add other types here
};

enum class MovementType {
    Stalking,
    Fast,
    Flying,
    // Add other movement types here
};




struct Stats {
    std::unordered_map<StatNames, int> stats;

    Stats(int speed, int sneak, int fight, int willpower, int occult, int faith) {
        stats[SPEED] = speed;
        stats[SNEAK] = sneak;
        stats[FIGHT] = fight;
        stats[WILLPOWER] = willpower;
        stats[OCCULT] = occult;
        stats[FAITH] = faith;
    }

    // Overload += operator
    Stats& operator+=(const Stats& rhs) {
        for (const auto& [stat_name, value] : rhs.stats) {
            this->stats[stat_name] += value;
        }
        return *this;
    }
    Stats& operator=(const Stats& rhs) {
        for (const auto& [stat_name, value] : rhs.stats) {
            this->stats[stat_name] = value;
        }
        return *this;
    }


    // Get a stat value
    int GetStat(StatNames stat_name) const {
        return stats.at(stat_name);
    }

    // Modify a stat value
    void AdjustStat(StatNames stat_name, int amount) {
        stats[stat_name] += amount;
    }

    // Set a stat value directly
    void SetStat(StatNames stat_name, int value) {
        stats[stat_name] = value;
    }
};