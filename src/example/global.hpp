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
    TilePlacer,
    Showcase
};
enum class ObjectIDs{
    NONE,
    Shot
};
enum class FloorTileIDs{
    NONE,
    Standard,
    Round,
    Grass0,
    Grass1,
    Grass2,
    Grass3,
    Grass4,
    Grass5,
    Grass6,
    Grass7,
    Grass8,
    TopWalls0,
    TopWalls1,
    TopWalls2,
    TopWalls3,
    TopWalls4,
    TopWalls5,
    Floor0,
    Floor1,
    Floor2

};
enum class Directions{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

//denotes the specific sheet in its CharacterIDs
enum class CharacterAnimations{
    Idle,
    Aim,
    Fire,

};

//CharacterIDs denotes the category of needed spritesheet
enum class CharacterIDs{
    NONE,
    PlayerCharacter,
    Orc,
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