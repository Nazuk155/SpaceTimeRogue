/// Created by Prince of Brass on 20/01/2025
#pragma once
#include "../global.hpp"
#include "quests.h"
enum class EnvironmentType
{
    Village,
    Village2,
    WindmillOutskirts,
    OakPath,
    HunterCamp,
    VillageOutskirts,
    ForestOutskirts,
    HermitLodge,
    MonasteryPath,
    ForestLake,
    ForestClearing,
    DenseForest,
    HeartApproach,
    ForestHeart
};

// Enumerations for various flags and phases
enum class ExecuteFlags {
    Wound,
    SanityLoss,
    Heal,
    RegainSan,
    GainItem,
    StartQuest,
    AdvanceQuestStage
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
    hasEquipped,//check if item equipped -> todo if loaded gun equipped...
    quest //todo might need more, unless we encode -> quest 12 ar stage 100 = 12100 etc



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
    std::vector<std::tuple<ExecuteFlags, int>> successOutcomes;
    std::vector<std::tuple<ExecuteFlags, int>> failureOutcomes;
    int jumpTargetSuccess;
    int jumpTargetFail;
    Vector<ItemID> rewardItemIDs; //TODO seems to be a redundancy
    Vector<ItemID> failureItemIDs;
    Vector<std::tuple<RequirementFlags, int>> requirements = {};
    bool bHasRequirements = false;

};


enum class SceneCompositionEntities
{
    Character,
    Wolf,
    Villager1,
    VillagerCouple,
    Villager2,
    Healer,
    Werewolf,
    Hunter,
    MonasteryGate,
    Monk,
    Abbot,
    Bear,
    Hermit
};
enum class SceneCompositionSlots
{
    CharacterMain,
    CharacterAtBottomMain,
    CharacterFront,
    EnemyMain,
    NPCAtBottomMain,
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
    //bool bShowPreviousDicerolls=false;

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
