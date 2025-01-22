//
// Created by Prince of Brass on 20/01/2025.
//
#pragma once
#include "../global.hpp"


///TODO rip out the testing code and put encounters into a encounter manager, split skillcheckengine into fight and skillchecks as well as a seperate dice roller
struct SceneOption;
enum class ExecuteFlags
{
    Wound,
    SanityLoss,
    Heal,
    RegainSan,
    GainItem
};

enum class DialoguePhase{
    Scene,
    DieRoll,
    FateReroll

};
struct SceneOption
{
    std::string Text;

    bool bIsSkillCheck;
    StatNames skill;
    int difficulty;
    std::vector<std::tuple<ExecuteFlags,int8_t >> SuccessOutcomes;
    std::vector<std::tuple<ExecuteFlags,int8_t >> FailureOutcomes;

    int JumpTargetSuccess;
    int JumpTargetFail;

};
struct Scene{

//Background
//compostion, characters, objects... todo
    std::string SceneText;
    std::vector<SceneOption> Options; //todo make check for at least 1!!

};
struct Encounter
{

    //id todo
    //EncounterType...


    std::vector<Scene> Scenes;

};