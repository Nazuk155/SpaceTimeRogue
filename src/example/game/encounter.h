/// Created by Prince of Brass on 20/01/2025
#pragma once
#include "../global.hpp"

enum class EnvironmentType
{
    VillageOutskirts,
    ForestOutskirts,
    MonasteryPath,
    DenseForest,
    CurseForest
};

// Enumerations for various flags and phases
enum class ExecuteFlags {
    Wound,
    SanityLoss,
    Heal,
    RegainSan,
    GainItem
};

enum class RequirementFlags
{
    speed,
    sneak,
    fight,
    willpower,
    occult,
    faith,

    stamina,
    sanity,

    //differ from just health/san - depend on relative max for char  -might benefit from differet implenentation - percentages?
    isPhysicallyWounded, //do not require value - ignored
    isMentallyWounded,

    item,  //check if in inventory
    quest //todo might reed more, unless we enconde -> quest 12 ar stage 100 = 012100 etc



};




enum class DialoguePhase {
    Scene,
    DieRoll,
    FateReroll
};

// Structs for options, scenes, and encounters
struct SceneOption {
    const char * text;
    bool isSkillCheck;
    StatNames skill;
    int difficulty;
    std::vector<std::tuple<ExecuteFlags, int8_t>> successOutcomes;
    std::vector<std::tuple<ExecuteFlags, int8_t>> failureOutcomes;
    int jumpTargetSuccess;
    int jumpTargetFail;
    Vector<ItemID> rewardItemIDs; //TODO seems to be a redundancy
    Vector<ItemID> failureItemIDs;
    Vector<std::tuple<RequirementFlags, int8_t>> requirements = {};
    bool bHasRequirements = false;

};


enum class SceneCompositionEntities
{
    Character,
    Wolf,
    Villager,
    Werewolf,
    MonasteryGate,
    Monk,
    Boar,
    Hermit
};
enum class SceneCompositionSlots
{
    CharacterMain,
    CharacterFront,
    EnemyMain,
    Enemy_2,
    Enemy_3,
    InteractionMain

};


struct Scene {
    const char *sceneText;
    EnvironmentType background;
    //std::Vector composition
    std::vector<SceneOption> options; // Ensure at least one option exists.

    std::vector<std::tuple<SceneCompositionEntities,SceneCompositionSlots>> compositionVector ={};

    bool validate() const {
        return !options.empty();
    }
};

struct Encounter {
    EncounterID id; // enum with all encounter names in global
    EncounterTypeID type; // enum for encounter types in global
    std::vector<Scene> scenes;
    DialoguePhase currentDialoguePhase;

    bool validate() const {
        for (const auto& scene : scenes) {
            if (!scene.validate()) {
                return false;
            }
        }
        return true;
    }
};
