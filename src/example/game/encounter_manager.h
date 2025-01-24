#pragma once
#include "../global.hpp"
#include "encounter.h"
#include "skillCheckEngine.h"
#include "item_manager.h"


// EncounterManager class
class EncounterManager {
public:

    ItemManager* iManager;
   // SDL_Point SzeneOptionStatus;

    // Add a new encounter
    void addEncounter(EncounterID id, const Encounter& encounter) {
        if (encounter.validate()) {
            encounters[id] = encounter;
        } else {
            throw std::runtime_error("Invalid encounter: Scenes must have at least one option.");
        }
    }

    // Get an encounter by ID
    const Encounter* getEncounter(EncounterID id) const {
        auto it = encounters.find(id);
        if (it != encounters.end()) {
            return &it->second;
        }
        return nullptr;
    }

    // Remove an encounter by ID
    void removeEncounter(EncounterID id) {
        encounters.erase(id);
    }

    // Check if an encounter exists
    bool hasEncounter(EncounterID id) const {
        return encounters.find(id) != encounters.end();
    }

    bool isSelectedOptionSkillcheck(EncounterID eID,int szene,int input){

        if(getEncounter(eID)->scenes[szene].options[input - 1].isSkillCheck)
        {
            return true;
        }
        else{
            return false;
        }
    }

/*
    bool ResolveEncounter(Encounter &encounter,int szene,int input,SkillChallengeEngine ske, Character & currentCharacter) {
        switch (encounter.currentDialoguePhase) {
            case DialoguePhase::Scene:
                input = input - 1;

                //new idea








                if (!encounter.scenes[szene].options[input - 1].isSkillCheck) {
                    //if Jump Target is escape value TODO define further behavior, construct Combat encounter encoding and Jump
                    if (encounter.scenes[szene].options[input - 1].jumpTargetSuccess ==
                        255) {
                        return true;
                    } else {
                        szene = encounter.scenes[szene].options[input - 1].jumpTargetSuccess;
                    }
                } else {


                    //ske.bIsActive=true; todo put flag in other place
                    ske.setDifficulty(
                            encounter.scenes[szene].options[input - 1].difficulty);
                    ske.setModifier(0);
                    ske.setSkill(encounter.scenes[szene].options[input - 1].skill);


                    if (ske.checkSkill()) {//Skillcheck Passed
                        iterateOverOutcomes(encounter.scenes[szene].options[input].rewardItemIDs,
                                encounter.scenes[szene].options[input].successOutcomes,currentCharacter);
                        szene = encounter.scenes[szene].options[input].jumpTargetSuccess;
                        //bNeedInput = false;

                    } else {
                        //Not Passed TODO
                        if (currentCharacter.GetFatePoints() > 0) { // can spend will

                        } else {
                            //  bNeedInput = false;
                            iterateOverOutcomes(
                                    encounter.scenes[szene].options[input].failureOutcomes);
                            szene = encounter.scenes[szene].options[input].jumpTargetFail;
                        }


                    }
                    encounter.currentDialoguePhase = DialoguePhase::DieRoll;
                }


                input = -1;

                break;
            case DialoguePhase::DieRoll: // misnomer
                //???
                if (bNeedInput) {
                    //if any WP avalkable
                    switch (CurrentInput) {
                        case 1: // todo move to reroll phase?
                            character1->SpendFate();
                            dialoguePhase = DialoguePhase::FateReroll;
                            bNeedInput = false;
                            if (ske.addFateDice()) //todo seems broken
                            {
                                //Passed after Fateroll
                                iterateOverOutcomes(
                                        CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].SuccessOutcomes);
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetSuccess;
                            } else {
                                fmt::println("Debug fate fail!");
                                iterateOverOutcomes(
                                        CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].FailureOutcomes);
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetFail;
                            }

                            break;
                        case 2:
                            //Choose to fail/not roll
                            iterateOverOutcomes(
                                    CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput - 1].FailureOutcomes);
                            CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetFail;

                            dialoguePhase = DialoguePhase::Scene;
                            break;
                        default:;


                    }
                    CurrentInput = -1;

                } else {
                    dialoguePhase = DialoguePhase::Scene;
                    bNeedInput = true;
                }


                break;
            case DialoguePhase::FateReroll:


                dialoguePhase = DialoguePhase::Scene;
                CurrentInput = -1;
                bNeedInput = true;
                break;
        }
    }
*/


void iterateOverOutcomes(const Vector<ItemName>& rewards, const std::vector<std::tuple<ExecuteFlags, int8_t>> &outcomes, Character &currentCharacter) const {
    for (std::tuple<ExecuteFlags, int8_t> outcome: outcomes) {

        switch (get<0>(outcome)) {
            case ExecuteFlags::Wound:

                fmt::print("Debug- Injury");
                currentCharacter.AdjustHealth(-get<1>(outcome));
                break;
            case ExecuteFlags::GainItem:
                for(auto e : rewards) {
                    currentCharacter.AddToInventory(iManager->GetItem(e));
                }
                //TODO Ressources
                break;
            case ExecuteFlags::Heal:
                currentCharacter.AdjustHealth(get<1>(outcome));
                break;
            case ExecuteFlags::SanityLoss:
                currentCharacter.AdjustSanity(-get<1>(outcome)); //todo fix this mess/warning
                break;
            case ExecuteFlags::RegainSan:
                currentCharacter.AdjustSanity(get<1>(outcome));
                break;

        }
    }
}



private:
    std::unordered_map<EncounterID, Encounter> encounters;
};