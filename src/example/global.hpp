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
    LoseItem,
    StartQuest,
    AdvanceQuestStage,
    StartCombat,
    FinishedCombatWIN,
    FinishedCombatLOSS,
    SpawnMonster,
    RemoveEncounter,
    GainBulletLead,
    UnloadSilverBullet,
    UnloadLeadBullet, //todo one unload function may be enough? the requirement splits the outcmes in the scene
    RecoverFate
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

    Intro,
    MonasteryMain,
    VillageMain,
    HunterCamp,
    CorpseDiscovery,
    SkullDiscovery,
    FlowerDiscovery,
    HermitMain,
    RavineMain,
    ForestHeartApproach,
    ForestHeartFinal

};
enum class EncounterTypeID{
    Tutorial,
    Fight,
    Trade,
    Trap,
    Unique,
    FinalZone
    //etc add as needed
};
enum class ItemID {
    NONE,
    Halberd,
    HalberdMaster,
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

    RitualSkullCursed,
    RitualSkullBound, //TODO use?
    RitualSkullFaith,
    Relic,
    BulletLead,
    BulletSilver,
    LoadedGunLead,
    LoadedGunSilver};

enum class ItemType {Melee,Ranged,Magic,Unique};

///DO NOT TOUCH THIS. I assign the MapNode <-> Location using the order of the elements in the enum during Init().
/// ONLY ADD NEW LocationIDs AT THE END OF THE ENUM - Max
enum class LocationID {
    Forest,
    Crossroads,
    Clearing,
    Lake,
    Overgrowth,
    Grove,
    HunterCamp,
    Windmill,
    Village,
    ForestOutskirts,
    MonasteryPath,
    Monastery,
    Hermit,
    Ravine,
    DeepForest,
    Lair,
    UNASSIGNED_LOCATION
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
    UNASSIGNED_MONSTERID,
    Wolf,
    Bear,
    Skeleton,
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
    Wandering,
    Circling,
    Stationary,
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

    enum class NamedColorIndex : u8 {
        Transparent = 0,// In reality this is pink or cyan, but when used as index, the framework will treat it as transparent
        Black = 1,      // Not totally black
        Grey10,         // Charcoal,
        Grey20,         // MidnightBlue,
        Grey30,         // SteelBlue,
        Grey40,         // SlateGray,
        Grey50,         // SlateBlue,
        Grey62,         // BlueGray,       // BaliHai
        Grey75,         // LightSteelBlue, // Casper
        Grey88,         // LightSlateGray, // LinkWater
        White = 10,
        Red25, RedWine = Red25,
        Red50,          // Crimson, Siren
        Red75,          // Monza
        Red,            // Scarlet, Vermilion
        OrangeRed,      // ? BlazeOrange
        Orange,         // OrangePeel, Goldenrod
        Gold,           // Gold
        Yellow,
        LimeYellow,
        Lime, LimeGreen = Lime,
        MalachiteGreen, // Harlequin
        Green,
        ForestGreen,
        DarkForest,
        Teal = 37,
    };
};