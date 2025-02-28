/// Created by Prince of Brass on 20/01/2025
#pragma once

#include "../global.hpp"
#include "quests.h"

enum class EnvironmentType {
    Village,
    Village2,
    WindmillOutskirts,
    OakPath,
    HunterCamp,
    VillageOutskirts,
    ForestOutskirts,
    HermitLodge,
    MonasteryPath,
    MonasteryOutside,
    MonasteryGate,
    MonasteryInterior,
    ForestLake,
    ForestClearing,
    DenseForest,
    HeartApproach,
    ForestHeart
};

// Enumerations for various flags and phases


enum class RequirementFlags {
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
    hasQuestOnStage,
    hasQuest,
    notOnQuest,
    notOnStage


};


enum class DialoguePhase {
    Scene,
    DieRoll,
    FateReroll
};

// Structs for options, scenes, and encounters
struct SceneOption {
    const char *text;
    bool isSkillCheck;
    StatNames skill;
    int difficulty;
    std::vector<std::tuple<ExecuteFlags, int>> successOutcomes;
    std::vector<std::tuple<ExecuteFlags, int>> failureOutcomes;
    int jumpTargetSuccess;
    int jumpTargetFail;
    Vector<ItemID> rewardItemIDs;
    Vector<ItemID> failureItemIDs;
    Vector<std::tuple<RequirementFlags, int>> requirements = {};
    bool bHasRequirements = false;

};


enum class SceneCompositionEntities {
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
    Hermit,

    //Overlays
    RitualSkullOverlay
};
enum class SceneCompositionSlots {
    OverlayMainPoint,
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

    std::vector<std::tuple<SceneCompositionEntities, SceneCompositionSlots>> compositionVector = {};
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

    ///The Combat relevant attributes below can simply be ignored for encounters that do not contain a StartCombat ExecuteFlag
    std::vector<MonsterID> monsterIDs; // for encounters that can start a combat with up to 3 monsters
    int fightVictorySzene,fightDefeatSzene;
    int hp;
    //jump back szenes that eTrackerSaver copys before eTracker gets overwritten with the combat event. Simply set these to win/loss result scenes
    // these are used in the ExecuteFlags FinishedCombatWIN/LOSS to go to the correct scene of the encounter that got paused for combat.

    bool validate() const {
        for (const auto &scene: scenes) {
            if (!scene.validate()) {
                return false;
            }
        }
        return true;
    }
    void setHP(int newHP){hp = newHP;}
};

///test encounter for triggering& resolving a fight while jumping back into the encounter at the correct scenes. Set to Smith node.
inline Encounter testingCombat
        {
                EncounterID::Testing_Combat,
                EncounterTypeID::Unique,
                {
                        {"The old monastery of Saint Lykon stands before you. You approach its gates.",
                         EnvironmentType::MonasteryOutside,
                         {
                                 {
                                         "Fight a wolf",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::StartCombat, 0}},
                                         {},
                                         1, 255,
                                         {},
                                         {},
                                         {}, //If not on Quest 3, start quest 3
                                         false


                                 }
                         },
                         {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain}}
                        }, {"Choose",
                            EnvironmentType::MonasteryGate,
                            {
                                    {
                                            "Back to Szene 0",
                                            false,
                                            StatNames::FIGHT,
                                            0,
                                            {},
                                            {},
                                            0, 0,
                                            {},
                                            {},
                                            {}, //If not on Quest 3, start quest 3
                                            false

                                    },  //Require healing
                                    {

                                            "I need a place to rest. [Regain San]",
                                            false,
                                            StatNames::FIGHT,
                                            0,
                                            {},
                                            {},
                                            6, 255,
                                            {},
                                            {},
                                            {}, //If not on Quest 3, start quest 3
                                            false


                                    },  //Regain San/Rest
                                    // {} // I found this skull in the forest? TODO Expand MSQ, Sidequests etc


                            },
                            {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                             {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}}
                        },
                        {"A monk opens the gate. \"Welcome, I am Brother Albert of the Order of Preachers. What brings you here? \"",
                         EnvironmentType::MonasteryGate,
                         {
                                 {
                                         "I am Franz Todbringer, a mercenary hired to hunt down the beasts plaguing the forest",
                                         false,
                                         StatNames::FIGHT,
                                         0,
                                         {},
                                         {},
                                         3, 255,
                                         {},
                                         {},
                                         {}, //If not on Quest 3, start quest 3
                                         false
                                 },//todo choose a name for intro? based on class?,
                                 {
                                         "I am in need of healing. I was hunting the beasts plaguing the forest and got wounded. My name is Franz Todbringer",
                                         false,
                                         StatNames::FIGHT,
                                         0,
                                         {},
                                         {},
                                         4, 255,
                                         {},
                                         {},
                                         {{RequirementFlags::isPhysicallyWounded,
                                           3}}, //If not on Quest 3, start quest 3
                                         false

                                 }
                         },
                         {
                                 {SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}
                         }

                        },
                        {  //Scene 3 - Basic Intro Answer
                                "FIGHT WIN",
                                EnvironmentType::MonasteryGate,
                                {
                                        {
                                                "BACK TO 0",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                0, 255,
                                                {},
                                                {},
                                                {}, //If not on Quest 3, start quest 3
                                                false

                                        },
                                        {
                                                "Finish Event and Remove Encounter from Location",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::RemoveEncounter,0}},
                                                {},
                                                255, 255,
                                                {},
                                                {},
                                                {}, //If not on Quest 3, start quest 3
                                                false

                                        }
                                        // {} // I found this skull in the forest? TODO Expand MSQ, Sidequests etc
                                },
                                {
                                        {SceneCompositionEntities::Character,
                                         SceneCompositionSlots::CharacterAtBottomMain},
                                        {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}

                                }},
                        { //Scene 4 - Basic Healing Answer

                                "FIGHTLOSS",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"Back to 0",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {},
                                         {},
                                         0,
                                         255,
                                         {},
                                         {},
                                         {},
                                         false
                                        },
                                        {
                                                "Finish Event",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                255, 255,
                                                {},
                                                {},
                                                {}, //If not on Quest 3, start quest 3
                                                false

                                        }
                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}}


                        },
                        { //Scene 5 - Healing Description
                                //{{ExecuteFlags::Heal, 3}}
                                "The monks are adept keepers of natural magic. Your wounds are cleaned and treated.",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"The poultices do their work. It is time to move on. [+4 Stamina]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::Heal, 1}, {ExecuteFlags::Heal, 4}},
                                         {},
                                         255,
                                         255,
                                         {},
                                         {}
                                        }

                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}
                                }
                        },
                        { //Scene 6 - Rest/Prayer Answer
                                "Of course. We gladly offer you sanctuary",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"Rest and recover. [Regain San]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {},
                                         {},
                                         7,
                                         255,
                                         {},
                                         {}
                                        },
                                        {"[Faith 6] Spend your time in prayer and meditation. [Chance to recover more.]",
                                         true,
                                         StatNames::FAITH,
                                         3,
                                         {},
                                         {},
                                         8,
                                         7,
                                         {},
                                         {},
                                         {{RequirementFlags::faith, 6}},
                                         true
                                        }
                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}}

                        },
                        {
                                //Scene 7 Rest Description.
                                //{ExecuteFlags::Heal,1},{ExecuteFlags::RegainSan,3}
                                "You spend some time in the monastery. The nightmares and exhaustion fade.",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"It is time to move on. [+1 Stamina +3 San]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::Heal, 1}, {ExecuteFlags::RegainSan, 3}},
                                         {},
                                         255,
                                         255,
                                         {},
                                         {}
                                        },

                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::InteractionMain}
                                }


                        },
                        {
                                //Scene 8 - Prayer Success description
                                "You spend time in deep prayer. Your soul recovers from its ordeals.",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"It is time to move on. [+1 Stamina +6 San]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::Heal, 1}, {ExecuteFlags::RegainSan, 6}},
                                         {},
                                         255,
                                         255,
                                         {},
                                         {}
                                        },

                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::InteractionMain}
                                }
                        }

                }, DialoguePhase::Scene,{MonsterID::Wolf,MonsterID::Wolf},3,4 // Starting dialogue phase
        };
inline Encounter monasteryMain
        {
                EncounterID::MonasteryMain,
                EncounterTypeID::Unique,
                {
                        {"The old monastery of Saint Lykon stands before you. You approach its gates.",
                         EnvironmentType::MonasteryOutside,
                         {
                                 {
                                         "You are a stranger to the monks. Introduce yourself and ask for entry.",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::StartQuest, 3}},
                                         {},
                                         2, 255,
                                         {},
                                         {},
                                         {{RequirementFlags::notOnQuest, 3}}, //If not on Quest 3, start quest 3
                                         true


                                 },
                                 {
                                         "You require aid from the monks. Ask for entry.",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {},
                                         {},
                                         1, 255,
                                         {},
                                         {},
                                         {{RequirementFlags::hasQuest, 3}}, //If not on Quest 3, start quest 3
                                         true


                                 },
                                 {
                                         "[Leave] There is nothing here that you require.",
                                         false,
                                         StatNames::FIGHT,
                                         0,
                                         {},
                                         {},
                                         255, 255,
                                         {},
                                         {},
                                         {},
                                         true

                                 }
                         },
                         {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain}}
                        }

                        , {"Welcome back, how may our humble order help you?",
                           EnvironmentType::MonasteryGate,
                           {
                                   {
                                           "I am in need of healing. [Heal]",
                                           false,
                                           StatNames::FIGHT,
                                           0,
                                           {},
                                           {},
                                           4, 255,
                                           {},
                                           {},
                                           {{RequirementFlags::isPhysicallyWounded,
                                             3}}, //If not on Quest 3, start quest 3
                                           true

                                   },  //Require healing
                                   {

                                           "I need a place to rest. [Regain San]",
                                           false,
                                           StatNames::FIGHT,
                                           0,
                                           {},
                                           {},
                                           6, 255,
                                           {},
                                           {},
                                           {}, //If not on Quest 3, start quest 3
                                           true


                                   },  //Regain San/Rest
                                   // {} // I found this skull in the forest? TODO Expand MSQ, Sidequests etc


                           },
                           {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                            {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}}
                        },
                        {"A monk opens the gate. \"Welcome, I am Brother Albert of the Order of Preachers. What brings you here? \"",
                         EnvironmentType::MonasteryGate,
                         {
                                 {
                                         "I am Franz Todbringer, a mercenary hired to hunt down the beasts plaguing the forest",
                                         false,
                                         StatNames::FIGHT,
                                         0,
                                         {},
                                         {},
                                         3, 255,
                                         {},
                                         {},
                                         {}, //If not on Quest 3, start quest 3
                                         false
                                 },//todo choose a name for intro? based on class?,
                                 {
                                         "I am in need of healing. I was hunting the beasts plaguing the forest and got wounded. My name is Franz Todbringer",
                                         false,
                                         StatNames::FIGHT,
                                         0,
                                         {},
                                         {},
                                         4, 255,
                                         {},
                                         {},
                                         {{RequirementFlags::isPhysicallyWounded,
                                           3}}, //If not on Quest 3, start quest 3
                                         true

                                 }
                         },
                         {
                                 {SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}
                         }

                        },
                        {  //Scene 3 - Basic Intro Answer
                                "I see. What brings you to our monastery?",
                                EnvironmentType::MonasteryGate,
                                {
                                        {
                                                "I am in need of healing.",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                4, 255,
                                                {},
                                                {},
                                                {{RequirementFlags::isPhysicallyWounded,
                                                  3}}, //If not on Quest 3, start quest 3
                                                true

                                        },  //Require healing
                                        {

                                                "I need a place to rest.",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                6, 255,
                                                {},
                                                {},
                                                {}, //If not on Quest 3, start quest 3
                                                true


                                        }  //Regain San/Rest
                                        // {} // I found this skull in the forest? TODO Expand MSQ, Sidequests etc
                                }   ,
                                {
                                        {SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                        {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}

                                }},
                        { //Scene 4 - Basic Healing Answer

                                "Of course. We gladly provide for those in need",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"Rest and recover. [Regain Stamina]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {},
                                         {},
                                         5,
                                         255,
                                         {},
                                         {}
                                        }
                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}}


                        },
                        { //Scene 5 - Healing Description
                                //{{ExecuteFlags::Heal, 3}}
                                "The monks are adept keepers of natural magic. Your wounds are cleaned and treated.",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"The poultices do their work. It is time to move on. [+4 Stamina]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::Heal, 1}, {ExecuteFlags::Heal, 4}},
                                         {},
                                         255,
                                         255,
                                         {},
                                         {}
                                        },

                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}
                                }
                        },
                        { //Scene 6 - Rest/Prayer Answer
                                "Of course. We gladly offer you sanctuary",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"Rest and recover. [Regain San]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {},
                                         {},
                                         7,
                                         255,
                                         {},
                                         {}
                                        },
                                        {"[Faith 6] Spend your time in prayer and meditation. [Chance to recover more.]",
                                         true,
                                         StatNames::FAITH,
                                         3,
                                         {},
                                         {},
                                         8,
                                         7,
                                         {},
                                         {},
                                         {{RequirementFlags::faith,6}},
                                         true
                                        }
                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterAtBottomMain},
                                 {SceneCompositionEntities::Monk, SceneCompositionSlots::EnemyMain}}

                        },
                        {
                                //Scene 7 Rest Description.
                                //{ExecuteFlags::Heal,1},{ExecuteFlags::RegainSan,3}
                                "You spend some time in the monastery. The nightmares and exhaustion fade.",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"It is time to move on. [+1 Stamina +3 San]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::Heal, 1}, {ExecuteFlags::RegainSan, 3}},
                                         {},
                                         255,
                                         255,
                                         {},
                                         {}
                                        },

                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::InteractionMain}
                                }


                        },
                        {
                                //Scene 8 - Prayer Success description
                                "You spend time in deep prayer. Your soul recovers from its ordeals.",
                                EnvironmentType::MonasteryInterior,
                                {
                                        {"It is time to move on. [+1 Stamina +6 San]",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::Heal, 1}, {ExecuteFlags::RegainSan, 6}},
                                         {},
                                         255,
                                         255,
                                         {},
                                         {}
                                        },

                                },

                                {{SceneCompositionEntities::Character, SceneCompositionSlots::InteractionMain}
                                }
                        }

                },DialoguePhase::Scene // Starting dialogue phase
//             EnvironmentType::MonasteryOutside,
//            const char * text;
//            bool isSkillCheck;
//            StatNames skill;
//            int difficulty;
//            std::vector<std::tuple<ExecuteFlags, int>> successOutcomes;
//            std::vector<std::tuple<ExecuteFlags, int>> failureOutcomes;
//            int jumpTargetSuccess;
//            int jumpTargetFail;
//            Vector<ItemID> rewardItemIDs;
//            Vector<ItemID> failureItemIDs;
//            Vector<std::tuple<RequirementFlags, int>> requirements = {};
//            bool bHasRequirements = false;

        };
