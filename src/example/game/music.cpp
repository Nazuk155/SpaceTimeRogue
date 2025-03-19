//
// Created by Prince of Brass on 24.02.2025.
//
#include "music.h"


void MusicManager::init()
{
    bool bDone = true;
    musicGroove = Mix_LoadMUS(GroovePath.c_str());
    musicGameOver = Mix_LoadMUS(GameOverPath.c_str());
    musicLongShift = Mix_LoadMUS(LongShiftPath.c_str());
    musicSlowStart = Mix_LoadMUS(SlowStartPath.c_str());

    effectGravity = Mix_LoadWAV(effectGravityPath.c_str());
    effectGlassRinging = Mix_LoadWAV(effectGlassRingingPath.c_str());
    effectPlayerBark = Mix_LoadWAV(effectPlayerBarkPath.c_str());
    effectPlayerWalk = Mix_LoadWAV(effectPlayerWalkPath.c_str());
    effectPackageOpen = Mix_LoadWAV(effectPackageOpenPath.c_str());
    effectTurtleJump = Mix_LoadWAV(effectTurtleJumpPath.c_str());



    Mix_Volume(-1,1); //TODO seems broken?
    if( musicGroove == nullptr )
    {
        printf( "Failed to load groove! SDL_mixer Error: %s\n", Mix_GetError() );
        bDone = false;
    }

    bIsInitialized=bDone;
    currentBGM= bgm::GameOver;
    Mix_VolumeMusic(10);
    Mix_VolumeChunk(effectPlayerBark,MIX_MAX_VOLUME);
    Mix_VolumeChunk(effectTurtleJump,MIX_MAX_VOLUME);
    Mix_VolumeChunk(effectGravity,MIX_MAX_VOLUME);
    Mix_VolumeChunk(effectGlassRinging,MIX_MAX_VOLUME);
    Mix_VolumeChunk(effectPackageOpen,MIX_MAX_VOLUME);
    Mix_VolumeChunk(effectPlayerWalk,MIX_MAX_VOLUME);

    Mix_PlayMusic(musicGameOver, -1 );


}

void MusicManager::changeMusic(bgm toPlay)
{

    if(currentBGM != toPlay && bIsInitialized)
    {
        switch (toPlay) {

            case bgm::Groove:
                Mix_PlayMusic( musicGroove, -1 );
                currentBGM = toPlay;
                break;
            case bgm::GameOver:
                Mix_PlayMusic( musicGameOver, -1 );
                currentBGM = toPlay;
                break;
            case bgm::LongShift:
                Mix_PlayMusic( musicLongShift, -1 );
                currentBGM = toPlay;
                break;
            case bgm::SlowStart:
                Mix_PlayMusic( musicSlowStart, -1 );
                currentBGM = toPlay;
                break;
            case bgm::NONE:
                Mix_HaltMusic();
                currentBGM = toPlay;
                break;

            default:Mix_PlayMusic( musicGroove, -1 );
                currentBGM = bgm::Groove;
                break;


        }

        fmt::println("changed music track");
    }

}

void MusicManager::changeEffect(Effect toPlay) {
    using enum Effect;
    currentEffect = toPlay;

}

