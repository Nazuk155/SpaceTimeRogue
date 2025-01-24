/// Created by Prince of Brass on 20/01/2025
#pragma once
#include "../global.hpp"

/// TODO rip out the testing code and put encounters into an EncounterManager,
/// split SkillCheckEngine into fight and skill checks as well as a separate dice roller.



// Enumerations for various flags and phases
enum class ExecuteFlags {
    Wound,
    SanityLoss,
    Heal,
    RegainSan,
    GainItem
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
    Vector<ItemName> rewardItemIDs;
    Vector<ItemName> failureItemIDs;


};

struct Scene {
    const char *sceneText;
    std::vector<SceneOption> options; // Ensure at least one option exists.

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
