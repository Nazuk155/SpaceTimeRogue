#pragma once

#include "../global.hpp"

#include <sor/sdl_game.hpp>
#include <sor/sdl_shapeops.hpp>
#include <map>
//#include <autocast_ptr.h>
//#include <sor/tiles.h>


#include "grid.h"
#include "AnimationManager.h"
#include "playerCharacter.h"

namespace JanSordid::SDL_Example {
    using namespace JanSordid;
    using namespace JanSordid::SDL;
    //SDL_Point windowPoint = {480,270};

    class MyGame;

    class MyGameState;

    class IntroState;

    class PlasmaState;

    class SortState;

    class CameraState;

    class ShooterState;

    class STR_State;

    // MyGameState-Index
    // Why not in the classes themselves? For reusability!
    enum class MyGS : u8 {
        Intro = 0,
        Plasma,
        Ball,
        Parallax,
        Shooter,
        // "Invalid" is a special value, do NOT reproduce in your own game
        // its only purpose is to show how hard it would be to crash the game
        Invalid,
    };


    // abstract
    class MyGameState : public SDL::GameState<MyGame> {
        using Base = GameState;

    public:
        // ctor
        using Base::Base;
    };

    class MyGame final : public SDL::Game<MyGameState, MyGS> {
        using Base = Game;

    public:
        MyGame();

        bool HandleEvent(const Event &event) override;
    };


    class IntroState final : public MyGameState {
        using Base = MyGameState;

    protected:
        Owned<Font> _font = nullptr;
        Owned<Texture> _image = nullptr;
        Owned<Music> _music = nullptr;
        Owned<Chunk> _sound = nullptr;
        Owned<Texture> _blendedText = nullptr;

        Point _blendedTextSize = {0, 0};
        u8 _textmode = 0;

        // Testvars controlled by ImGui
        Point _p = {20, 30};
        int _colorIndex = 9;
        bool _isDarkOutline = true;

        static constexpr const Color white{255, 255, 255, SDL_ALPHA_OPAQUE};
        static constexpr const Color black{0, 0, 0, SDL_ALPHA_OPAQUE};

    public:
        /// Ctors & Dtor
        using Base::Base;

        /// Getters & Setters: non-virtual first, followed by (pure) virtual/override
        [[nodiscard]] constexpr Color clearColor() const noexcept override {
            return Color{255, 255, 255, SDL_ALPHA_OPAQUE};
        }

        /// Methods: non-virtual first, followed by (pure) virtual/override
        void Init() override;

        void Enter(bool isStacking) override;

        void Exit(bool isStackedUpon) override;

        void Destroy() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;

        ImGuiOnly(
                void RenderUI(u64 framesSinceStart, u64 msSinceStart, f32 deltaTNeeded) override;)
    };

    class PlasmaState final : public MyGameState {
        using Base = MyGameState;

    protected:
        Font *font = nullptr;
        Texture *blendedText = nullptr;
        Point blendedTextSize = {0, 0};
        Surface *plasmaSrf;
        Texture *plasmaTex;

        int brightness = 160;

        static constexpr const int Scale = 8;

    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Destroy() override;

        bool Input() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;
    };

    class SortState final : public MyGameState {
        using Base = MyGameState;

    protected:
        struct Ball {
            f32 x, y, z, w;
        };

        Texture *image = nullptr;
        Vector<Ball> balls;
        bool isOrdered = false;
        bool isTransparent = false;
        bool isDarkened = false;

    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Destroy() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;
    };

    class CameraState : public MyGameState {
        using Base = MyGameState;

    protected:
        Texture *bg[4] = {nullptr};
        Point bgSize[4]; // Is initialized in Init()
        const FPoint bgStart[4] = {
                {0, -330},
                {-350, -330},
                {-450, -900},
                {-800, -1500},
        };
        const FPoint bgFactor[4] = {
                {0.2f, 0.3f},
                {0.4f, 0.45f},
                {0.8f, 0.8f},
                {1.2f, 1.2f},
        };
        bool bgIsVisible[4] = {
                true,
                true,
                true,
                true,
        };
        FPoint mouseOffset = {0, 0};
        FPoint mouseOffsetEased = {0, 0};

        bool isInverted = false;
        bool isEased = true;
        bool isFlux = true;
        FPoint dir = {0, 0};
        FPoint cam = {0, 0};

    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Destroy() override;

        bool Input() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;

        FPoint CalcFluxCam(const u64 totalMSec) const;

        void RenderLayer(const Point windowSize, const FPoint camPos, const int index) const;
    };

    class ShooterState final : public CameraState {
        using Base = CameraState;

    protected:
        f32 progress = 0;
        u32 shootCooldown = 0;

        Chunk *sound = nullptr;
        Texture *projectile[4] = {nullptr};
        //ReuseFPoints rvProjectiles;

        Vector<FPoint> enemyProjectiles;
        Vector<FPoint>::iterator enemyProjReuse;
        int numDeadEnemyProj = 0;

        Vector<FPoint> myProjectiles;
        Vector<FPoint>::iterator myProjReuse;
        int numDeadMyProj = 0;

        Vector<FRect> enemies = {
                {1100, 280, 160, 160},
                {1200, 500, 80,  80},
                {1100, 680, 80,  80},
        };

        FRect player = {200, 530, 200, 100};
        FPoint sat[5] = {{0, 0}};
        int satCount = 5;

        FPoint spawnProjectileAt;           // Valid if x and y is >= 0
        u32 spawnProjectileSoundCD = 0;  //

        static constexpr const int satRadius = 25;

    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Destroy() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;

        //bool isFPSLimited() const noexcept override { return false; }

        [[nodiscard]]
        bool IsProjectileAlive(const Vector<FPoint>::iterator &it) const;

        void SpawnEnemyProjectile(const FPoint pos);

        void SpawnMyProjectile(const FPoint pos);

        void RetireProjectile(const Vector<FPoint>::iterator &it);

        void RetireMyProjectile(const Vector<FPoint>::iterator &it);
    };

    class STR_State final : public MyGameState {
        using Base = MyGameState;

    protected:
        Owned<Font> _font = nullptr;
        Owned<Texture> _image = nullptr;
        Owned<Music> _music = nullptr;
        Owned<Chunk> _sound = nullptr;
        Owned<Texture> _blendedText = nullptr;

        Point blendedTextSize = {0, 0};
        Point _blendedTextSize = {0, 0};
        u8 _textmode = 0;

        // Testvars controlled by ImGui
        Point _p = {20, 30};
        int _colorIndex = 9;
        bool _isDarkOutline = true;

        const Color outlineColor = _isDarkOutline
                                   ? Color{0, 0, 0, SDL_ALPHA_OPAQUE}
                                   : Color{255, 255, 255, SDL_ALPHA_OPAQUE};
        static constexpr const Color white{255, 255, 255, SDL_ALPHA_OPAQUE};
        static constexpr const Color black{0, 0, 0, SDL_ALPHA_OPAQUE};
        int brightness = 160;
        static constexpr const int Scale = 8;

        ///own stuff
        Texture * playerIdleSheet;
        Texture * playerIdleSheetFlip;
        Texture * playerWalkSheet;
        Texture * playerWalkSheetFlip;

        Texture * playerDamageSheet;
        Texture * playerDamageSheetFlip;
        Texture * playerDamageKnockdownSheet;
        Texture * playerDamageKnockdownSheetFlip;
        Texture * playerGetUpSheet;
        Texture * playerGetUpSheetFlip;


        Texture * playerAnimation = nullptr;


        bool showGrid = true;
        //animation clipper for 32x32 sprites
        Vector<SDL_Rect> clips32;
        u64 animationFrame = 0;
        u64 startAnim = 0;
        u64 phase = 0;
        bool loopAnimation = true;
        bool playerSwitchedState = false;
        PlayerState nextState = PlayerState::Idle;
        //testing
        int count = 0;
       // SDL_Rect playerRect;



        //text size for all text for now
        int fontsize = 18;
       // PlayerState state = PlayerState::Idle;
        bool knockdown = false;

        Vector<AnimationTarget> tar = {};
        AnimationManager aManager = tar;
        Rect target;

        int scale = 32;

    public:
        /// Ctors & Dtor
        using Base::Base;

        Grid grid;
        SDL_Point gridStartingPoint = {0,0};

        playerCharacter pChar;

        /// Getters & Setters: non-virtual first, followed by (pure) virtual/override
        [[nodiscard]] constexpr Color clearColor() const noexcept override {
            return Color{255, 255, 255, SDL_ALPHA_OPAQUE};
        }

        /// Methods: non-virtual first, followed by (pure) virtual/override
        void Init() override;

        void Enter(bool isStacking) override;

        void Exit(bool isStackedUpon) override;

        void Destroy() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;





        void renderFromSpritesheet(Rect values,
                                   SDL_Texture* t,
                                   SDL_Rect* clip = nullptr,
                                   double angle = 0.0,
                                   SDL_Point* center = nullptr,
                                   SDL_RendererFlip flip = SDL_FLIP_NONE,
                                   bool useClipSize = false);

        Texture *loadFromFile(const std::string &path);

        Texture *textToTexture(const char *text);

        void renderText(Rect values, SDL_Texture *t);

        void renderText(Rect values, SDL_Texture *t, int colorIndex);

        u64 RenderPlayerAnimation(Rect target, SDL_Texture *t, Vector<SDL_Rect> clips);

        void SwitchPlayerAnimation(PlayerState sheet);

        void RenderPlayer();

        void AnimateTargets();

        SDL_Texture *GetAnimation(EntityType type, EntityAnimations animation);

        SDL_Texture *GetAnimation(AnimationTarget &a);

        void ZoomOut();

        void ZoomIn();

        void CameraMoveBy1Tile(Directions direction);
    };

}
