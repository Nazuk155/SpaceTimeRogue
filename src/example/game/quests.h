//
// Created by Prince of Brass on 24.02.2025.
//
#pragma once
#include "../global.hpp"
#ifndef SDL_BASE_QUESTS_H
#define SDL_BASE_QUESTS_H


struct Quest
{
    String questName;
    String description;
    int questID;

    std::vector<std::pair<int, String>> questStages;

    int currentQuestStage;
};

inline std::vector<Quest> availableQuests
{
    {"The Hunt","Track down and kill the beast.",1,
          {{0,"Talk to the Villagers."},
           {10,"Reach the Hunters' Camp"},
           {20,"Look for clues around the forest."},
                  {30,"You found a first clue."},
                  {40,"You found a second clue. Someone will have to hear of this."},
                  {50,"Speak to the monks about the devilry afoot."},
                  {60,"Find the hermit."},
                  {80,"Produce the relic."},
                  {82,"You were rebuked. Return to the Hermit."},
                  {83,"It seems you will have to rob a grave. Go to the ravine."},
                  {84,""},
                  {85,"You have what you need. The veteran should be able to make the bullet."},
                  {90, "You have your bullet. It is time."},
           {100,"Complete"}
          },
          0},

    {"Test-Start New Quest", "Added through an option",6,
            {{0,"The start"},{70,"The Middle"},{100,"Complete"}},0},


    {"The Monastery of St. Lykon", "An old and respected Dominican monastery",3,
            {{0,"You are known to the Monks of the convent."},
             {10,"The Middle"},
             {100,"Complete"}},0},
    {"The Skull","A skull was used for something unnatural.",9,
     {
             {0,"You picked up a skull inscribed with a glowing sigil. You feel fingertips at the surface of your mind."},
             {5,"Your faith protects you from the cursed skull you carry."},
             {10,"You bound the skull to your will. You can draw a drop of infernal strength from it."},
             {100,"The skull is now with the monastery, may it rest in peace."}
     },0},

    {"The Corpses","You found a pile of savaged corpses.",11,
     {
             {0,"The corpses were torn apart by what appears to be a massive animal. But a bear has smaller claws, and few animals revel in such bloody displays."},
     },0},


    {"Faith, Steel and Gunpowder","The only way to fight the darkness?", 4,
            {

                    {0,"Talk to the old veteran in the village about a gun."},
                    {5,"Talk to the old veteran in the village about bullets for your gun."},
                    {15,"You own a gun. Try not to run out of ammunition."},
                    {10,"Talk to the old veteran in the village about some additional lead bullets [get 5 bullets (once)]"}

            }},
};


class QuestLog
{
public:
    std::vector<Quest> activeQuests;

    bool addQuest(int questId)
    {
        //TODO chack if already in
        for(const Quest& q : activeQuests)
        {
            if (q.questID == questId)
            {
                return false;
            }
        }
        for(const Quest& q : availableQuests)
        {
            if(q.questID == questId)
            {
                activeQuests.push_back(q);
                fmt::println("Added quest: {}",q.questName);
                return true;
            }
        }
        fmt::println("Failed to add quest");
        return false;

    }
    bool bHasQuest(int questId)
    {  bool bHas = false;
        for(Quest q : activeQuests)
        {
            if (q.questID == questId)
                bHas = true;
        }
        return bHas;
    }
    //Returns stage of a quest, if active else -1
    int getQuestStage(int questId)
    {

        int stage = -1;
        for(Quest q : activeQuests)
        {
            if (q.questID == questId)
                stage=q.currentQuestStage;
        }
        return stage;
    }

    bool setStage(int questId, int nextStage)
    {
        for(Quest q : activeQuests)
        {
            if (q.questID == questId)
            {
                for(const std::pair<int, String>& stage: q.questStages)
                {
                    if(stage.first == nextStage)
                    {
                        q.currentQuestStage=nextStage;
                        return true;
                    }

                }

            }
        }
        return false;
    }

};




#endif //SDL_BASE_QUESTS_H
