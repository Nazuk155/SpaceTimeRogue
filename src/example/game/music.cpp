//
// Created by Prince of Brass on 24.02.2025.
//
#include "music.h"


void MusicManager::init()
{
    bool bDone = true;
    mainMusic = Mix_LoadMUS(minBGMPath.c_str());
    villageTheme= Mix_LoadMUS(BGM2Path.c_str());
    forestTheme= Mix_LoadMUS(forestBGMPath.c_str());
    monasteryTheme= Mix_LoadMUS(monasteryBGMPAth.c_str());
    darkWoodsCombat=Mix_LoadMUS(elsewhereBattlePAth.c_str());
    Mix_Volume(-1,1); //TODO seems broken?
    if( mainMusic == nullptr )
    {
        printf( "Failed to load main music! SDL_mixer Error: %s\n", Mix_GetError() );
        bDone = false;
    }
    if( villageTheme == nullptr )
    {
        printf( "Failed to load village 1 music! SDL_mixer Error: %s\n", Mix_GetError() );
        bDone = false;
    }
    if( forestTheme == nullptr )
    {
        printf( "Failed to load forest music! SDL_mixer Error: %s\n", Mix_GetError() );
        bDone = false;
    }
    if( monasteryTheme == nullptr )
    {
        printf( "Failed to load monastery music! SDL_mixer Error: %s\n", Mix_GetError() );
        bDone = false;
    }
    if( darkWoodsCombat == nullptr )
    {
        printf( "Failed to load monastery music! SDL_mixer Error: %s\n", Mix_GetError() );
        bDone = false;
    }
    bIsInitialized=bDone;
    currentBGM= bgm::main_theme;
    Mix_VolumeMusic(5);
    Mix_PlayMusic(mainMusic, -1 );


}
void MusicManager::changeMusic(bgm toPlay)
{

    if(currentBGM != toPlay && bIsInitialized)
    {
        switch (toPlay) {
            case bgm::village1:Mix_PlayMusic( villageTheme, -1 );
                currentBGM = toPlay;
                break;
            case bgm::main_theme:Mix_PlayMusic( mainMusic, -1 );
                currentBGM = toPlay;
                break;
            case bgm::forest_quiet:
                Mix_PlayMusic(forestTheme,-1);
                currentBGM=toPlay;
                break;
            case bgm::monastery:
                Mix_PlayMusic(monasteryTheme,-1);
                currentBGM=toPlay;
                break;
            case bgm::battle:
                Mix_PlayMusic(darkWoodsCombat,-1);
                currentBGM=toPlay;
                break;
            default:Mix_PlayMusic( mainMusic, -1 );
                currentBGM = bgm::main_theme;
                break;


        }

        fmt::println("changed music track");
    }

}


