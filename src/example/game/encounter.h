/// Created by Prince of Brass on 20/01/2025
#pragma once

#include "../global.hpp"
#include "quests.h"

enum class EnvironmentType {
    Village,
    Village2,
    VillageChurch,
    WindmillOutskirts,
    OakPath,
    HunterCamp,
    VillageOutskirts,
    ForestOutskirts,
    SheepTree,
    HermitLodge,
    MonasteryPath,
    MonasteryOutside,
    MonasteryGate,
    MonasteryInterior,
    ForestLake,
    Ravine,
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
    notOnStage,
    SilverBulletLoaded,
    LeadBulletLoaded


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
    Veteran,
    Monk,
    Abbot,
    Bear,
    Hermit,
    SpearSkeleton,
    Mercenary,
    Priest,

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

//to play at game start - start msq, get starting gear
inline Encounter IntroEncounter
        {EncounterID::Intro,

                EncounterTypeID::Unique,
                {
                 {"You arrive at the village of . Some manner of beast has been killing people in the area, and you - a mercenary - were hired to deal with id.", //todo name
                  EnvironmentType::Village,
                  {
                          {
                                  "Continue.",
                                  false,
                                  StatNames::FAITH,
                                  0,
                                  {{ExecuteFlags::StartQuest, 2}},
                                  {},
                                  1, 255,
                                  {ItemID::Sword},
                                  {},
                                  {{RequirementFlags::notOnQuest, 2}}, //If not on Quest 3, start quest 3
                                  true


                          }
                  },
                  {}
                 },
                 {
                         "You are an adept enough fighter with sword and halberd. But what sets you apart rom others?", //todo name
                         EnvironmentType::Village,
                         {
                                 {
                                         "A master-crafted halberd and the skill to use it.",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::GainItem, 1}},
                                         {},
                                         2, 255,
                                         {ItemID::HalberdMaster},
                                         {},
                                         {{}}, //If not on Quest 3, start quest 3
                                         false,


                                 },
                                 {
                                         "You own and can read some grimoires. While not a sorcerer, you have insights into magic natural and daemonic.",
                                         false,
                                         StatNames::OCCULT,
                                         0,
                                         {{ExecuteFlags::GainItem, 1}},
                                         {},
                                         2, 255,
                                         {ItemID::Honorius},
                                         {},
                                         {{}}, //If not on Quest 3, start quest 3
                                         false,


                                 },
                                 {
                                         "You own a gun and four bullets - no mere beast can withstand faith, steel and gunpowder.",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::GainItem, 1}, {ExecuteFlags::GainBulletLead, 3}},
                                         {},
                                         2, 255,
                                         {ItemID::LoadedGunLead},
                                         {},
                                         {{}}, //If not on Quest 3, start quest 3
                                         false,


                                 },
                                 {
                                         "An ancient heirloom - a lead amulet of a pagan forest god of Roman time. With it in hand the forests seem to hide you on their own.",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::GainItem, 1}},
                                         {},
                                         2, 255,
                                         {ItemID::Talisman},
                                         {},
                                         {{}}, //If not on Quest 3, start quest 3
                                         false,

                                 },
                                 {
                                         "Your faith is your shield. You carry your prayer-book with you.",
                                         false,
                                         StatNames::FAITH,
                                         0,
                                         {{ExecuteFlags::GainItem, 1}},
                                         {},
                                         2, 255,
                                         {ItemID::PrayerBook},
                                         {},
                                         {{}}, //If not on Quest 3, start quest 3
                                         false,

                                 }
                         },
                         {{SceneCompositionEntities::Character, SceneCompositionSlots::CharacterFront}}
                 }



                         ,
                         {
                                 "You should get to work. First speak to the villagers to find out more about you quarry.", //todo name
                                 EnvironmentType::Village,
                                 {

                                         {
                                                 "Onwards.",
                                                 false,
                                                 StatNames::OCCULT,
                                                 0,
                                                 {{ExecuteFlags::StartQuest,1}},
                                                 {},
                                                 255, 255,
                                                 {},
                                                 {},
                                                 {}, //If not on Quest 3, start quest 3
                                                 false,


                                         }
                                 },
                                 {{SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront}}



                         }
                }

        };

//Main encounter fot village, handles quest progress, gun acquisition and church
inline Encounter VillageMain
        {
    EncounterID::VillageMain,
    EncounterTypeID::Tutorial,
    {
            {
                "The village of Wölfingen. A nice enough place, if you ignore the death.",//todo NAME!!!
                EnvironmentType::Village,
                {
                        {//speak with your employer INTRO
                                "Speak with your employer.",
                                false,
                                StatNames::OCCULT,
                                0,
                                {},
                                {},
                                4, 255, //TODO
                                {},
                                {},
                                {{RequirementFlags::hasQuestOnStage,1000}}, //
                                true,


                        },
                        {//speak with your employer after intro
                                "Speak with your employer.",
                                false,
                                StatNames::OCCULT,
                                0,
                                {},
                                {},
                                1, 255,
                                {},
                                {},
                                {{RequirementFlags::hasQuest,1},{RequirementFlags::notOnStage,1000}}, //
                                true,


                        },

                        {//speak with the gunner veteran
                                "Speak with Gunner Grimaldus.",
                                false,
                                StatNames::OCCULT,
                                0,
                                {},
                                {},
                                2, 255,
                                {},
                                {},
                                {{RequirementFlags::hasQuest,4}}, //
                                true,


                        },
                        {
                            //visit the priest at the local church

                                "Visit the church.",
                                false,
                                StatNames::OCCULT,
                                0,
                                {},
                                {},
                                9, 255,
                                {},
                                {},
                                {{RequirementFlags::hasQuest,1}}, //
                                true,
                            },
                        {
                                "Leave",
                                false,
                                StatNames::OCCULT,
                                0,
                                {},
                                {},
                                255, 255,
                                {},
                                {},
                                {},
                                false,
                        }
                }
                ,
                {
                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain}
                }

            },
            {
                //Villager 2
                    "\"How goes the hunt?\"",//todo NAME!!!
                    EnvironmentType::Village,
                    {

                            {
                                    //returned from finding 1+ clues
                                    "Describe what you found.",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    3, 255,
                                    {},
                                    {},
                                    {{RequirementFlags::hasQuest,9},{RequirementFlags::notOnQuest,11}}, //If skull no corpse
                                    true,
                            },
                            {
                                    //returned from finding 1+ clues
                                   "Describe what you found.",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    3, 255,
                                    {},
                                    {},
                                    {{RequirementFlags::notOnQuest,9},{RequirementFlags::hasQuest,11}}, //If corpse no skull
                                    true,
                            },
                            {
                                    //returned from finding 1+ clues
                                    "Describe what you found.",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    3, 255,
                                    {},
                                    {},
                                    {{RequirementFlags::hasQuest,9},{RequirementFlags::hasQuest,11}}, //If both clues
                                    true,
                            },
                            {
                                    "Leave",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    255, 255,
                                    {},
                                    {},
                                    {},
                                    false,
                            }


                    },
                    {
                            {
                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                    {SceneCompositionEntities::Villager2,SceneCompositionSlots::CharacterFront},
                                    {SceneCompositionEntities::VillagerCouple,SceneCompositionSlots::EnemyMain}
                            }
                    }

                },

            {
                //veteran gunner

                    "\"What is it?\"",//todo NAME!!!
                    EnvironmentType::Village,
                    {
                            {//no gun
                                    "We need a gun for this beast. (shortened quest - no money)", //TODO?
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::GainBulletLead,5},
                                     {ExecuteFlags::AdvanceQuestStage,4010},
                                     {ExecuteFlags::GainItem,1}},
                                    {},
                                    255, 255,
                                    {ItemID::GUN},
                                    {},
                                    {{RequirementFlags::hasQuestOnStage,4000}}, //If not on Quest 3, start quest 3
                                    true,


                            },
                            {
                                    "We need more bullets for this beast. (shortened quest - no money)", //TODO?
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::GainBulletLead,5},{ExecuteFlags::AdvanceQuestStage,4010}},
                                    {},
                                    255, 255,
                                    {},
                                    {},
                                    {{RequirementFlags::hasQuestOnStage,4005}}, //If not on Quest 3, start quest 3
                                    true,
                                    //gun, get bullets
                            },
                            {
                                    //get extra bullets?
                                    "We need more bullets for this beast. (shortened quest - no money)", //TODO?
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::GainBulletLead,5},{ExecuteFlags::AdvanceQuestStage,4015} },
                                    {},
                                    255, 255,
                                    {},
                                    {},
                                    {{RequirementFlags::hasQuestOnStage,4010}}, //If not on Quest 3, start quest 3
                                    true,
                            },
                            {
                                    //forge silver bullet?
                                    "A silver bullet is needed to put the beast down. Could you melt this down? [Hand over Relic]",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::GainItem,1},{ExecuteFlags::AdvanceQuestStage,1090} },
                                    {},
                                    255, 255,
                                    {ItemID::BulletSilver},
                                    {},
                                    {{RequirementFlags::hasQuestOnStage,1085}}, //If not on Quest 3, start quest 3
                                    true,
                            }

                    }
                    ,
                    {
                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                            {SceneCompositionEntities::Veteran,SceneCompositionSlots::CharacterFront},
                            {SceneCompositionEntities::Villager1,SceneCompositionSlots::EnemyMain}
                    }
                },

            {
                    //Villager 2 - Describe clues
                    "\"Not an ordinary beast indeed. I think it best if you had more firepower. Let's fetch Grimaldus. He is a veteran that knows his way around blackpowder.\"",//todo NAME!!!
                    EnvironmentType::Village,
                    {

                            {
                                    //returned from finding 1+ clues
                                    "Continue.",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    2, 255,
                                    {},
                                    {},
                                    {}, //If skull no corpse
                                    true,
                            }
                    },
                    {
                            {
                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                    {SceneCompositionEntities::VillagerCouple,SceneCompositionSlots::CharacterFront},
                                    {SceneCompositionEntities::Villager2,SceneCompositionSlots::EnemyMain}
                            }
                    }

            },

            {
                    //Villager 2 - Intro
                    R"("You are the mercenary we hired then? Welcome Herr Todbringer." The villager shakes your hand. "As you know something has been killing people. As far as we know it lives in the forest.")",
                    EnvironmentType::Village,
                    {

                            {
                                "Continue.",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    5, 255,
                                    {},
                                    {},
                                    {},
                                false,
                            }
                    },
                    {
                            {
                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                    {SceneCompositionEntities::Villager2,SceneCompositionSlots::EnemyMain}
                            }
                    }

            },
            {
                    //Villager 2 - Intro
                    R"("As per the contract, here is the first part of your payment" [Money NYI], the rest will be handed over once you have the beast." )",
                    EnvironmentType::Village,
                    {

                            {
                                    "Anything new you can tell me about my quarry?",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    6, 255,
                                    {},
                                    {},
                                    {},
                                    true,
                            }
                    },
                    {
                            {
                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                    {SceneCompositionEntities::Villager2,SceneCompositionSlots::EnemyMain}
                            }
                    }

            },
            {
                    //Villager 2 - Intro
                    R"("A bit." The villager nods "We lost a hunter three days ago. He did just not return, so it could have been the beast." )",
                    EnvironmentType::Village,
                    {

                            {
                                    "Continue.",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    7, 255,
                                    {},
                                    {},
                                    {},
                                    false,
                            }
                    },
                    {
                            {
                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                    {SceneCompositionEntities::Villager2,SceneCompositionSlots::EnemyMain}
                            }
                    }

            },
            {
                    //Villager 2 - Intro
                    R"("There have been...", he hesitates, "sightings, I suppose, of large beasts in the forest. Unfortunately some claim to have seen an oversized wolf, while others speak of a lion wielding a sword." )",
                    EnvironmentType::Village,
                    {

                            {
                                    "Anything new you can tell me about my quarry?",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {},
                                    {},
                                    8, 255,
                                    {},
                                    {},
                                    {},
                                    false,
                            }
                    },
                    {
                            {
                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                    {SceneCompositionEntities::Villager2,SceneCompositionSlots::EnemyMain}
                            }
                    }

            },
            {
                    //Villager 2 - Intro
                    R"("You should speak to one of the remaining hunters at their camp, if you want actual facts about the forest" He points to the east. "Their camp is that way, past the windmills. Good luck")",
                    EnvironmentType::Village,
                    {

                            {
                                    "Anything new you can tell me about my quarry?",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::AdvanceQuestStage,1010}},
                                    {},
                                    255, 255,
                                    {},
                                    {},
                                    {}, //If skull no corpse
                                    false,
                            }
                    },
                    {
                            {
                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                    {SceneCompositionEntities::Villager2,SceneCompositionSlots::EnemyMain}
                            }
                    }

            },
            {
                    //Church
                    R"(The village church. Not particularly noteworthy, though they claim to house a relic of Saint Lykon.)",
                    EnvironmentType::VillageChurch,
                    {

                            {
                                    "Pray [Restore 1+ sanity]",
                                    true,
                                    StatNames::FAITH,
                                    3,
                                    {{ExecuteFlags::RegainSan,4}},
                                    {{ExecuteFlags::RegainSan,1}},
                                    255, 255,
                                    {},
                                    {},
                                    {{RequirementFlags::isMentallyWounded,1}}, //If skull no corpse
                                    true,
                            },
                            {
                                    "Ask the priest for the relic.",
                                    true,
                                    StatNames::FAITH,
                                    2,
                                    {},
                                    {},
                                    10, 11,
                                    {},
                                    {},
                                    {{RequirementFlags::hasQuestOnStage,1080}}, //If skull no corpse
                                    true,
                            },
                            {
                                    "Leave",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::RegainSan,2}},
                                    {},
                                    255, 255,
                                    {},
                                    {},
                                    {},
                                    false,
                            }
                    },
                    {

                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterAtBottomMain},
                            {SceneCompositionEntities::Priest,SceneCompositionSlots::NPCAtBottomMain}

                                     }

            },
            {
                    //Church
                    R"(The priest's face shifts between outrage, pensiveness and finally sorrow. "I see no other choice", he finally says. "Take it, and go with God." )",
                    EnvironmentType::VillageChurch,
                    {
                            {
                                    "Thank you.",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::GainItem,1},{ExecuteFlags::AdvanceQuestStage,1085}, {ExecuteFlags::StartQuest,4}},
                                    {},
                                    255, 255,
                                    {/**ItemID::Relic*/},
                                    {},
                                    {}, //If skull no corpse
                                    false,
                            }
                    },
                    {

                                    {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterAtBottomMain},
                                    {SceneCompositionEntities::Priest,SceneCompositionSlots::NPCAtBottomMain}
                    }

            },
            {
                    //Church
                    R"(The priest's face shifts to outrage. "Do you even understand what you are asking for? No!" )",
                    EnvironmentType::VillageChurch,
                    {
                            {
                                    "Leave",
                                    false,
                                    StatNames::OCCULT,
                                    0,
                                    {{ExecuteFlags::AdvanceQuestStage, 1082}},
                                    {},
                                    255, 255,
                                    {},
                                    {},
                                    {}, //If skull no corpse
                                    false,
                            },

                            {
                                "Try to reason with him - surely this is a worthy cause.",
                                        true,
                                        StatNames::FAITH,
                                        2,
                                        {{ExecuteFlags::AdvanceQuestStage,1090}},
                                        {{ExecuteFlags::AdvanceQuestStage,1082}},
                                        10, 255,
                                        {},
                                        {},
                                        {{RequirementFlags::hasQuestOnStage,1080}}, //If skull no corpse
                                        true,
                            }


                    },


                    {

                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterAtBottomMain},
                            {SceneCompositionEntities::Priest,SceneCompositionSlots::NPCAtBottomMain}

                    }

            }


    },DialoguePhase::Scene // Starting dialogue phase

    };

inline Encounter CorpseDiscovery
    {
    EncounterID::CorpseDiscovery,
    EncounterTypeID::Unique,
    {
        {"",
        EnvironmentType::ForestOutskirts,}}
//todo end on dire wolf fight, advance msq / start clue quest 1
    };
inline Encounter SkullDiscovery
        {
    EncounterID::SkullDiscovery,EncounterTypeID::Unique,
    {
            {
                    "A gruesome sight meets your eyes. A skull and a dismembered hand hand from a tree.",
                    EnvironmentType::ForestClearing
                    ,
                    {
                            {
                                    //Occult
                                    "It is clearly a ritual implement. Try to bind it for yourself.",
                                    true,
                                    StatNames::OCCULT,
                                    3, {{ExecuteFlags::StartQuest,9},{ExecuteFlags::AdvanceQuestStage,9010},{ExecuteFlags::GainItem,1}}, {{ExecuteFlags::StartQuest,9},{ExecuteFlags::GainItem,1}},
                                    1, 255,
                                    {ItemID::RitualSkullBound},{ItemID::RitualSkullCursed},{{RequirementFlags::occult,3}},true


                            },
                            {
                                    //Faith
                                    "It is clearly infernal in nature. Recite the Pater Noster when touching it.",
                                    true,
                                    StatNames::FAITH,
                                    3, {{ExecuteFlags::StartQuest,9},{ExecuteFlags::AdvanceQuestStage,9005},{ExecuteFlags::GainItem,1}}, {{ExecuteFlags::StartQuest,9},{ExecuteFlags::GainItem,1}},
                                    1, 255,
                                    {ItemID::RitualSkullBound},{ItemID::RitualSkullCursed},{{RequirementFlags::faith,3}},true
                            },
                            {
                                    //none
                                    "You should take it to somebody knowledgeable.",
                                    false,
                                    StatNames::FAITH,
                                    3, {{ExecuteFlags::StartQuest,9},{ExecuteFlags::AdvanceQuestStage,9000},{ExecuteFlags::GainItem,1}}, {{ExecuteFlags::StartQuest,9},{ExecuteFlags::GainItem,1}},
                                    1, 255,
                                    {ItemID::RitualSkullCursed},{ItemID::RitualSkullCursed},{},false
                            }



                    },
                    {
                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                            {SceneCompositionEntities::RitualSkullOverlay,SceneCompositionSlots::OverlayMainPoint}
                    }
            },
            {
                    "Whatever your methods of dealing with it, this is clearly evidence of supernatural happenings. You take it with you.",
                    EnvironmentType::ForestClearing
                    ,
                    {//check whether first or second
                            {
                                    //first
                                    "Leave. You have your first clue.",
                                    false,
                                    StatNames::OCCULT,
                                    4, {{ExecuteFlags::AdvanceQuestStage,1030}}, {},
                                    255, 255,
                                    {},{},{{RequirementFlags::hasQuestOnStage,1020}},true


                            },
                            {
                                    //Second Clue
                                    "Leave. You have your second clue.",
                                    false,
                                    StatNames::OCCULT,
                                    4, {{ExecuteFlags::AdvanceQuestStage,1030}}, {},
                                    255, 255,
                                    {},{},{{RequirementFlags::hasQuestOnStage,1040}},true


                            },
                            {
                                    //Sequence break
                                    "Leave. Though you are getting ahead of yourself, this is important.",
                                    false,
                                    StatNames::OCCULT,
                                    4, {{ExecuteFlags::AdvanceQuestStage,1030}}, {},
                                    255, 255,
                                    {},{},{{RequirementFlags::hasQuest,1}},true


                            }
                            ,
                            {
                                    //Sequence break 2
                                    "Leave. Though you are getting VERY ahead of yourself, this is important.",
                                    false,
                                    StatNames::OCCULT,
                                    4, {{ExecuteFlags::StartQuest,1},{ExecuteFlags::AdvanceQuestStage,1030}}, {},
                                    255, 255,
                                    {},{},{{RequirementFlags::notOnQuest,1}},true


                            }




                    },
                    {
                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain}
                    }
            }
    },DialoguePhase::Scene // Starting dialogue phase
    //todo advance msq / start clue quest 2

        };

inline Encounter HermitMain
        {
    EncounterID::HermitMain,
    EncounterTypeID::Unique,
    {{
             "The hermit looks at you briefly and nods in greeting before returning to his book.",
             EnvironmentType::HermitLodge,
             {

                     {
                             //MSQ 1 - what do we need?
                             "Brother Kasimir? Brother Albert sends me, Kasimir. We need your advice.",
                             false,
                             StatNames::OCCULT,
                             0, {}, {},
                             1, 3,
                             {},{},
                             {{RequirementFlags::hasQuestOnStage,1020}},true  //TODO fix shortcut
                     },
                     {
                             //MSQ 2 - failed to get silver?
                             "You mentioned another way?", //TODO TEMP
                             false,
                             StatNames::FAITH,
                             0, {}, {},
                             255,
                             255,
                             {},{},
                             {{RequirementFlags::hasQuestOnStage,1082}}, true
                     },
                     {
                             "Leave.",
                             false,
                             StatNames::FAITH,
                             0, {}, {},
                             255,
                             255
                     }
             },
             {

                             {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
                             {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}


             }

     },
     {
             "The man eyes you warily. \"Whatever for?\"",
             EnvironmentType::HermitLodge,
             {

                     {"We found proof that the beast - the werewolf - is a result of demonic invocation. Do you know of anything that might be used to banish it?",
                      false,
                      StatNames::OCCULT,
                      0, {}, {},
                      3, 255,
                      {},{},
                      {{RequirementFlags::occult,2}},true

                     },
                     {"The beast - the werewolf - is a result of a spell. Brother Albert thinks a silver bullet alone will not suffice.",
                      false,
                      StatNames::OCCULT,
                      0, {}, {},
                      2, 255,
                      {},{},{},false

                     },
             },
             {
                     {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
                     {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}

             }

     },
     {
             //no occult answer
             "He furrows his brow. \"I thought something foul was afoot. What sort of spell?\"",
             EnvironmentType::HermitLodge,
             {
                     {
                             "We found a skull with a red symbol. The symbol glows faintly.",
                             false,
                             StatNames::OCCULT,
                             0, {}, {},
                             4, 4
                     }
             },
             {
                     {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
                     {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}

             }
     },
     {
             //occult answer
             "He furrows his brow. \"I believe I know of a thing or two. Do you know anything specific about the invocation?\"",
             EnvironmentType::HermitLodge,
             {
                     {
                             "The demon was invoked through a sigil. I will not name him, but the one invoked is the chimaeric wolf that seeks to return to the seventh heaven.",
                             false,
                             StatNames::OCCULT,
                             0, {}, {},
                             5, 5
                     }
             },
             {
                     {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
                     {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}

             }
     },
     {
             //no occult cont.
             "\"A demonic invocation, perhaps. I suppose some form of astral magic is also possible.\"",
             EnvironmentType::HermitLodge,
             {
                     {
                             "Can you help?",
                             false,
                             StatNames::OCCULT,
                             0, {}, {},
                             5, 5
                     }
             },{
                     {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
                     {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}

             }
     },
     {
             //final 1
             "The hermit nods \"It is true that no ordinary silver will suffice. You will need to melt down an item of sufficient meaning. The relic housed in the village's church will suffice.\"",
             EnvironmentType::HermitLodge,
             {
                     {
                             "I will need to convince its keepers then.",
                             false,
                             StatNames::OCCULT,
                             0, {}, {},
                             6, 255
                     }
             },
             {
                     {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
                     {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}

             }
     },//Fin 2
     {R"("I believe so." The hermit thinks for a moment. "Should you be refused there might be another, worse option. Return to me, should it come to that")",
      EnvironmentType::HermitLodge, {
              {
                      "Very well. Thank you. [Leave.]",
                      false,
                      StatNames::OCCULT,
                      0,
                      {
                              {ExecuteFlags::AdvanceQuestStage, 1080}     //TODO PROGRESS MSQ

                      },
                      {},
                      255, 255
              }
      },
      {
              {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
              {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}

      }
     }
    },DialoguePhase::Scene // Starting dialogue phase

        };
inline Encounter HunterCamp
        {
    EncounterID::HunterCamp,
    EncounterTypeID::Unique,
    {
            {
                "The hunter glances at you. \"What do you want?\"",
                EnvironmentType::HunterCamp,
                {
                        {
                                "I was hired to hunt down the beast. I was told you might know something.",
                                false,
                                StatNames::FIGHT,
                                0,
                                {},{},1,255,
                                {},{},{{RequirementFlags::hasQuestOnStage,1010}},true

                        },
                        {
                                "Journey onwards",
                                false,
                                StatNames::FIGHT,
                                0,
                                {},{},255,255

                        }

                }
                    ,
                {
                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                        {SceneCompositionEntities::Hunter,SceneCompositionSlots::EnemyMain}

                }
            },
            {
                    R"("Trying to die?" He shakes his head. "Sure, your funeral - if even that. FineI can tell you what I actually know to be true.")",
                    EnvironmentType::HunterCamp,
                    {
                        {
                             "Go on.",
                             false,
                             StatNames::FIGHT,
                             0,
                             {},{},2,255,
                             {},{},{{RequirementFlags::hasQuestOnStage,1010}},true

                     }}
                    ,
                    {
                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                            {SceneCompositionEntities::Hunter,SceneCompositionSlots::EnemyMain}

                    }
            },
            {
                    R"("As far as we could tell the beast lives deep in the heart of the forest and ranges outside every once in a while." He looks at your weapons. "The way I see it, going there is just feeding the beast.")",
                    EnvironmentType::HunterCamp,
                    {
                            {
                                    "Do you know what the beast actually is?",
                                    false,
                                    StatNames::FIGHT,
                                    0,
                                    {},{},3,255,
                                    {},{},{{RequirementFlags::hasQuestOnStage,1010}},true

                            }}
                    ,
                    {
                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                            {SceneCompositionEntities::Hunter,SceneCompositionSlots::EnemyMain}

                    }
            },
            {
                    R"("I have guesses, but nothing concrete." He turns towards the forest. "The way I reckon its either something foreign that crept in, something unnatural. The claw-marks make little sense otherwise.")",
                    EnvironmentType::HunterCamp,
                    {
                            {
                                    "I see.",
                                    false,
                                    StatNames::FIGHT,
                                    0,
                                    {},{},4,255,
                                    {},{},{{RequirementFlags::hasQuestOnStage,1010}},true

                            }}
                    ,
                    {
                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                            {SceneCompositionEntities::Hunter,SceneCompositionSlots::EnemyMain}

                    }
            }
            ,
            {
                    R"("You are free to look for whatever clues we missed." He shrugs "Doubt it will help though. The way I see it the lord should send an actual force to deal with it.
Good luck.")",
                    EnvironmentType::HunterCamp,
                    {
                            {
                                    "I see.",
                                    false,
                                    StatNames::FIGHT,
                                    0,
                                    {{ExecuteFlags::AdvanceQuestStage,1020}},{},255,255,
                                    {},{},{},false

                            }}
                    ,
                    {
                            {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                            {SceneCompositionEntities::Hunter,SceneCompositionSlots::EnemyMain}

                    }
            }

    },DialoguePhase::Scene // Starting dialogue phase
        };
inline Encounter RavineMain
        {
    EncounterID::RavineMain,
    EncounterTypeID::Unique,
    {
            {
                "A ravine - try not to fall",
                EnvironmentType::Ravine,
                {
                        {
                            "Journey onwards",
                            false,
                            StatNames::FIGHT,
                            0,
                            {},{},255,255

                        }
                }
            }
            //TODO Combat with skeleton -> alternatice relic

        }

                ,DialoguePhase::Scene // Starting dialogue phase

        };

inline Encounter ForestHeartFinal
        {
    EncounterID::ForestHeartFinal,
    EncounterTypeID::FinalZone,
    {
        //Approach
            {
                "You approach the heart of the forest. You know instinctively - a battle awaits. Are you acually ready?",
                EnvironmentType::HeartApproach,
                {//Start Werewolf fight?  //TODO FIGHT
                        {
                                "Not yet.",
                                false,
                                StatNames::FAITH,
                                0,
                                {},
                                {},
                                255,
                                255
                        }//NOPE
                }
            }

    }
                ,DialoguePhase::Scene // Starting dialogue phase


        };