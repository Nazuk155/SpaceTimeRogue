//
// Created by Prince of Brass on 24.02.2025.
//
#pragma once
#include "../global.hpp"
#include <SDL_mixer.h>

inline Mix_Music * musicGroove = nullptr;
inline Mix_Music * musicGameOver = nullptr;
inline Mix_Music * musicLongShift = nullptr;
inline Mix_Music * musicSlowStart = nullptr;

inline Mix_Chunk * effectGravity = nullptr;
inline Mix_Chunk * effectGlassRinging = nullptr;
inline Mix_Chunk * effectPlayerBark = nullptr;
inline Mix_Chunk * effectPlayerWalk = nullptr;
inline Mix_Chunk * effectPackageOpen = nullptr;
inline Mix_Chunk * effectTurtleJump = nullptr;


//Music
inline String GroovePath = BasePath "/src/example/game/Ressources/sound/bgm/Groove_Intro.mp3";
inline String GameOverPath = BasePath "/src/example/game/Ressources/sound/bgm/Lost_in_Transit_OST-Game_Over.wav";
inline String LongShiftPath = BasePath "/src/example/game/Ressources/sound/bgm/Lost_in_Transit_OST-Long_Shift.wav";
inline String SlowStartPath = BasePath "/src/example/game/Ressources/sound/bgm/Lost_in_Transit-Slow_Start.mp3";

//Effects
inline String effectGravityPath = BasePath "/src/example/game/Ressources/sound/effects/Ability Usage - Gravity.mp3";
inline String effectGlassRingingPath = BasePath "/src/example/game/Ressources/sound/effects/Glass_Ringing_Sound.mp3";
inline String effectPlayerBarkPath = BasePath "/src/example/game/Ressources/sound/effects/Player_Speak.mp3";
inline String effectPlayerWalkPath =  BasePath "/src/example/game/Ressources/sound/effects/Walk.mp3";
inline String effectPackageOpenPath =  BasePath "/src/example/game/Ressources/sound/effects/Package_Open.mp3";
inline String effectTurtleJumpPath =  BasePath "/src/example/game/Ressources/sound/effects/Turtle_Jump.mp3";

enum class bgm{

    Groove,
    GameOver,
    LongShift,
    SlowStart,
    NONE

};
enum class Effect{

    Gravity,
    GlassRinging,
    BarkPlayer,
    Walk


};

class MusicManager
{
    Mix_Music * currentSong=musicGameOver;
    Mix_Chunk * currentChunk = effectGravity;
    bgm currentBGM = bgm::GameOver;
    Effect currentEffect = Effect::GlassRinging;



    bool bIsInitialized  =false;
public:
    int volume = 5;
    void changeMusic(bgm toPlay);
    void changeEffect(Effect toPlay);
    void playEffect(Effect toPlay);
    void init();


};