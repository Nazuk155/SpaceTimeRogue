//
// Created by Prince of Brass on 24.02.2025.
//
#pragma once
#include "../global.hpp"
#include <SDL_mixer.h>
#include <map>

#ifndef SDL_BASE_MUSIC_H
#define SDL_BASE_MUSIC_H
inline Mix_Music * mainMusic = nullptr;
inline Mix_Music * villageTheme = nullptr;
inline Mix_Music * forestTheme = nullptr;
inline Mix_Music * monasteryTheme = nullptr;

inline Mix_Music * darkWoodsCombat = nullptr;

//Music
inline String minBGMPath = BasePath "/src/example/game/Ressources/bgm/Zavlore-ATaleNeverTold-05ATaleNeverTold.mp3";
inline String forestBGMPath = BasePath "/src/example/game/Ressources/bgm/Woods_of_Vorduin-Serenade_of_the_Silent_Grove-03_Mistsele.mp3";
//inline String forestBGMPath = BasePath "/src/example/game/Ressources/bgm/Woods_of_Vorduin-Serenade_of_the_Silent_Grove-08_Gārsecg.mp3";
inline String BGM2Path = BasePath "/src/example/game/Ressources/bgm/Zavlore-A_Tale_Never_Told-08The_Song_of_Other_Skies.mp3";
inline String monasteryBGMPAth = BasePath "/src/example/game/Ressources/bgm/Schola_Gregoriana-Antiphona_et_Magnificat.ogg";


enum class bgm
{
    main_theme,
    village1,
    battle,
    forest_quiet,
    forest_haunted,
    monastery
};

class MusicManager
{
    Mix_Music * currentSong=mainMusic;
    bgm currentBGM=bgm::main_theme;
    bool bIsInitialized  =false;
public:
    void changeMusic(bgm toPlay);
    void init();


};




#endif //SDL_BASE_MUSIC_H
