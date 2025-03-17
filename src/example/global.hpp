#pragma once

#include "sor/core.hpp"
#include "sor/sdl_core.hpp"
#include "sor/sdl_shapeops.hpp"
#include <random>
//#include "sor/sdl_game.hpp"
#include <iostream>



using namespace JanSordid::Core;

static int WINDOWSIZE_X = 480*4;
static int WINDOWSIZE_Y = 270 *4;

enum class Mode{
    Game,
    TilePlacer
};
enum class Objects{
    NONE,
    Shot
};
enum class FloorTileStyles{
    NONE,
    Standard,
    Round
};
enum class Directions{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

//denotes the specific sheet in its EntityType
enum class EntityAnimations{
    Idle,
    Aim,
    Fire,

};

//EntityType denotes the category of needed spritesheet
enum class EntityType{
    EnemyType1,
    Orc,
    Turret,
    Hazard,
    Environment
};

enum class PlayerState{
    Idle,
    Idle_Flip,
    Walk,
    Walk_Flip,
    Damage,
    Damage_Flip,
    KnockdownDamage,
    Grounded,
    GetUp,
    KnockdownDamage_Flip,
    Grounded_Flip,
    GetUp_Flip

};

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