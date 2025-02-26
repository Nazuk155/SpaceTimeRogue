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
    {"Chapter I","Find out what is hunting humans.",1,
          {{0,"Talk to the Villagers."},
           {10,"Reach the Hunters' Camp"},
           {20,"Look for clues around the forest"},
           {100,"Complete"}
          },
          0},
    {"Test-Start New Quest", "Added through an option",6,
            {{0,"The start"},{70,"The Middle"},{100,"Complete"}},0},
    {"The Monastery of St. Lykon", "An old and respected Dominican monastery",3,
            {{0,"You are known to the Monks of the convent."},{10,"The Middle"},{100,"Complete"}},0},
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
