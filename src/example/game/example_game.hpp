#pragma once

#include "../global.hpp"

#include <sor/sdl_game.hpp>
#include <sor/sdl_shapeops.hpp>
#include <map>
//#include <autocast_ptr.h>
//#include <sor/tiles.h>
#include "blueprint_manager.h"
#include "map.h"
#include "ability_manager.h"
#include "item_manager.h"
#include "location_manager.h"
#include "character.h"
#include "encounter.h"
#include "skillCheckEngine.h"
#include "encounter_manager.h"
#include "monster_manager.h"

#include "inventory_components.h"
#include "music.h"

namespace JanSordid::SDL_Example {
    using namespace JanSordid;
    using namespace JanSordid::SDL;

    class MyGame;

    class MyGameState;

    class IntroState;

    class PlasmaState;

    class SortState;

    class CameraState;

    class ShooterState;

    class BeasthoodState;

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

    class BeasthoodState final : public MyGameState {
        using Base = MyGameState;

    protected:
        //tracks the current game phase between input,update and render
        GamePhases Phase = GamePhases::UPKEEP;
        int DisasterCounter = 0;

        Point windowSize;
        int fontsize = 18;


        //generate one manager object per relevant class
        ItemManager itemManager;
        Map map;
        EncounterManager encounterManager;
        AbilityManager abilityManager;
        BlueprintManager blueprintManager;
        LocationManager locationManager;
        MonsterManager monsterManager;
        MusicManager musicManager;

        Character *character1;
        bool itemInUse = false;
        ItemID activeItem = ItemID::NONE;

        InventoryScreen inventoryScreen;
        bool bInInventory = false;
        bool bInJournal = false;
        bool bShowRightItemInfo = false;
        bool bShowLeftItemInfo = false;

        //Healtbar components
        Texture * healtbarBG = nullptr;
        Texture * healtbarRed = nullptr;
        Texture * healthbarEdge = nullptr;
        //TODO TEMP REMOVE
        float tempHealth = 1.0;


        //   std::vector<Location> locations;
        Font *font = nullptr;
        Owned<Font> _font = nullptr;
        int mouseOverX = 0;  //TODO move elsewhere, Fix Redundancy
        int mouseOverY = 0;
        Owned<Texture> _blendedText = nullptr;
        Texture *blendedText = nullptr;
        Texture *forestLocationIconTexture = nullptr;
        Texture *playerMapIconTexture = nullptr;
        Texture *playerMainSpite = nullptr;

        //Interface
        Texture *endTurnButtonOn = nullptr;
        Texture *endTurnButtonOff = nullptr;
        Texture *endTurnButtonMouseover = nullptr;

        Texture *bagIconOn = nullptr;
        Texture *bagIconMouseover = nullptr;
        Texture *bagIconOff = nullptr;

        Texture * journalIcon = nullptr;
        Texture * journalIconMouseover = nullptr;
        Texture * journalIconOff = nullptr;

        Texture *emptyInventoryItem = nullptr;

        Texture *dice1 = nullptr;
        Texture *dice2 = nullptr;
        Texture *dice3 = nullptr;
        Texture *dice4 = nullptr;
        Texture *dice5 = nullptr;
        Texture *dice6 = nullptr;

        //inventory icons

        Texture * emptyItem = nullptr;
        Texture * missingIcon = nullptr;
        Texture * candleIcon = nullptr;
        Texture * prayerbookIcon = nullptr;

        Texture * torchIcon = nullptr;

        Texture *ritualSkullIcon = nullptr;

        Texture * halberdIcon = nullptr;

        Texture * relicIcon = nullptr;
        Texture * shortSwordIcon = nullptr;
        Texture * honoriusIcon = nullptr;

        Texture * gunIcon = nullptr;
        Texture * bulletSilver = nullptr;
        Texture * bulletLead = nullptr;
        Texture * gunSilverIcon = nullptr;
        Texture * gunLeadIcon = nullptr;


        std::vector<Texture*> Icons;

        //NPCs
        Texture *monk1Sprite = nullptr;
        Texture * abbotSprite = nullptr;

        Texture* anthonySprite = nullptr;
        Texture* peasant1Sprite = nullptr;
        Texture* peasant1CoupleSprite = nullptr;
        Texture* peasant2Sprite = nullptr;
        Texture* hunterSprite = nullptr;
        Texture* peasantWomanSprite = nullptr;
        Texture *mercenarySprite= nullptr;
        Texture * veteranSprite = nullptr;
        Texture * priestSprite = nullptr;


        Texture *enemyWereWolfMainSprite = nullptr;
        Texture *enemyWolfSprite = nullptr;
        Texture* enemyBearSprite=nullptr;
        Texture* enemySkeletonSpearSprite = nullptr;



        Texture *errorIMG = nullptr;

        //environments
        Texture *denseForestBG = nullptr;
        Texture *denseForestFG = nullptr;
        Texture* monasteryPathBG = nullptr;
        Texture *monasteryApproachBG = nullptr;
        Texture *monasteryGateBG= nullptr;
        Texture *monasteryInteriorBG= nullptr;
        Texture* village1 = nullptr;
        Texture * village2 = nullptr;

        Texture* outskirtsPath= nullptr;
        Texture* windmillOutskirts= nullptr;
        Texture* oakPath= nullptr;
        Texture* hunterCamp = nullptr;

        Texture* forestLakeBG= nullptr;
        Texture *forestHermitLodge = nullptr;
        Texture* forestClearingBG= nullptr;
        Texture* forestPathToHeartBG= nullptr;
        Texture* forestPathToHeartFG= nullptr;
        Texture* forestHeartBG= nullptr;
        Texture * ravineBG = nullptr;
        Texture * sheep_treeBG = nullptr;
        Texture * churchBG = nullptr;


        //Overlay Items
        Texture* OverlayForestClearingSkull = nullptr;
        Texture * CorpsePileOverlay = nullptr;






        struct LocationTextures {
            SDL_Texture *iconTexture = nullptr;
            SDL_Texture *nameTexture = nullptr;
        };

        //easy lookup for location rendering on map
        std::unordered_map<LocationID, LocationTextures> locationTextureMap;

        std::unordered_map<MonsterID,SDL_Texture*> monsterIDtoTextureMap;
       // std::unordered_map<MonsterID,SDL_Texture*> monsterIDtoIconMap;

        //skillengine
        SkillChallengeEngine ske;
        Character *currentCharacter;

        //movement phase related variables
        LocationID moveTarget = LocationID::UNASSIGNED;
        bool playerMoved = false;
        bool endMovementConfirmation = false;
        u8 movementPoints = 0;

        //flag that is set when a encounter is specifically combat
        bool currentEncounterIsOnlyCombat = false;

        //encounter Phase related variables

        struct EncounterTracker{
           Encounter *activeEncounter = nullptr;
            int szene = 0;
            bool inputIsViable = false;
            bool chooseFateReroll = false;
            int fateRerollChoice = -1;
            EncounterID encounterID;
            int selectedOption = -1;
            DialoguePhase diaPhase = DialoguePhase::Scene;
            bool alreadyDisplayedText = false;
            int lastSzeneTextDisplayed = 0;
            bool bShowPreviousDicerolls=false;
            Vector<MonsterID> monsterIDs = {};
            Vector<ExecuteFlags> exFlag = {};
            int szeneWin,szeneLoss;

            void Reset(){
                activeEncounter = nullptr;
                szene = 0;
                chooseFateReroll = false;
                fateRerollChoice = -1;
                encounterID = EncounterID::NO_ENCOUNTER_ASSIGNED;
                selectedOption = -1;
                diaPhase = DialoguePhase::Scene;
                alreadyDisplayedText = false;
                bShowPreviousDicerolls = false;
                monsterIDs.clear();
                szeneWin = 0;
                szeneLoss = 0;
                exFlag.clear();
            }
        };
        EncounterTracker eTracker;
        EncounterTracker eTrackerSaver;

        bool awaitingInput = false;


        //sets up the combat encounters values when triggered
        struct CombatTracker{
            LocationID location = LocationID::UNASSIGNED;
            LocationID alreadyDodged = LocationID::UNASSIGNED;
            MonsterID monID = MonsterID::UNASSIGNED_MONSTERID;
            int hpVisual = 0; /// USE THIS FOR THE HP BAR
            /// logical hp gets calculated after FATE REROLL, Visual HP does not.
            /// Example: We reduce a 4 toughness monster to 2 HP by having 2 successes. -> not dead -> spend FATE?
            /// ske keeps the successes we rolled so it sees 2 success > 2hp which kills the monster without going to 0 hp
            int hp = 0; //logical hp for calculations. DO NOT USE FOR HPBAR
            int awareness = 0; // monsterManager.getMonsterByID(locationManager.GetItem(currentCharacter->GetCurrentLocationID())->monsters_or_npcs.back())->awareness etc.
            int toughness = 0;
            int horrorDamage = 0;
            int combatDamage = 0;
            int horrorRating = 0;
            int combatRating = 0;

            int monstersInFight;
            bool encounterTriggeredThis = false;

            Vector<Monster> monsters;
            void updateCurrentMonster(){
                if(!monsters.empty()) {
                    monID = monsters.back().id;
                    hpVisual = monsters.back().hp;
                    hp = monsters.back().hp;
                    awareness = monsters.back().awareness;
                    toughness = monsters.back().toughness;
                    horrorDamage = monsters.back().horrorDamage;
                    combatDamage = monsters.back().combatDamage;
                    horrorRating = monsters.back().horrorRating;
                    combatRating = monsters.back().combatRating;
                }else{
                     monID = MonsterID::UNASSIGNED_MONSTERID;
                     hpVisual = 0;
                     hp = 0;
                     awareness = 0;
                     toughness = 0;
                     horrorDamage = 0;
                     combatDamage = 0;
                     horrorRating = 0;
                     combatRating = 0;
                }

            }
            void RemoveMonster(MonsterID id) {
                auto it = std::find_if(monsters.begin(), monsters.end(),
                                       [id](const Monster &m) { return m.id == id; });
                if (it != monsters.end()) {
                    monsters.erase(it);  // Only removes the first matching monster
                }
            }
            void Reset(){
                location = LocationID::UNASSIGNED;
                hpVisual = 0;
                hp = 0;
                awareness = 0;
                toughness = 0;
                horrorDamage = 0;
                combatDamage = 0;
                horrorRating = 0;
                combatRating = 0;
                monID = MonsterID::UNASSIGNED_MONSTERID;
                alreadyDodged = LocationID::UNASSIGNED;
                monsters.clear();

            }
        };
        CombatTracker cTracker;



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

    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Destroy() override;

        bool Input() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;

        //added functions for our game

        void CleanupMonsterTextures();


        void PopulateBlueprints();

        void renderFromSpritesheet(int targetX,
                                   int targetY,
                                   int targetW,
                                   int targetH,
                                   SDL_Texture *t,
                                   const SDL_Rect *clip = nullptr,
                                   double angle = 0.0,
                                   SDL_Point *center = nullptr,
                                   SDL_RendererFlip flip = SDL_FLIP_NONE,
                                   bool useClipSize = false
        );

        void renderFromSpritesheet(Rect values,
                                   SDL_Texture *t,
                                   SDL_Rect *clip = nullptr,
                                   double angle = 0.0,
                                   SDL_Point *center = nullptr,
                                   SDL_RendererFlip flip = SDL_FLIP_NONE,
                                   bool useClipSize = false);

        //helper for SDL_CreateTextureFromSurface. Also applys a color key:(r:0, g:0xFF,b:0xFF) if transparent pixels are ever needed
        Texture *loadFromFile(const std::string &path);

        Texture *textToTexture(const char *text);

        void renderText(Rect values, SDL_Texture *t);

        bool IsMouseInsideRect(const SDL_Rect &rect, int mouseX, int mouseY);


        void renderDicerollAnimation(SkillChallengeEngine &ske);

        void renderFateDieAnimation(const SkillChallengeEngine &ske);

        static std::string StatToString(StatNames stat);

        void PopulateEventManager();

        void PopulateLocationEvents();

        void renderText(Rect values, SDL_Texture *tn, int colorIndex);

        void RenderSceneComposition(const std::vector<std::tuple<SceneCompositionEntities, SceneCompositionSlots>>& compositionVector, EnvironmentType environment);

        void PopulateMonsterManager();

        void UpdateCombatEncounter();
        //void RenderSceneComposition(const std::vector<std::tuple<SceneCompositionEntities, SceneCompositionSlots>>& compositionVector);

        void RenderSidebar();

        void RenderTurnButton(bool bIsActive);

        void RenderInventory();

        void RenderInventorySelection(int mouseX, int mouseY, int screenWidth, int screenHeight);

        void RenderInventorySelectionNoOption(int mouseX, int mouseY, int screenWidth, int screenHeight,bool left_item);

        bool bOptionRequirementMet(std::tuple<RequirementFlags, int> requirement);

        void RenderJournal();

        SceneCompositionEntities MatchMonsterIDtoSceneComp(MonsterID target);

        void ResolveItemUsage(ItemID id);

        void MoveMonsters();

        LocationID FindNextStep(LocationID start, LocationID goal);

        void SpawnMonster(LocationID location, MonsterID monster);

        void DespawnMonster(LocationID location, MonsterID monster);

        void MoveMonster(LocationID origin,LocationID destination, Monster monster);

        void RenderHealthbar(float currentHealth);

        void AddEncounter(LocationID lID, EncounterID eID);

        void RemoveEncounter(LocationID lID, EncounterID eID);
    };

}
