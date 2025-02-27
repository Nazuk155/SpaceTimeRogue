//
// Created by max on 15.01.25.
//
#include "example_game.hpp"
#include <hsnr64/offset.hpp>
#include "../global.hpp"
#include "map.h"

#include <hsnr64/palette.hpp>
#include <iostream>
#include <map>
#include "ability_manager.h"
#include "ability_ReduceStaminaLoss.h"
#include "ability_DrawExtraItem.h"
#include "item_manager.h"
#include "item.h"
#include "character.h"
//#include "encounter.h"
#include "skillCheckEngine.h"
#include "layout.h"



//TODO HP/Sanity 0 conditions in Encounter einbauen sowie Monster mit HP und inkrementalen verletzungen anstatt toughness überbieten or bust
//TODO monster spawn und bewegung per Disaster Phase regeln.
namespace JanSordid::SDL_Example {
    struct {

        InventoryIcon Left {false,SidebarLayout.EquippedItemsStart.x,
                            SidebarLayout.InventoryStart.y,
                            SidebarLayout.InventoryItemScale.x,
                            SidebarLayout.InventoryItemScale.y};

        InventoryIcon Right {false,SidebarLayout.EquippedItemsStart.x+SidebarLayout.InventoryScale.x-SidebarLayout.InventoryItemScale.x,
                             SidebarLayout.InventoryStart.y,
                             SidebarLayout.InventoryItemScale.x,
                             SidebarLayout.InventoryItemScale.y};

    }SidebarIcons; //todo move somewhere


    QuestLog Questlog;
    void BeasthoodState::Init() {
        using std::string;

        Base::Init();

        if (!_font) {
            //_font = TTF_OpenFont(BasePath "asset/font/RobotoSlab-Bold.ttf", (int) (12.0f * _game.scalingFactor()));
            //_font = TTF_OpenFont(BasePath "/src/example/game/Ressources/fonts/KJV1611.otf", (int) (12.0f * _game.scalingFactor()));
            _font = TTF_OpenFont(BasePath "/src/example/game/Ressources/fonts/IMFeENrm29P.ttf", (int) (15.0f * _game.scalingFactor()));

            TTF_SetFontHinting(_font, TTF_HINTING_LIGHT);
            if (!_font)
                print(stderr, "TTF_OpenFont failed: {}\n", TTF_GetError());
        }

        //Set up Intro Quest(s)
        Questlog.addQuest(1);


        //Paths for Image Assets
        string forestLocationIconPath = BasePath "/src/example/game/Ressources/Image_assets/token_1.png";
        string playerMapIconPath = BasePath "/src/example/game/Ressources/Image_assets/Landsknecht.jpg";

        string playerMainSpritePath = BasePath "/src/example/game/Ressources/Image_assets/lk_sprite.png";

        //Map icon
        string monasteryLocationIconPath = BasePath "/src/example/game/Ressources/Image_assets/map_icons/monastery_icon.png";
        //Healthbar
        string healtbarBGPath = BasePath "/src/example/game/Ressources/Image_assets/healthbar/healthbar_bg.png";
        string healthbarRedPath = BasePath "/src/example/game/Ressources/Image_assets/healthbar/healthbar_red.png";
        string healthbarEdgePath = BasePath "/src/example/game/Ressources/Image_assets/healthbar/healthbar_edge.png";


        //NPCs
        string enemyWereWolfMainSpritePath = BasePath "/src/example/game/Ressources/Image_assets/entities/garou_sprite.png";
        string enemyWolfSpritePath = BasePath "/src/example/game/Ressources/Image_assets/entities/wolf_sprite.png";
        string enemyBearSpritePath = BasePath "/src/example/game/Ressources/Image_assets/entities/bear_sprite.png";
        string errorIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/ERROR.png";
        string monk1IMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/monk_1_sprite.png";
        string abbotIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/monk_2_sprite.png";

        string anthonySpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/anthony_sprite.png";
        string peasant1SpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/peasant_1_sprite.png";
        string peasant1CoupleSpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/peasants_market_sprite.png";
        string peasant2SpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/peasant_2_sprite.png";
        string hunterSpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/hunter_sprite.png";
        string peasantWomanSpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/woman_1_sprite.png";
        string mercenarySpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/mercenary_sprite.png";
        string enemySkeletonSpearSpriteIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/skeleton_spear_sprite.png";


        //Backgrounds/Foregrounds
        string denseForestBGPath = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/dense_forest_test.png";
        string denseForestFGPath = BasePath "/src/example/game/Ressources/Image_assets/foregrounds/dense_forest_test_fg.png";
        string monasteryPathBGPAth = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/monasteryPath.png";
        string monasteryApproachBGPath = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/monastery_approach.png";
        string monasteryGateBGPath= BasePath "/src/example/game/Ressources/Image_assets/backgrounds/monastery_gate.png";
        string monasteryInteriorBGPath = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/monastery_interior.png";

        string village1PathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/village_1.png";

        string village2PathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/village_2.png";

        string sheepTreePathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/sheep_tree.png";

        string outskirtsPathPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/outskirts_path.png";
        string windmillOutskirtsPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/windmill_outskirts.png";
        string oakPathPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/oak_path.png";
        string hunterCampPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/hunter_camp.png";

        string forestLakeBGPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/forest_lake.png";
        string forestHermitLodgePathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/forest_lodge_shishkin.png";
        string forestClearingBGPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/forest_clearing.png";
        string forestPathToHeartBGPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/heart_approach_bg.png";
        string forestPathToHeartPathFG = BasePath "/src/example/game/Ressources/Image_assets/foregrounds/heart_approach_fg.png";
        string forestHeartBGPathBG = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/forest_heart.png";
        string ravinePathBG= BasePath "/src/example/game/Ressources/Image_assets/backgrounds/ravine_bg.png";

        //Overlay Items

        string OverlayForestClearingSkullPath = BasePath "/src/example/game/Ressources/Image_assets/foregrounds/forest_clearing_overlay_skull.png";

        //Buttons

        string endTurnButtonOnPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/clock_button_PLACEHOLDER.png";
        string endTurnButtonOffPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/clock_disabled_PLACEHOLDER.png";
        string endTurnButtonMouseoverPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/clock_mouseover_PLACEHOLDER.png";
        string emptyInventoryItemPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/icon_empty.png";

        string bagIconOnPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/bag_icon_base.png";
        string bagIconOffPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/bag_icon_off.png";
        string bagIconMouseoverPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/bag_icon_mouseover.png";

        string journalIconOnPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/journal_icon_base.png";
        string journalIconOffPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/journal_icon_off.png";
        string journalIconMouseoverPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/journal_icon_mouseover.png";




        string dice1Path = BasePath "/src/example/game/Ressources/Image_assets/dice/Dice_1.png";
        string dice2Path = BasePath "/src/example/game/Ressources/Image_assets/dice/Dice_2.png";
        string dice3Path = BasePath "/src/example/game/Ressources/Image_assets/dice/Dice_3.png";
        string dice4Path = BasePath "/src/example/game/Ressources/Image_assets/dice/Dice_4.png";
        string dice5Path = BasePath "/src/example/game/Ressources/Image_assets/dice/Dice_5.png";
        string dice6Path = BasePath "/src/example/game/Ressources/Image_assets/dice/Dice_6.png";

        // item icon paths
        String emptyItemPath = BasePath "/src/example/game/Ressources/Image_assets/items/empty_icon.png";
        String missingItemPath = BasePath "/src/example/game/Ressources/Image_assets/items/missing_icon.png";
        String halberdIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/halberd_icon.png";
        String candleIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/candle_icon.png";
        String prayerbookIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/prayerbook_icon.png";
        String torchIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/torch_icon.png";
        String gunIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/gun_icon.png";
        String gunSilverIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/gun_silver_icon.png";
        String gunLeadIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/gun_lead_icon.png";
        String ritualSkullIconPath = BasePath "/src/example/game/Ressources/Image_assets/items/ritual_skull_icon.png";
        String bulletLeadPath = BasePath "/src/example/game/Ressources/Image_assets/items/bullet_lead.png";
        String bulletSilverPath = BasePath "/src/example/game/Ressources/Image_assets/items/bullet_silver.png";






        //--------------- load textures from file
        forestLocationIconTexture = loadFromFile(forestLocationIconPath);
        playerMapIconTexture = loadFromFile(playerMapIconPath);
        playerMainSpite = loadFromFile(playerMainSpritePath);
        denseForestBG = loadFromFile(denseForestBGPath);
        denseForestFG = loadFromFile(denseForestFGPath);
        monasteryPathBG = loadFromFile(monasteryPathBGPAth);
        monasteryApproachBG= loadFromFile(monasteryApproachBGPath);
        monasteryGateBG= loadFromFile(monasteryGateBGPath);
        monasteryInteriorBG= loadFromFile(monasteryInteriorBGPath);

        village1 = loadFromFile(village1PathBG);
        village2 = loadFromFile(village2PathBG);
        sheep_treeBG= loadFromFile(sheepTreePathBG);

        outskirtsPath= loadFromFile(outskirtsPathPathBG);
        windmillOutskirts= loadFromFile(windmillOutskirtsPathBG);
        oakPath= loadFromFile(oakPathPathBG);
        hunterCamp = loadFromFile(hunterCampPathBG);

        forestLakeBG= loadFromFile(forestLakeBGPathBG);
        forestHermitLodge = loadFromFile(forestHermitLodgePathBG);
        forestClearingBG= loadFromFile(forestClearingBGPathBG);
        forestPathToHeartBG= loadFromFile(forestPathToHeartBGPathBG);
        forestPathToHeartFG= loadFromFile(forestPathToHeartPathFG);
        forestHeartBG= loadFromFile(forestHeartBGPathBG);
        ravineBG = loadFromFile(ravinePathBG);

        //Overlay Items
        OverlayForestClearingSkull = loadFromFile(OverlayForestClearingSkullPath);

        //NPCs

        //this maps the scene sprite to the MonsterID
        monsterIDtoTextureMap[MonsterID::Wolf] = loadFromFile(enemyWolfSpritePath);
        monsterIDtoTextureMap[MonsterID::Werewolf] = loadFromFile(enemyWereWolfMainSpritePath);
        monsterIDtoTextureMap[MonsterID::Bear] = loadFromFile(enemyBearSpritePath);

        //map MonsterID to corresponding MAP ICON texture
        // monsterIDtoIconMap[MonsterID::Wolf] = loadFromFile(enemyWolfIconPath);

        //old version

        enemyWereWolfMainSprite = loadFromFile(enemyWereWolfMainSpritePath);
        enemyWolfSprite = loadFromFile(enemyWolfSpritePath);
        enemyBearSprite= loadFromFile(enemyBearSpritePath);
        enemySkeletonSpearSprite = loadFromFile(enemySkeletonSpearSpriteIMGPath);


        errorIMG = loadFromFile(errorIMGPath);
        monk1Sprite = loadFromFile(monk1IMGPath);
        abbotSprite= loadFromFile(abbotIMGPath);
        anthonySprite = loadFromFile(anthonySpriteIMGPath);
        peasant1Sprite = loadFromFile(peasant1SpriteIMGPath);
        peasant1CoupleSprite = loadFromFile(peasant1CoupleSpriteIMGPath);
        peasant2Sprite = loadFromFile(peasant2SpriteIMGPath);
        hunterSprite = loadFromFile(hunterSpriteIMGPath);
        peasantWomanSprite = loadFromFile(peasantWomanSpriteIMGPath);
        mercenarySprite= loadFromFile(mercenarySpriteIMGPath);

        //Buttons
        endTurnButtonOn = loadFromFile(endTurnButtonOnPath);
        endTurnButtonOff = loadFromFile(endTurnButtonOffPath);
        endTurnButtonMouseover = loadFromFile(endTurnButtonMouseoverPath);
        emptyInventoryItem = loadFromFile(emptyInventoryItemPath);

        bagIconOn = loadFromFile(bagIconOnPath);
        bagIconMouseover = loadFromFile(bagIconMouseoverPath);
        bagIconOff = loadFromFile(bagIconOffPath);

        journalIcon = loadFromFile(journalIconOnPath);
        journalIconMouseover = loadFromFile(journalIconMouseoverPath);
        journalIconOff = loadFromFile(journalIconOffPath);

        //Healthbar
        healtbarBG = loadFromFile(healtbarBGPath);
        healtbarRed = loadFromFile(healthbarRedPath);
        healthbarEdge = loadFromFile(healthbarEdgePath);


        //DIce Textures
        dice1 = loadFromFile(dice1Path);
        dice2 = loadFromFile(dice2Path);
        dice3 = loadFromFile(dice3Path);
        dice4 = loadFromFile(dice4Path);
        dice5 = loadFromFile(dice5Path);
        dice6 = loadFromFile(dice6Path);


        //items
        emptyItem=loadFromFile(emptyItemPath);
        halberdIcon =loadFromFile(halberdIconPath);
        missingIcon= loadFromFile(missingItemPath);
        candleIcon = loadFromFile(candleIconPath);
        prayerbookIcon = loadFromFile(prayerbookIconPath);
        gunIcon= loadFromFile(gunIconPath);
        gunLeadIcon= loadFromFile(gunLeadIconPath);
        gunSilverIcon = loadFromFile(gunSilverIconPath);
        torchIcon= loadFromFile(torchIconPath);
        ritualSkullIcon = loadFromFile(ritualSkullIconPath);

        bulletLead= loadFromFile(bulletLeadPath);
        bulletSilver= loadFromFile(bulletSilverPath);


        //Icons index!!!
        Icons.push_back(missingIcon); //Missing = 0
        Icons.push_back(halberdIcon); // Halberd=1
        Icons.push_back(prayerbookIcon);//Prayerbook=2
        Icons.push_back(candleIcon);//Candle=3
        Icons.push_back(torchIcon); //Torch = 4
        Icons.push_back(gunIcon);//Gun = 5
        Icons.push_back(ritualSkullIcon);//Skull=6
        Icons.push_back(bulletLead);//Lead = 7
        Icons.push_back(bulletSilver); //Silver = 8
        Icons.push_back(gunLeadIcon); //Lead loaded gun = 9
        Icons.push_back(gunSilverIcon); //Silver loaded gun = 10





        //struct
        struct LocationTextures {
            SDL_Texture *iconTexture = nullptr;
            SDL_Texture *nameTexture = nullptr;
        };

        //fill the location <-> texture map with image and name textures
        locationTextureMap[LocationID::Forest].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Forest].nameTexture = textToTexture("Forest");

        locationTextureMap[LocationID::Church].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Church].nameTexture = textToTexture("Church");

        locationTextureMap[LocationID::River].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::River].nameTexture = textToTexture("River");

        locationTextureMap[LocationID::Smith].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Smith].nameTexture = textToTexture("Smith");

        locationTextureMap[LocationID::Windmill].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Windmill].nameTexture = textToTexture("Windmill");

        locationTextureMap[LocationID::Crossroads].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Crossroads].nameTexture = textToTexture("Crossroads");

        locationTextureMap[LocationID::Cave].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Cave].nameTexture = textToTexture("Cave");

        locationTextureMap[LocationID::Monastery].iconTexture = loadFromFile(monasteryLocationIconPath);
        locationTextureMap[LocationID::Monastery].nameTexture = textToTexture("Monastery");

        locationTextureMap[LocationID::Farm].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Farm].nameTexture = textToTexture("Farm");

        locationTextureMap[LocationID::Clearing].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Clearing].nameTexture = textToTexture("Clearing");

        locationTextureMap[LocationID::Townhall].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Townhall].nameTexture = textToTexture("Townhall");

        locationTextureMap[LocationID::Thicket].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::Thicket].nameTexture = textToTexture("Thicket");

        locationTextureMap[LocationID::UNASSIGNED].iconTexture = loadFromFile(forestLocationIconPath);
        locationTextureMap[LocationID::UNASSIGNED].nameTexture = textToTexture("UNASSIGNED");


        font = TTF_OpenFont(BasePath "asset/font/MonkeyIsland-1991-refined.ttf", _game.scalingFactor() * 16);
        TTF_SetFontHinting(font, TTF_HINTING_NONE);

        //todo moved windowsize, check for consequences
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);

        const Point resolution = windowSize / Scale;

        /*
        forestNameTexture = textToTexture("Forest");
        churchNameTexture = textToTexture("Church");
        riverNameTexture = textToTexture("River");
        smithNameTexture = textToTexture("Smith");
        windmillNameTexture = textToTexture("Windmill");
        crossroadsNameTexture = textToTexture("Crossroads");
        caveNameTexture = textToTexture("Cave");
        monasteryNameTexture = textToTexture("Monastery");
        farmNameTexture = textToTexture("Farm");
        clearingNameTexture = textToTexture("Clearing");
        townhallNameTexture = textToTexture("Townhall");
        thicketNameTexture = textToTexture("Thicket");
        unassignedNameTexture = textToTexture("UNASSIGNED");
        */

        /*
            Map map;
            // Add 5 slots with arbitrary positions
            map.AddSlot(1,{100, 100});
            map.AddSlot(2,{200, 200});
            map.AddSlot(3,{300, 300});
            map.AddSlot(4,{400, 400});
            map.AddSlot(5,{500, 500});

            Location forest("Forest",1);

            // Print out the IDs and positions of all slots
            for (int i = 1; i <= 5; ++i) {
                Map_Slot* slot = map.GetSlotByID(i);
                if (slot) {
                    std::cout << "Slot ID: " << slot->id << ", Position: ("
                              << slot->position.x << ", " << slot->position.y << ")\n";
                    std::cout.flush();
                }
            }


            Map map;

            // Add 5 slots
            for (int i = 1; i <= 5; ++i) {
                map.AddSlot(i,{i * 100, i * 100});
            }

            // Define locations
            Location church( "Church",1);
            Location inn("Inn",2);

            // Assign locations to map slots
            map.SetLocation(1, church);
            map.SetLocation(2, inn);

            // Print results
            for (int i = 1; i <= 5; ++i) {
                Map_Slot* slot = map.GetSlotByID(i);
                if (slot) {
                    std::cout << "Map_Slot ID: " << slot->id
                              << ", Location ID: " << slot->location_id << "\n";
                    std::cout.flush();
                }
            }

            // Verify Location's map slot pointer
            if (church.GetMapSlot()) {
                std::cout << "Church is in Map_Slot ID: "
                          << church.GetMapSlot()->id << "\n";
                std::cout.flush();
            }

            if (inn.GetMapSlot()) {
                std::cout << "Inn is in Map_Slot ID: "
                          << inn.GetMapSlot()->id << "\n";
                std::cout.flush();
            }

        */

        /// testing everything here for now
        // Add 12 Map_Slots
        map.AddSlot(0, {500, 50});
        for (int i = 1; i <= 5; ++i) {
            map.AddSlot(i, {i * 140, 200});
        }
        map.AddSlot(6, {700, 500});
        for (int i = 7; i <= 11; ++i) {
            map.AddSlot(i, {(i - 6) * 140, 700});
        }

        // Add connections


        map.ConnectSlots(0, 1);
        map.ConnectSlots(0, 2);
        map.ConnectSlots(0, 3);
        map.ConnectSlots(0, 4);
        map.ConnectSlots(0, 5);

        map.ConnectSlots(5, 6);

        map.ConnectSlots(6, 7);
        map.ConnectSlots(6, 8);
        map.ConnectSlots(6, 9);
        map.ConnectSlots(6, 10);
        map.ConnectSlots(6, 11);

        // Create and assign locations

        /*
                 auto forest =  std::make_unique<Location>("Forest",LocationID::Forest);
                 auto church =  std::make_unique<Location>("Church",LocationID::Church);
                 auto River =  std::make_unique<Location>("River",LocationID::River);
                 auto Smith =  std::make_unique<Location>("Smith",LocationID::Smith);
             auto Windmill =  std::make_unique<Location>("Windmill",LocationID::Windmill);
             auto Crossroads =  std::make_unique<Location>("Crossroads",LocationID::Crossroads);
             auto Cave =  std::make_unique<Location>("Cave",LocationID::Cave);
             auto Monastery =  std::make_unique<Location>("Monastery",LocationID::Monastery);
             auto Farm =  std::make_unique<Location>("Farm",LocationID::Farm);
             auto Clearing =  std::make_unique<Location>("Clearing",LocationID::Clearing);
             auto Townhall =  std::make_unique<Location>("Townhall",LocationID::Townhall);
             auto Thicket =  std::make_unique<Location>("Thicket",LocationID::Thicket);


             locationManager.AddItem(std::move(forest));
             locationManager.AddItem(std::move(church));
             */

        // locations.emplace_back( "Location " + std::to_string(i),i);
        //map.SetLocation(i, locations.back());
        for (int i = 0; i <= 11; ++i) {
            locationManager.AddItem(std::move(std::make_unique<Location>(static_cast<LocationID>(i))));
            map.SetLocation(i, *locationManager.GetItem(static_cast<LocationID>(i)));
        }

        // Verify connections and location setup
        for (int i = 0; i <= 11; ++i) {
            Map_Slot *slot = map.GetSlotByID(i);
            if (slot) {
                std::cout << "Map_Slot ID: " << slot->id << ", Connections: ";
                std::cout.flush();

                for (std::pair<int, bool> connected_id: slot->connections) {
                    std::cout << connected_id.first << " ";
                    std::cout.flush();

                }
                std::cout << "\n";

                map.SetConnectionStatus(2, 0, false);

                // Location* loc = &locations[i - 1];
                std::cout << "  Location: " << locationManager.GetItem(static_cast<LocationID>(i))->name
                          << ", Active Connections: ";
                std::cout.flush();


                if (locationManager.GetItem(static_cast<LocationID>(i))->GetMapSlot()) {
                    for (int connected_id: locationManager.GetItem(
                            static_cast<LocationID>(i))->GetActiveConnections()) {
                        std::cout << connected_id << " ";
                        std::cout.flush();

                    }
                }
                std::cout << "\n";
                std::cout.flush();

            }
        }



        // Add abilities
        abilityManager.AddAbility(std::make_unique<ReduceStaminaLossAbility>());
        abilityManager.AddAbility(std::make_unique<DrawExtraItemAbility>());

        // Use abilities
        Ability *reduceStaminaLoss = abilityManager.GetAbility(AbilityID::ReduceStaminaLoss);
        if (reduceStaminaLoss) {
            reduceStaminaLoss->Activate();
        }

        Ability *drawExtraItem = abilityManager.GetAbility(AbilityID::DrawExtraItem);
        if (drawExtraItem) {
            drawExtraItem->Activate();
        }




        // Create and add an ability
        auto staminaAbility = std::make_unique<ReduceStaminaLossAbility>();
        Ability *staminaAbilityPtr = staminaAbility.get();
        abilityManager.AddAbility(std::move(staminaAbility));

        // Create and add items
        auto sword = std::make_unique<Item>(ItemID::Halberd, ItemType::Melee, "Halberd of Valor", 2);
        sword->SetStats({0, 0, 5, 0, 0, 0});
        sword->SetAbility(staminaAbilityPtr); // Associate ability with item
        itemManager.AddItem(std::move(sword));

        auto torch = std::make_unique<Item>(ItemID::Torch, ItemType::Unique,"Not so Common Torch",1);
        torch->SetStats({0, 0, 1, 1, 0, 5});
        itemManager.AddItem(std::move(torch));

        auto gun = std::make_unique<Item>(ItemID::GUN, ItemType::Unique,"Unloaded Gun",1);
        gun->SetStats({0, 0, 1, 0, 0, 0}); // Attack 1
        itemManager.AddItem(std::move(gun));

        auto gunLoadedSilver = std::make_unique<Item>(ItemID::LoadedGunSilver, ItemType::Unique,"Gun - Silver Bullet",1);
        gunLoadedSilver->SetStats({0, 0, 1, 2, 3, 3}); // Attack 1
        itemManager.AddItem(std::move(gunLoadedSilver));

        auto gunLoadedLead = std::make_unique<Item>(ItemID::LoadedGunLead, ItemType::Unique,"Gun - Lead Bullet",1);
        gunLoadedLead->SetStats({0, 0, 1, 1, 0, 0}); // Attack 1
        itemManager.AddItem(std::move(gunLoadedLead));



        auto prayerBook = std::make_unique<Item>(ItemID::PrayerBook, ItemType::Unique,"Prayer Book of St. Lycon",1);
        prayerBook->SetStats({0, 0, 1, 2, 2, 6});
        itemManager.AddItem(std::move(prayerBook));

        auto talisman = std::make_unique<Item>(ItemID::Talisman, ItemType::Unique,"Lead-Sigil of Pan",1);
        talisman->SetStats({2, 5, 2, 0, 2, 0});
        itemManager.AddItem(std::move(talisman));

        auto ritual_skull = std::make_unique<Item>(ItemID::RitualSkull, ItemType::Unique,"Ritual Skull",0);
        ritual_skull->SetStats({0, 0, 0, 0, 1, -2});
        itemManager.AddItem(std::move(ritual_skull));

        auto bullet_silver = std::make_unique<Item>(ItemID::BulletSilver,ItemType::Magic,"Silver Bullet",0);
        bullet_silver->isBullet = true;
        bullet_silver->SetStats({0, 0, 0, 0, 2, 2});
        itemManager.AddItem(std::move(bullet_silver));
        auto bullet_lead = std::make_unique<Item>(ItemID::BulletLead,ItemType::Ranged,"Lead Bullet",0);
        bullet_lead->isBullet = true;
        bullet_lead->SetStats({0, 0, 0, 0, 0, 0});
        itemManager.AddItem(std::move(bullet_lead));

        // Access and use an item
        Item *item = itemManager.GetItem(ItemID::Halberd);
        if (item) {
            std::cout << "Item: " << item->GetName() << ", Attack: " << item->GetStats().GetStat(FIGHT) << "\n";
            if (item->GetAbility()) {
                item->GetAbility()->Activate(); // Activate associated ability
            }
        }

        std::cout << "\n";
        std::cout.flush();


        PopulateBlueprints();

        auto landsknechtBlueprint = blueprintManager.GetBlueprintByName("Landsknecht");
        Character Landsknecht(*landsknechtBlueprint);
        std::cout << "Item: " << Landsknecht.GetInventory().back()->GetName();
        std::cout << "\n";
        std::cout.flush();
        Landsknecht.EquipItem(Landsknecht.GetInventory().back());
        Landsknecht.UpdateCurrentStats();
        std::cout << "Stats: " << Landsknecht.GetCurrentStats().GetStat(FIGHT);
        std::cout.flush();

        character1 = new Character(*landsknechtBlueprint);

        character1->RefillFatePoints();
        currentCharacter = character1;

        currentCharacter->AddToInventory(itemManager.GetItem(ItemID::Torch));
        currentCharacter->AddToInventory(itemManager.GetItem(ItemID::PrayerBook));
        currentCharacter->AddToInventory(itemManager.GetItem(ItemID::Talisman));
        currentCharacter->AddToInventory(itemManager.GetItem(ItemID::BulletSilver));
        currentCharacter->AddToInventory(itemManager.GetItem(ItemID::BulletLead));
        currentCharacter->AddToInventory(itemManager.GetItem(ItemID::GUN));

        inventoryScreen = InventoryScreen(currentCharacter);

        // get character into SKE
        ske.changeCharacter(currentCharacter);
        fmt::println("Fate available: {}",
                     character1->GetFatePoints()); //todo 0 fate dialogue makes no sense, prints options that should not be printed
        std::cout.flush();

        currentCharacter->SetCurrentLocation(LocationID::Forest);
        //currentCharacter->EquipItem(currentCharacter->GetInventory().back());
        currentCharacter->UpdateCurrentStats();

        encounterManager.iManager=&itemManager;//Was missing ctd by add item outcome

        PopulateMonsterManager();
        PopulateEventManager();
        PopulateLocationEvents();



        locationManager.GetItem(LocationID::Forest)->AddMonster(monsterManager.GetMonster(MonsterID::Wolf));
       // locationManager.GetItem(LocationID::Forest)->AddMonster(monsterManager.GetMonster(MonsterID::Wolf));
       // locationManager.GetItem(LocationID::Forest)->AddMonster(monsterManager.GetMonster(MonsterID::Bear));

        //locationManager.GetItem(LocationID::Forest)->monsters_or_npcs.push_back(MonsterID::Wolf);
        //locationManager.GetItem(LocationID::Forest)->monsters_or_npcs.push_back(MonsterID::Wolf);

        //Load Music system

        musicManager.init();




    }

    void BeasthoodState::Destroy() {

        CleanupMonsterTextures();
        SDL_DestroyTexture(forestLocationIconTexture);
        SDL_DestroyTexture(playerMapIconTexture);
        SDL_DestroyTexture(playerMainSpite);
        SDL_DestroyTexture(denseForestBG);
        SDL_DestroyTexture(denseForestFG);
        SDL_DestroyTexture(monasteryPathBG);
        SDL_DestroyTexture(monasteryApproachBG);
        SDL_DestroyTexture(monasteryGateBG);
        SDL_DestroyTexture(monasteryInteriorBG);
        SDL_DestroyTexture(village1);

        SDL_DestroyTexture(village2);
        SDL_DestroyTexture(sheep_treeBG);
        SDL_DestroyTexture(outskirtsPath);
        SDL_DestroyTexture(windmillOutskirts);
        SDL_DestroyTexture(oakPath);
        SDL_DestroyTexture(hunterCamp);
        SDL_DestroyTexture(forestLakeBG);
        SDL_DestroyTexture(forestHermitLodge);
        SDL_DestroyTexture(forestClearingBG);
        SDL_DestroyTexture(forestPathToHeartBG);
        SDL_DestroyTexture(forestPathToHeartFG);
        SDL_DestroyTexture(forestHeartBG);
        SDL_DestroyTexture(ravineBG);

        SDL_DestroyTexture(OverlayForestClearingSkull);



        SDL_DestroyTexture(errorIMG);

        SDL_DestroyTexture(endTurnButtonOff);
        SDL_DestroyTexture(endTurnButtonOn);
        SDL_DestroyTexture(endTurnButtonMouseover);

        SDL_DestroyTexture(emptyInventoryItem);
        SDL_DestroyTexture(bagIconOn);
        SDL_DestroyTexture(bagIconMouseover);
        SDL_DestroyTexture(bagIconOff);

        SDL_DestroyTexture(journalIcon);
        SDL_DestroyTexture(journalIconMouseover);
        SDL_DestroyTexture(journalIconOff);

        SDL_DestroyTexture(healtbarBG);
        SDL_DestroyTexture(healtbarRed);
        SDL_DestroyTexture(healthbarEdge);



        SDL_DestroyTexture(dice1);
        SDL_DestroyTexture(dice2);
        SDL_DestroyTexture(dice3);
        SDL_DestroyTexture(dice4);
        SDL_DestroyTexture(dice5);
        SDL_DestroyTexture(dice6);

        SDL_DestroyTexture(emptyItem);
        for(auto t:Icons)
        {
            SDL_DestroyTexture(t);
            t= nullptr;
        }

        //Enemies
        SDL_DestroyTexture(enemyWereWolfMainSprite);
        SDL_DestroyTexture(enemyWolfSprite);
        SDL_DestroyTexture(enemyBearSprite);
        SDL_DestroyTexture(enemySkeletonSpearSprite);
        //NPCS
        SDL_DestroyTexture(monk1Sprite);
        SDL_DestroyTexture(abbotSprite);
        SDL_DestroyTexture(anthonySprite);
        SDL_DestroyTexture(peasant1Sprite);
        SDL_DestroyTexture(peasant1CoupleSprite);
        SDL_DestroyTexture(peasant2Sprite);
        SDL_DestroyTexture(hunterSprite);
        SDL_DestroyTexture(peasantWomanSprite);
        SDL_DestroyTexture(mercenarySprite);



        for (auto e: locationTextureMap) {
            SDL_DestroyTexture(e.second.iconTexture);
            SDL_DestroyTexture(e.second.nameTexture);
        }

        forestLocationIconTexture = nullptr;
        playerMapIconTexture = nullptr;
        playerMainSpite = nullptr;
        denseForestBG = nullptr;
        denseForestFG = nullptr;
        monasteryPathBG = nullptr;
        monasteryApproachBG= nullptr;
        monasteryGateBG= nullptr;
        monasteryInteriorBG = nullptr;
        village1 = nullptr;
        village2 = nullptr;
        sheep_treeBG= nullptr;

        outskirtsPath= nullptr;
        windmillOutskirts= nullptr;
        oakPath= nullptr;
        hunterCamp = nullptr;

        forestLakeBG= nullptr;
        forestHermitLodge = nullptr;
        forestClearingBG= nullptr;
        forestPathToHeartBG= nullptr;
        forestPathToHeartFG= nullptr;
        forestHeartBG= nullptr;
        ravineBG= nullptr;

        OverlayForestClearingSkull = nullptr;

        enemyWereWolfMainSprite = nullptr;
        enemyWolfSprite = nullptr;
        enemyBearSprite= nullptr;
        enemySkeletonSpearSprite = nullptr;
        errorIMG = nullptr;

        healtbarBG = nullptr;
        healthbarEdge = nullptr;
        healtbarRed = nullptr;


        monk1Sprite = nullptr;
        abbotSprite= nullptr;
        anthonySprite = nullptr;
        peasant1Sprite = nullptr;
        peasant1CoupleSprite = nullptr;
        peasant2Sprite = nullptr;
        hunterSprite = nullptr;
        peasantWomanSprite = nullptr;
        mercenarySprite = nullptr;

        endTurnButtonOff = nullptr;
        endTurnButtonMouseover = nullptr;
        endTurnButtonOn = nullptr;

        bagIconOn = nullptr;
        bagIconOff = nullptr;
        bagIconMouseover = nullptr;

        journalIcon = nullptr;
        journalIconMouseover = nullptr;
        journalIconOff = nullptr;

        emptyInventoryItem = nullptr;
        dice1= nullptr;
        dice2 = nullptr;
        dice3 = nullptr;
        dice4 = nullptr;
        dice5 = nullptr;
        dice6 = nullptr;

        emptyItem= nullptr;


        Base::Destroy();
    }

    bool BeasthoodState::HandleEvent(const Event &event) {

        if (event.type == SDL_MOUSEMOTION ) {
            //int mouseX, mouseY;
            SDL_GetMouseState(&mouseOverX, &mouseOverY);
            if(bInInventory)
                inventoryScreen.currentPage.MouseOver(mouseOverX,mouseOverY);
            SDL_Rect equipIcon= //Equip R
                    {
                            static_cast<int>((SidebarIcons.Right.position.x * windowSize.x*0.01)),
                            static_cast<int>(SidebarIcons.Right.position.y*windowSize.y*0.01),
                            static_cast<int>(SidebarIcons.Right.position.w*windowSize.x*0.01),
                            static_cast<int>(SidebarIcons.Right.position.h*windowSize.x*0.01),

                    };

            if(IsMouseInsideRect(equipIcon,mouseOverX,mouseOverY) && currentCharacter->GetEquipment().second) //todo this approach is wrong.
            {
                fmt::println("Mouse over right equip {}", currentCharacter->GetEquipment().second->GetName());

                SidebarIcons.Right.referencedItem = currentCharacter->GetEquipment().second;
                inventoryScreen.currentPage.MouseOverIcon = &SidebarIcons.Right;
                bShowRightItemInfo = true;
                RenderInventorySelection(mouseOverX, mouseOverY,windowSize.x,windowSize.y);

            }
            else
            {

                bShowRightItemInfo = false;
            }
            equipIcon= //Equip L
                    {
                            static_cast<int>((SidebarIcons.Left.position.x * windowSize.x*0.01)),
                            static_cast<int>(SidebarIcons.Left.position.y*windowSize.y*0.01),
                            static_cast<int>(SidebarIcons.Left.position.w*windowSize.x*0.01),
                            static_cast<int>(SidebarIcons.Left.position.h*windowSize.x*0.01),

                    };

            if(IsMouseInsideRect(equipIcon,mouseOverX,mouseOverY) && currentCharacter->GetEquipment().first) //todo this approach is wrong.
            {
                fmt::println("Mouse over left equip {}", currentCharacter->GetEquipment().first->GetName());

                SidebarIcons.Left.referencedItem = currentCharacter->GetEquipment().first;
                inventoryScreen.currentPage.MouseOverIcon = &SidebarIcons.Left;
                bShowLeftItemInfo = true;
                RenderInventorySelection(mouseOverX, mouseOverY,windowSize.x,windowSize.y);

            }
            else
            {
                bShowLeftItemInfo = false;

            }
        }


        if(bInInventory) //todo expand functionality of inventory screen
        {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //int mouseX, mouseY;
                SDL_GetMouseState(&mouseOverX, &mouseOverY);

                    inventoryScreen.Click(mouseOverX,mouseOverY,windowSize.x,windowSize.y,&itemManager);
                    fmt::println("equip handled?");
                    //inventoryScreen.BuildInventory(); //CTD RIP

                    //Inventory Button
                    if(IsMouseInsideRect({static_cast<int>(SidebarLayout.InventoryIconStart.x*0.01*windowSize.x),
                                          static_cast<int>(SidebarLayout.InventoryIconStart.y*0.01*windowSize.y+SidebarLayout.InventoryItemScale.y*0.01*windowSize.x),
                                          static_cast<int>(SidebarLayout.InventoryIconScale.x*0.01*windowSize.x),
                                          static_cast<int>(SidebarLayout.InventoryIconScale.y*0.01*windowSize.x)},mouseOverX,mouseOverY))
                    {
                        bInInventory=false;
                    }

            }



            if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                        case SDLK_i:
                        bInInventory=!bInInventory;
                        break;
                        case SDLK_v:
                        fmt::println("VillageMusic");
                        musicManager.changeMusic(bgm::village1);

                        break;
                    case SDLK_f:
                        fmt::println("Forest_quiet Music");
                        musicManager.changeMusic(bgm::forest_quiet);

                        break;
                    case SDLK_c:
                        fmt::println("Monastery Music");
                        musicManager.changeMusic(bgm::monastery);

                        break;
                    case SDLK_m:
                        Mix_VolumeMusic(0);
                        break;
                    case SDLK_PLUS:



                        if(Mix_VolumeMusic(-1)< (MIX_MAX_VOLUME-2))
                        {
                            Mix_VolumeMusic(Mix_VolumeMusic(-1)+2);
                        }
                        else
                        {
                            fmt::println("The silence offends Slaanesh! Volume to {}",MIX_MAX_VOLUME);
                            Mix_VolumeMusic(MIX_MAX_VOLUME);
                        }
                        break;
                    case SDLK_MINUS:
                        fmt::println("quiet");

                        if(Mix_VolumeMusic(-1)>2)
                        {
                            Mix_VolumeMusic(Mix_VolumeMusic(-1)-2);
                        }
                        else
                            Mix_VolumeMusic(0); //mute

                                    }
            }

        }
        else if(bInJournal)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //int mouseX, mouseY;
                SDL_GetMouseState(&mouseOverX, &mouseOverY);

                //Journal Icon
                if(IsMouseInsideRect({static_cast<int>(SidebarLayout.JournalIconStart.x*0.01*windowSize.x),
                                      static_cast<int>(SidebarLayout.JournalIconStart.y*0.01*windowSize.y+SidebarLayout.InventoryItemScale.y*0.01*windowSize.x),
                                      static_cast<int>(SidebarLayout.InventoryIconScale.x*0.01*windowSize.x),
                                      static_cast<int>(SidebarLayout.InventoryIconScale.y*0.01*windowSize.x)},mouseOverX,mouseOverY))
                {
                    bInJournal=false;
                }

            }


            if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {
                    case SDLK_j:
                        bInJournal = !bInJournal;
                        break;
                }
            }
            //TODO
        }
        else {
            if (Phase == GamePhases::MOVEMENT) {
                if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                    switch (event.key.keysym.sym) {
                        case SDLK_j:
                            bInJournal=!bInJournal;
                            break;
                        case SDLK_i:
                            bInInventory=!bInInventory;
                            break;
                            //TODO what is happening here? possible problem with the button? copied to wrong case at some point?
                            /*
                            if(!locationManager.GetItem(currentCharacter->GetCurrentLocationID())->monsters.empty()){
                            currentEncounterIsOnlyCombat = true;
                            cTracker.location = currentCharacter->GetCurrentLocationID();
                            cTracker.monsters = locationManager.GetItem(cTracker.location)->monsters;
                            cTracker.monID = locationManager.GetItem(cTracker.location)->monsters.back().id;

                           cTracker.updateCurrentMonster();
                            UpdateCombatEncounter();
                            eTracker.activeEncounter = encounterManager.getEncounter(EncounterID::Combat_Encounter);
                            eTracker.encounterID = EncounterID::Combat_Encounter;
                        }break;
                            */
                    }
                }
                if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                    //int mouseX, mouseY;
                    SDL_GetMouseState(&mouseOverX, &mouseOverY);
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        //End Turn Button
                        if (IsMouseInsideRect(
                                {static_cast<int>(SidebarLayout.EndTurnButtonStart.x * windowSize.x * 0.01 - 0.5 *
                                                                                                             (SidebarLayout.EndTurnbuttonHeight *
                                                                                                              SpriteData.Turn_Button.x /
                                                                                                              SpriteData.Turn_Button.y *
                                                                                                              windowSize.y *
                                                                                                              0.01)),
                                 static_cast<int>(SidebarLayout.EndTurnButtonStart.y * windowSize.y * 0.01),
                                 static_cast<int>(SidebarLayout.EndTurnbuttonHeight * SpriteData.Turn_Button.x /
                                                  SpriteData.Turn_Button.y * windowSize.y * 0.01),
                                 static_cast<int>(SidebarLayout.EndTurnbuttonHeight * windowSize.y * 0.01)
                                }, mouseOverX, mouseOverY))
                        { endMovementConfirmation = true;

                            //TODO what is happening here? possible problem with the button? copied to wrong case at some point?
                            //check if we already avoided the fight
                            if(cTracker.alreadyDodged != currentCharacter->GetCurrentLocationID()) {
                                if (!locationManager.GetItem(
                                        currentCharacter->GetCurrentLocationID())->monsters.empty()) {
                                    currentEncounterIsOnlyCombat = true;
                                    cTracker.location = currentCharacter->GetCurrentLocationID();
                                    cTracker.monsters = locationManager.GetItem(cTracker.location)->monsters;
                                    cTracker.monID = cTracker.monsters.back().id;

                                    cTracker.updateCurrentMonster();
                                    UpdateCombatEncounter();
                                    eTracker.activeEncounter = encounterManager.getEncounter(
                                            EncounterID::Combat_Encounter);
                                    eTracker.encounterID = EncounterID::Combat_Encounter;
                                }
                            }

                        }
                        //Inventory Button
                        if(IsMouseInsideRect({static_cast<int>(SidebarLayout.InventoryIconStart.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconStart.y*0.01*windowSize.y+SidebarLayout.InventoryItemScale.y*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.y*0.01*windowSize.x)},mouseOverX,mouseOverY))


                        {
                            bInInventory=true;
                        }
                        //Journal Button
                        if(IsMouseInsideRect({static_cast<int>(SidebarLayout.JournalIconStart.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.JournalIconStart.y*0.01*windowSize.y+SidebarLayout.InventoryItemScale.y*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.y*0.01*windowSize.x)},mouseOverX,mouseOverY))
                        {
                            bInJournal=true;
                        }
                    }

                    for (auto e: map.slots) {
                        if (IsMouseInsideRect(e.locationRect, mouseOverX, mouseOverY)) {
                            if (event.type == SDL_MOUSEMOTION) {

                               // std::cout << "Mouse moved inside the rectangle.\n";
                               // std::cout.flush();

                            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                                if (movementPoints > 0) {
                                    //mausklick reagiert nur wenn die location einen pfad zum aktuellen standort des characters hat
                                    for (auto c: e.connections) {
                                        //durchsuchen die aktiven connections der aktuellen node nach einam pfad zum character
                                        if (character1->GetCurrentLocationID() ==
                                            map.GetSlotByID(c.first)->location_id &&
                                            c.second == true) {
                                            //std::cout << "Mouse clicked inside the rectangle.\n";
                                            //setzen location vom charakter und pos auf das aktuelle e da dies die node ist die gecklickt wurde
                                            moveTarget = e.location_id;
                                            playerMoved = true;
                                            //if we did not dodge past already this turn
                                            if(cTracker.alreadyDodged != moveTarget) {
                                                if (!locationManager.GetItem(
                                                        currentCharacter->GetCurrentLocationID())->monsters.empty()) {
                                                    currentEncounterIsOnlyCombat = true;
                                                    cTracker.location = currentCharacter->GetCurrentLocationID();
                                                    cTracker.monsters = locationManager.GetItem(
                                                            cTracker.location)->monsters;
                                                    cTracker.monID = cTracker.monsters.back().id;

                                                    cTracker.updateCurrentMonster();
                                                    UpdateCombatEncounter();
                                                    eTracker.activeEncounter = encounterManager.getEncounter(
                                                            EncounterID::Combat_Encounter);
                                                    eTracker.encounterID = EncounterID::Combat_Encounter;
                                                }
                                            }


                                        std::cout.flush();
                                    }
                                }

                                }


                            }
                        } else if (!IsMouseInsideRect(e.locationRect, mouseOverX, mouseOverY)) {
                            if (event.type == SDL_MOUSEMOTION) {
                                /*
                                 std::cout << "Mouse moved OUTSIDE the rectangle. " << e.id;
                                std::cout << " \n";
                                std::cout.flush();
                                 */
                            }
                        }
                    }
                }
            }

            if (Phase == GamePhases::ENCOUNTER) {

                //Build Option Rects
                std::vector<std::pair<SDL_Rect,bool>> OptionVector = {};
                int validCount = -1;
                if(eTracker.activeEncounter)//TODO CTD at this position - fix it
                {

                    for (const SceneOption &o: eTracker.activeEncounter->scenes[eTracker.szene].options) {

                        bool bMeetsCriteria = true;

                        if (o.bHasRequirements) {

                            //loop over all requirements and check if fulfilled
                            for (const std::tuple<RequirementFlags, int> &req: o.requirements) {
                                if (!bOptionRequirementMet(req))
                                    bMeetsCriteria = false;
                            }

                        }

                        if (bMeetsCriteria) {
                            validCount++;

                            OptionVector.push_back(
                                    {{static_cast<int>((EncounterLayout.DialogueMainTextStart.x * 0.01 * windowSize.x)),
                                      static_cast<int>((EncounterLayout.DialogueMainTextEnd.y * 0.01 +
                                                        validCount *
                                                        EncounterLayout.DialogueOptionFieldScale.y *
                                                        0.01) * windowSize.y),
                                      static_cast<int>((EncounterLayout.DialogueMainTextEnd.x * 0.01 * windowSize.x)),
                                      static_cast<int>((EncounterLayout.DialogueOptionFieldScale.y * 0.01) *
                                                       windowSize.y)},true});
                        }
                        else
                        {
                            OptionVector.push_back( //Dummy Button
                                    {{
                                             windowSize.x,
                                             windowSize.y,
                                             0, 0
                                     }, false}
                                    );
                        }
                    }
                }
                else
                {
                    fmt::println("ENCOUNTER NULLPTR BUG!");
                }



                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&mouseOverX, &mouseOverY); //TODO REDUNDANCY
                    }



                if (!eTracker.chooseFateReroll && awaitingInput) {

                    if (event.type == SDL_MOUSEBUTTONDOWN) {

                        //Journal Icon
                        if(IsMouseInsideRect({static_cast<int>(SidebarLayout.JournalIconStart.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.JournalIconStart.y*0.01*windowSize.y+SidebarLayout.InventoryItemScale.y*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.y*0.01*windowSize.x)},mouseOverX,mouseOverY))
                        {
                            bInJournal= true;
                        }

                        //int mouseX, mouseY;
                        SDL_Rect button;
                        SDL_GetMouseState(&mouseOverX, &mouseOverY);
                        fmt::println("MouseButtonDownn Mouse x= {}, Mouse Y = {}", mouseOverX, mouseOverY);
                        for (int i = 0; i < OptionVector.size(); i++) {
                            if(OptionVector[i].second){
                                button = OptionVector[i].first;
                                fmt::println("Checking button {}", i);
                                fmt::println("x1 = {}, y1 = {}, x2 = {}, y2 = {}", button.x, button.y, button.w,
                                             button.h);


                                if (IsMouseInsideRect(button, mouseOverX, mouseOverY)) {
                                    fmt::println("Clicked option {}", i);
                                    eTracker.selectedOption = i;
                                    awaitingInput = false;
                                }
                            }
                        }


                    }

                    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                        switch (event.key.keysym.sym) {
                            case SDLK_SPACE:
                                break;
                            case SDLK_1:
                                eTracker.selectedOption = 0;
                                awaitingInput = false;
                                break;
                            case SDLK_2:
                                eTracker.selectedOption = 1;
                                awaitingInput = false;
                                break;
                            case SDLK_3:
                                eTracker.selectedOption = 2;
                                awaitingInput = false;
                                break;
                            case SDLK_j:
                                bInJournal=!bInJournal;
                                break;


                        }
                    }
                } else {
                    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                        switch (event.key.keysym.sym) {
                            case SDLK_SPACE:
                                break;
                            case SDLK_1:
                                eTracker.fateRerollChoice = 0;
                                eTracker.diaPhase = DialoguePhase::FateReroll;
                                break;
                            case SDLK_2:
                                eTracker.fateRerollChoice = 1;
                                break;
                            case SDLK_j:
                                bInJournal=!bInJournal;
                                break;


                        }
                    }
                    if (event.type == SDL_MOUSEBUTTONDOWN) {

                        //Journal Icon
                        if(IsMouseInsideRect({static_cast<int>(SidebarLayout.JournalIconStart.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.JournalIconStart.y*0.01*windowSize.y+SidebarLayout.InventoryItemScale.y*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.x*0.01*windowSize.x),
                                              static_cast<int>(SidebarLayout.InventoryIconScale.y*0.01*windowSize.x)},mouseOverX,mouseOverY))
                        {
                            bInJournal=true;
                        }

                        //int mouseX, mouseY;
                        SDL_Rect button;
                        SDL_GetMouseState(&mouseOverX, &mouseOverY);
                        fmt::println("MouseButtonDownn Mouse x= {}, Mouse Y = {}", mouseOverX, mouseOverY);
                        for (int i = 0; i < 2; i++) {
                            button = OptionVector[0].first;
                        if(i == 1){
                            button.y = button.y+button.h;
                        }
                            fmt::println("Checking button {}", i);
                            fmt::println("x1 = {}, y1 = {}, x2 = {}, y2 = {}", button.x, button.y, button.w, button.h);
                            //SDL_SetRenderDrawColor(renderer(),255,0,0,0);
                            //SDL_RenderFillRect(renderer(),&button);
                            //SDL_Delay(150);

                            if (IsMouseInsideRect(button, mouseOverX, mouseOverY)) {
                                fmt::println("Clicked option {}", i);
                                if (i == 0)
                                    eTracker.diaPhase = DialoguePhase::FateReroll;
                                eTracker.fateRerollChoice = i;
                                awaitingInput = false;
                            }
                        }
                    }


                }
            }

        }

        return false;

    }

    bool BeasthoodState::Input() {

        /*
        // Is not supressed during ImGui input
        const u8 * key_array = SDL_GetKeyboardState( nullptr );
        if( key_array[SDL_SCANCODE_DOWN] )
        {
            brightness -= 1;
        }
        if( key_array[SDL_SCANCODE_UP] ) // Not an else-if, as both buttons can be held at the same time
        {
            brightness += 1;
        }

*/
        return false;

    }

    void BeasthoodState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {

//        if( Mix_PlayingMusic() == 0 )
//        {
//            //Play the music
//            Mix_PlayMusic( villageTheme, -1 );
//        }

        if (Phase == GamePhases::UPKEEP) {

            //place character somewhere if not placed
            if (character1->GetCurrentLocationID() == LocationID::UNASSIGNED) {
                character1->SetCurrentLocation(LocationID::Forest);
                character1->SetPos(locationManager.GetItem(LocationID::Forest)->GetMapSlot()->locationRect);
            }

            movementPoints = currentCharacter->GetCurrentStats().GetStat(SPEED);
            cTracker.Reset();
            Phase = GamePhases::MOVEMENT;
        }


        if (Phase == GamePhases::MOVEMENT) {
            musicManager.changeMusic(bgm::main_theme);

            if (movementPoints > 0 && !endMovementConfirmation) {
                if (playerMoved) {
                    if(!currentEncounterIsOnlyCombat) {

                        character1->SetCurrentLocation(moveTarget);
                        character1->SetPos(locationManager.GetItem(moveTarget)->GetMapSlot()->locationRect);
                        movementPoints--;
                        playerMoved = false;
                    }else{
                        Phase = GamePhases::ENCOUNTER;
                        awaitingInput = true;
                    }
                }
            }
            if(movementPoints == 0 || endMovementConfirmation) {
                //check ob aktuell in combat
                if(!currentEncounterIsOnlyCombat) {
                    Phase = GamePhases::ENCOUNTER;
                    endMovementConfirmation = false;
                    awaitingInput = true;
                    playerMoved = false;

                    //check ob event vorhanden
                    if (locationManager.GetEncounterID(currentCharacter->GetCurrentLocationID()) !=
                        EncounterID::NO_ENCOUNTER_ASSIGNED) {
                        eTracker.encounterID = locationManager.GetEncounterID(currentCharacter->GetCurrentLocationID());
                        eTracker.activeEncounter = encounterManager.getEncounter(eTracker.encounterID);
                        eTracker.diaPhase = DialoguePhase::Scene;
                        eTracker.monsterIDs = encounterManager.getEncounter(eTracker.activeEncounter->id)->monsterIDs;
                        eTracker.szeneWin = eTracker.activeEncounter->fightVictorySzene;
                        eTracker.szeneLoss = eTracker.activeEncounter->fightDefeatSzene;
                    } else {
                        Phase = GamePhases::DISASTER;
                        awaitingInput = false;
                    }
                }else{
                    Phase = GamePhases::ENCOUNTER;
                    awaitingInput = true;
                }
            }
        }
        //movement on map, then trigger event on player location
        if (Phase == GamePhases::ENCOUNTER) {
            //show event text and options on screen, then wait for viable input from Beasthoodstate::input

            //this variable is set when the player has to choose to reroll with his fate points
            if (!eTracker.chooseFateReroll) {
                //255 denotes a finished event
                if (eTracker.szene != 255) {
                    //wait for player input after options of the scene are displayed
                    if (!awaitingInput) {
                        //dumb hack to kill monster when it is defeated via combat
                        if (currentEncounterIsOnlyCombat) {
                            if (eTracker.szene == 4) { //szene 4 passiert nur wenn encounter durch kampf gewonnen
                                //check if this is a encounter triggered fight
                                if(!cTracker.encounterTriggeredThis) {
                                    locationManager.GetItem(cTracker.location)->RemoveMonster(cTracker
                                                                                                      .monID);
                                }
                                cTracker.RemoveMonster(cTracker.monID);
                                cTracker.monstersInFight -1;
                            }
                            if (eTracker.szene == 5) {
                                cTracker.monstersInFight -1;
                                cTracker.RemoveMonster(cTracker.monID);

                            }
                        }
                        //check if the input is viable within the options provided
                        if (eTracker.selectedOption <=
                            eTracker.activeEncounter->scenes[eTracker.szene].options.size() - 1 &&
                            eTracker.selectedOption != -1) {
                            //resolve skillcheck if the option triggers one
                            if (eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].isSkillCheck) {
                                eTracker.bShowPreviousDicerolls = true;
                                ske.setDifficulty(
                                        eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].difficulty);
                                ske.setSkill(
                                        eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].skill);
                                ///terrible spot for this but no easy way to refactor
                                //if in combat check the modifier of the current monster and add/reduce dice
                                if(currentEncounterIsOnlyCombat) {
                                    if(ske.getCurrentSkill() == StatNames::WILLPOWER) {
                                        ske.setModifier(cTracker.horrorRating);
                                    }
                                    if(ske.getCurrentSkill() == StatNames::FIGHT){
                                        ske.setModifier(cTracker.combatRating);
                                    }
                                }
                                //if the skillcheck is not successful we ask if the player wants to spend fate
                                if (!ske.checkSkill()) {
                                    eTracker.diaPhase = DialoguePhase::DieRoll;
                                    awaitingInput = true;
                                    eTracker.chooseFateReroll = true;
                                    eTracker.alreadyDisplayedText = false;
                                } else {
                                    //if successfull we resolve the outcome and set the next scene as well as showing the rolls
                                    eTracker.diaPhase = DialoguePhase::DieRoll;
                                    //spaghetti workaround: if true then outome is combat encounter
                                   eTracker.exFlag = encounterManager.iterateOverOutcomes(
                                            eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].rewardItemIDs,
                                            eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].successOutcomes,
                                            *currentCharacter,Questlog);

                                    inventoryScreen.RebuildInventory();
                                    eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetSuccess;
                                    eTracker.selectedOption = -1;
                                    eTracker.alreadyDisplayedText = false;
                                    awaitingInput = true;


                                }
                            } else {
                                eTracker.exFlag = encounterManager.iterateOverOutcomes(
                                        eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].rewardItemIDs,
                                        eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].successOutcomes,
                                        *currentCharacter,Questlog);
                                inventoryScreen.RebuildInventory();
                                eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetSuccess;
                                eTracker.selectedOption = -1;
                                eTracker.alreadyDisplayedText = false;
                                eTracker.bShowPreviousDicerolls = false;
                                awaitingInput = true;
                            }
                        } else {
                            if (eTracker.selectedOption != -1) {
                                std::cerr << "Selected Input not viable! Choose from displayed options!" << "\n";
                                eTracker.selectedOption = -1;
                                awaitingInput = true;
                            }
                            //must be set true here or softlocks encounter after fate rolls- Max
                            awaitingInput = true;
                        }
                    }

                } else {
                    //if we hit a 255 jump we reset the encounterTracker and activate the next Game Phase
                    if (!currentEncounterIsOnlyCombat) {
                        Phase = GamePhases::DISASTER;
                        eTracker.szene = 0;
                        eTracker.bShowPreviousDicerolls = false;
                        awaitingInput = false;
                        eTracker.diaPhase = DialoguePhase::Scene;
                    } else {
                        if(cTracker.monsters.empty()) {
                            if(!cTracker.encounterTriggeredThis) {
                                Phase = GamePhases::MOVEMENT;
                                eTracker.bShowPreviousDicerolls = false;
                                currentEncounterIsOnlyCombat = false;
                                cTracker.updateCurrentMonster();
                                UpdateCombatEncounter();
                                cTracker.alreadyDodged = cTracker.location;
                            }

                        } else {
                            Phase = GamePhases::ENCOUNTER;
                            eTracker.bShowPreviousDicerolls = false;
                            cTracker.monID = cTracker.monsters.back().id;
                            awaitingInput = true;
                            cTracker.updateCurrentMonster();
                            UpdateCombatEncounter();
                            eTracker.activeEncounter = encounterManager.getEncounter(
                                    EncounterID::Combat_Encounter);
                            eTracker.encounterID = EncounterID::Combat_Encounter;
                        }
                    }

                    eTracker.szene = 0;
                    awaitingInput = false;
                    eTracker.diaPhase = DialoguePhase::Scene;

                }


            } else {
                if (eTracker.fateRerollChoice == 0 && currentCharacter->GetFatePoints() > 0) {
                    currentCharacter->SpendFate();
                    if (ske.addFateDice()) {
                        eTracker.exFlag = encounterManager.iterateOverOutcomes(
                                eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].rewardItemIDs,
                                eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].successOutcomes,
                                *currentCharacter,Questlog);
                        inventoryScreen.RebuildInventory();
                        eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetSuccess;
                        eTracker.alreadyDisplayedText = false;
                        eTracker.chooseFateReroll = false;
                        eTracker.fateRerollChoice = -1;
                        eTracker.diaPhase = DialoguePhase::Scene;
                        awaitingInput = true;
                    } else {
                        if (currentCharacter->GetFatePoints() > 0) {
                            eTracker.diaPhase = DialoguePhase::DieRoll;
                            eTracker.alreadyDisplayedText = false;
                            eTracker.fateRerollChoice = -1;
                        }

                    }
                }
                if (eTracker.fateRerollChoice == 1 || currentCharacter->GetFatePoints() <= 0) {
                    eTracker.exFlag = encounterManager.iterateOverOutcomes(
                            eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].failureItemIDs,
                            eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].failureOutcomes,
                            *currentCharacter,Questlog);
                    inventoryScreen.RebuildInventory();
                    eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetFail;
                    eTracker.alreadyDisplayedText = false;
                    eTracker.chooseFateReroll = false;
                    eTracker.fateRerollChoice = -1;
                    eTracker.diaPhase = DialoguePhase::Scene;
                    awaitingInput = true;
                    eTracker.selectedOption = -1;
                }
            }
            //resolve external functions of execute flags
            switch(eTracker.exFlag){
                case ExecuteFlags::StartCombat:
                    //save the current event to jump back in after combat
                    eTrackerSaver = eTracker;
                    cTracker.encounterTriggeredThis = true;
                    currentEncounterIsOnlyCombat = true;
                    //prepare a combat encounter on the location without filling the location with monsters
                    for(int i = 0; i< eTracker.monsterIDs.size();i++) {
                        cTracker.monsters.push_back(monsterManager.GetMonster(eTracker.monsterIDs[i]));
                    }
                        Phase = GamePhases::ENCOUNTER;
                        eTracker.bShowPreviousDicerolls = false;
                        cTracker.monID = cTracker.monsters.back().id;
                        cTracker.updateCurrentMonster();
                        UpdateCombatEncounter();
                        eTracker.activeEncounter = encounterManager.getEncounter(
                                EncounterID::Combat_Encounter);
                        eTracker.encounterID = EncounterID::Combat_Encounter;

                        eTracker.szene = 0;
                        awaitingInput = true;
                        eTracker.diaPhase = DialoguePhase::Scene;
                        eTracker.exFlag = ExecuteFlags::NONE;
                        break;

                case ExecuteFlags::FinishedCombatWIN:
                    //win in encounter triggered combat goes to szeneWin
                    if(cTracker.encounterTriggeredThis) {
                        if(cTracker.monsters.empty()) {
                            cTracker.encounterTriggeredThis = false;
                            eTracker = eTrackerSaver;
                            eTracker.szene = eTracker.szeneWin;
                            eTracker.alreadyDisplayedText = false;
                            eTracker.bShowPreviousDicerolls = false;
                            currentEncounterIsOnlyCombat = false;
                            eTracker.diaPhase = DialoguePhase::Scene;
                            awaitingInput = true;
                            eTracker.exFlag = ExecuteFlags::NONE;
                            cTracker.Reset();
                        }else{
                            //if the combat has multiple enemies we go here
                            Phase = GamePhases::ENCOUNTER;
                            currentEncounterIsOnlyCombat = true;
                            eTracker.bShowPreviousDicerolls = false;
                            cTracker.monID = cTracker.monsters.back().id;
                            awaitingInput = true;
                            cTracker.updateCurrentMonster();
                            UpdateCombatEncounter();
                            eTracker.activeEncounter = encounterManager.getEncounter(
                                    EncounterID::Combat_Encounter);
                            eTracker.encounterID = EncounterID::Combat_Encounter;
                            eTracker.exFlag = ExecuteFlags::NONE;

                        }
                    }
                    break;
                    //running away immediately triggers LOSS in combats triggered by events so no need to trigger more combat
                case ExecuteFlags::FinishedCombatLOSS:
                    if(cTracker.encounterTriggeredThis) {
                        cTracker.encounterTriggeredThis = false;
                        eTracker = eTrackerSaver;
                        eTracker.szene = eTracker.szeneLoss;
                        eTracker.bShowPreviousDicerolls = false;
                        currentEncounterIsOnlyCombat = false;
                        eTracker.diaPhase = DialoguePhase::Scene;
                        awaitingInput = true;
                        eTracker.exFlag = ExecuteFlags::NONE;
                        cTracker.Reset();

                    }
                    break;
                case ExecuteFlags::SpawnMonster:
                   //TODO implement spawns in general too
                   break;
                case ExecuteFlags::UnloadLeadBullet:
                    if(currentCharacter->GetEquipment().first && currentCharacter->GetEquipment().first->GetItemID()==ItemID::LoadedGunLead)
                    {
                        currentCharacter->UnequipItem(ItemID::LoadedGunLead);//unload gun in first
                        currentCharacter->RemoveFromInventory(ItemID::LoadedGunLead);
                        currentCharacter->EquipItem(itemManager.GetItem(ItemID::GUN));

                    }
                    else if(currentCharacter->GetEquipment().second && currentCharacter->GetEquipment().second->GetItemID()==ItemID::LoadedGunLead)//tbh redundant - you need the gun to get here
                    {
                        currentCharacter->UnequipItem(ItemID::LoadedGunLead);//unload gun in first
                        currentCharacter->RemoveFromInventory(ItemID::LoadedGunLead);
                        currentCharacter->EquipItem(itemManager.GetItem(ItemID::GUN));
                    }
                    break;
                case ExecuteFlags::UnloadSilverBullet:
                    if(currentCharacter->GetEquipment().first && currentCharacter->GetEquipment().first->GetItemID()==ItemID::LoadedGunSilver)
                    {
                        currentCharacter->UnequipItem(ItemID::LoadedGunSilver);//unload gun in first
                        currentCharacter->RemoveFromInventory(ItemID::LoadedGunSilver);
                        currentCharacter->EquipItem(itemManager.GetItem(ItemID::GUN));

                    }
                    else if(currentCharacter->GetEquipment().second && currentCharacter->GetEquipment().second->GetItemID()==ItemID::LoadedGunSilver)//tbh redundant - you need the gun to get here
                    {
                        currentCharacter->UnequipItem(ItemID::LoadedGunSilver);//unload gun in first
                        currentCharacter->RemoveFromInventory(ItemID::LoadedGunSilver);
                        currentCharacter->EquipItem(itemManager.GetItem(ItemID::GUN));
                    }
                    break;
                default:eTracker.exFlag = ExecuteFlags::NONE; break;

            }
        }

        ///Removing this has had no adverse effects so far. However, im keeping it around just in case. -Max
        /// Nevermind, this fixes a edge case. FIX ATTEMPT stays until i refactor this whole mess. -Max
        ///FIX ATTEMPT:
        if (eTracker.szene == 255)
        {//if we hit a 255 jump we reset the encounterTracker and activate the next Game Phase
            if (!currentEncounterIsOnlyCombat) {
                Phase = GamePhases::DISASTER;
                eTracker.szene = 0;
                eTracker.bShowPreviousDicerolls = false;
                awaitingInput = false;
                eTracker.diaPhase = DialoguePhase::Scene;
            } else {
                if(cTracker.monsters.empty()) {
                    if(!cTracker.encounterTriggeredThis) {
                        Phase = GamePhases::MOVEMENT;
                        eTracker.bShowPreviousDicerolls = false;
                        currentEncounterIsOnlyCombat = false;
                        cTracker.updateCurrentMonster();
                        UpdateCombatEncounter();
                        cTracker.alreadyDodged = cTracker.location;

                        eTracker.szene = 0;
                        awaitingInput = false;
                        eTracker.diaPhase = DialoguePhase::Scene;
                    }
                } else {
                    Phase = GamePhases::ENCOUNTER;
                    eTracker.bShowPreviousDicerolls = false;
                    cTracker.monID = cTracker.monsters.back().id;
                    cTracker.updateCurrentMonster();
                    UpdateCombatEncounter();
                    eTracker.activeEncounter = encounterManager.getEncounter(
                            EncounterID::Combat_Encounter);
                    eTracker.encounterID = EncounterID::Combat_Encounter;

                    eTracker.szene = 0;
                    awaitingInput = true;
                    eTracker.diaPhase = DialoguePhase::Scene;
                }
            }

        }


        if(Phase == GamePhases::DISASTER){
            musicManager.changeMusic(bgm::main_theme);
            std::cout << "DISASTER PHASE REACHED \n";
            std::cout.flush();


            //testing spawning monsters

            if(locationManager.GetItem(LocationID::Thicket)->monsters.size() < 3) {
                locationManager.GetItem(LocationID::Thicket)->AddMonster(monsterManager.GetMonster(MonsterID::Wolf));
            }

            Phase = GamePhases::UPKEEP;

        }


        // std::cout << "Item: " << character1->GetInventory().back()->GetName();
        // std::cout << "\n";
    }

    std::map<SceneCompositionSlots,SDL_Point> sceneCompositionTarget //  TODO EXPAND AS NEEDED
            {
                    {SceneCompositionSlots::CharacterMain, EncounterLayout.characterMainPoint},
                    {SceneCompositionSlots::CharacterAtBottomMain, EncounterLayout.characterBottomPoint},
                    {SceneCompositionSlots::CharacterFront,{EncounterLayout.characterMainPoint.x+10,EncounterLayout.characterMainPoint.y}},
                    {SceneCompositionSlots::EnemyMain,EncounterLayout.enemyMainPoint},
                    {SceneCompositionSlots::NPCAtBottomMain,EncounterLayout.npcBottomPoint},
                    {SceneCompositionSlots::Enemy_2,{EncounterLayout.enemyMainPoint.x+6,EncounterLayout.enemyMainPoint.y+10}},
                    {SceneCompositionSlots::Enemy_3,{EncounterLayout.enemyMainPoint.x+2,EncounterLayout.enemyMainPoint.y-5}},
                    {SceneCompositionSlots::InteractionMain,EncounterLayout.enemyMainPoint},
                    {SceneCompositionSlots::OverlayMainPoint,EncounterLayout.overlayMainPoint}
            };
    void BeasthoodState::RenderSceneComposition(const std::vector<std::tuple<SceneCompositionEntities,SceneCompositionSlots>>& compositionVector,
                                                const EnvironmentType environment)
    {
        switch (environment) {
            case EnvironmentType::DenseForest: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::MonasteryPath: musicManager.changeMusic(bgm::main_theme);break;
            case EnvironmentType::Village: musicManager.changeMusic(bgm::village1);break;
            case EnvironmentType::Village2: musicManager.changeMusic(bgm::village1);break;
            case EnvironmentType::WindmillOutskirts: musicManager.changeMusic(bgm::main_theme);break;
            case EnvironmentType::HunterCamp: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::ForestOutskirts: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::ForestClearing: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::ForestLake: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::HeartApproach: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::HermitLodge: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::Ravine: musicManager.changeMusic(bgm::forest_quiet);break;
            case EnvironmentType::ForestHeart: musicManager.changeMusic(bgm::battle);break;
            case EnvironmentType::MonasteryInterior: musicManager.changeMusic(bgm::monastery);break;
            default:musicManager.changeMusic(bgm::main_theme);break;




        }


        SDL_Rect targetRect;
        float perspectiveFactor = 1.0;//multiply with h und w to adjust to background
        switch (environment) {
            case EnvironmentType::DenseForest: perspectiveFactor = 1.0;break;
            case EnvironmentType::MonasteryPath: perspectiveFactor = 0.5;break;
            case EnvironmentType::Village: perspectiveFactor = 0.4;break;
            case EnvironmentType::Village2: perspectiveFactor = 0.4;break;
            case EnvironmentType::WindmillOutskirts: perspectiveFactor = 0.5;break;
            case EnvironmentType::HunterCamp: perspectiveFactor = 0.6;break;
            case EnvironmentType::ForestOutskirts: perspectiveFactor = 0.3;break;
            case EnvironmentType::ForestClearing: perspectiveFactor = 0.9;break;
            case EnvironmentType::ForestLake: perspectiveFactor = 0.7;break;
            case EnvironmentType::HeartApproach: perspectiveFactor = 0.75;break;
            case EnvironmentType::HermitLodge: perspectiveFactor = 0.7;break;
            case EnvironmentType::MonasteryOutside:perspectiveFactor=0.6;break;


            default: perspectiveFactor = 1.0;

        }

        for(std::tuple<SceneCompositionEntities,SceneCompositionSlots> compElement: compositionVector)
        {

            switch(get<0>(compElement))
            {
                case SceneCompositionEntities::Character:
                    targetRect.x = windowSize.x * (sceneCompositionTarget[get<1>(compElement)].x*0.01);
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueLKY*windowSize.y*perspectiveFactor));
                    targetRect.w = static_cast<int>(SpriteData.ScalingvalueLKX*windowSize.x*perspectiveFactor); // fix res dependence TODO differenciate between different player sprites
                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueLKY*windowSize.y*perspectiveFactor);
                    renderFromSpritesheet(targetRect,playerMainSpite);

                    break;
                case SceneCompositionEntities::Werewolf:

                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingValueGarouY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingValueGarouX*windowSize.x*perspectiveFactor;
                    targetRect.h = static_cast<int>(SpriteData.ScalingValueGarouY*windowSize.y*perspectiveFactor);
                    renderFromSpritesheet(targetRect,enemyWereWolfMainSprite);


                    break;
                case SceneCompositionEntities::Monk:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueMNKY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueMKNX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueMNKY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,monk1Sprite);

                    break;
                case SceneCompositionEntities::Abbot:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueABBTY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueABBTX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueABBTY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,abbotSprite);
                    break;
                case SceneCompositionEntities::Hermit:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueAnthonyY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueAnthonyX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueAnthonyY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,anthonySprite);
                    break;
                case SceneCompositionEntities::Villager1:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvaluePSNT1Y*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvaluePSNT1X*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvaluePSNT1Y*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,peasant1Sprite);
                    break;
                case SceneCompositionEntities::Villager2:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvaluePSNT2Y*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvaluePSNT2X*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvaluePSNT2Y*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,peasant2Sprite);
                    break;
                case SceneCompositionEntities::VillagerCouple:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvaluePSNT1Y*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvaluePSNT1X*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvaluePSNT1Y*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,peasant1CoupleSprite);
                    break;
                case SceneCompositionEntities::Healer:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueWoman1Y*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueWoman1X*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueWoman1Y*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,peasantWomanSprite);
                    break;
                case SceneCompositionEntities::Hunter:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueHunterY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueHunterX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueHunterY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,hunterSprite);
                    break;


                case SceneCompositionEntities::Wolf:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueWolfY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueWolfX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueWolfY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,enemyWolfSprite);

                    break;
                case SceneCompositionEntities::Bear:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueBearY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueBearX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueBearY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,enemyBearSprite);
                    break;
                case SceneCompositionEntities::Mercenary:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueMercY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueMercX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueMercY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,mercenarySprite);
                    break;
                case SceneCompositionEntities::SpearSkeleton:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingvalueSkeletonSpearY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingvalueSkeletonSpearX*windowSize.x*perspectiveFactor;

                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueSkeletonSpearY*windowSize.y*perspectiveFactor);

                    renderFromSpritesheet(targetRect,enemySkeletonSpearSprite);
                    break;


                    //Overlays
                case SceneCompositionEntities::RitualSkullOverlay:
                    renderFromSpritesheet({0,0,static_cast<int>(windowSize.x*EncounterLayout.SceneEnd.x*0.01),static_cast<int>(windowSize.y*EncounterLayout.SceneEnd.y*0.01)},OverlayForestClearingSkull);
                    //SDL_Rect sceneWindow = {0,0,static_cast<int>(windowSize.x*EncounterLayout.SceneEnd.x*0.01),static_cast<int>(windowSize.y*EncounterLayout.SceneEnd.y*0.01)};
                    break;

                default:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[get<1>(compElement)].y )*0.01-(SpriteData.ScalingValueGarouY*windowSize.y*perspectiveFactor));
                    targetRect.w = SpriteData.ScalingValueGarouX*windowSize.x*perspectiveFactor;
                    //fmt::println("Garou X: {}", SpriteData.ScalingValueGarouX*windowSize.x);
                    targetRect.h = static_cast<int>(SpriteData.ScalingValueGarouY*windowSize.y*perspectiveFactor);
                    //fmt::println("Garou Y: {} = {} * {} * {}", SpriteData.ScalingValueGarouY*windowSize.y,SpriteData.Garou_IMG.y,SpriteData.ScalingValueGarouY,windowSize.y);
                    renderFromSpritesheet(targetRect,errorIMG);
                    fmt::println("Scene Element not yet implemented");
            }

        }


    }


    void BeasthoodState::RenderSidebar()
    {

        SDL_Rect SidebarMain {static_cast<int>(SidebarLayout.SidebarStart.x*windowSize.x*0.01),
                              static_cast<int>(SidebarLayout.SidebarStart.y*windowSize.y*0.01),
                              static_cast<int>(SidebarLayout.SidebarSize.x*0.01*windowSize.x),
                               static_cast<int>(SidebarLayout.SidebarSize.y*0.01*windowSize.y)}; //todo move outside scope
        SDL_SetRenderDrawColor(renderer(),0,0,0,0);
        SDL_RenderFillRect(renderer(),&SidebarMain);
        Texture *SidebarText = textToTexture(currentCharacter->GetName().c_str());
        SDL_Rect SidebarTextTarget = {
                static_cast<int>(SidebarLayout.SidebarContentStart.x*windowSize.x*0.01),
                static_cast<int>(SidebarLayout.SidebarContentStart.y*windowSize.y*0.01),
                static_cast<int>(SidebarLayout.ClassTextBox.x*windowSize.x*0.01),
                static_cast<int>(SidebarLayout.ClassTextBox.y*windowSize.y*0.01)

        };

        renderText(SidebarTextTarget,SidebarText); //TODO complete Placeholder, ideally replace with premade image/portrait etc.

        //todo make font size variable

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Stamina   "+ std::to_string(currentCharacter->GetStamina())).c_str());
        renderText(SidebarTextTarget,SidebarText);

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Sanity   "+ std::to_string(currentCharacter->GetSanity())).c_str());
        renderText(SidebarTextTarget,SidebarText);


        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Will Points   "+ std::to_string(currentCharacter->GetFatePoints())).c_str());
        renderText(SidebarTextTarget,SidebarText);





        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y; //todo make font size variable
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Fight   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::FIGHT))).c_str());
        renderText(SidebarTextTarget,SidebarText);

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Speed   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::SPEED))).c_str());
        renderText(SidebarTextTarget,SidebarText);

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Occult   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::OCCULT))).c_str());
        renderText(SidebarTextTarget,SidebarText);

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Faith   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::FAITH))).c_str());
        renderText(SidebarTextTarget,SidebarText);

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Willpower   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::WILLPOWER))).c_str());
        renderText(SidebarTextTarget,SidebarText);

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Sneak   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::SNEAK))).c_str());
        renderText(SidebarTextTarget,SidebarText);

        //Sketch out Inventory



        //Inventory proper

        SDL_Rect InventoryMain =
                {static_cast<int>(SidebarLayout.InventoryStart.x*windowSize.x*0.01),
                 static_cast<int>(SidebarLayout.InventoryStart.y*windowSize.y*0.01),
                 static_cast<int>(SidebarLayout.InventoryScale.x*windowSize.x*0.01),
                 static_cast<int>(SidebarLayout.InventoryScale.y*windowSize.y*0.01)


                };
        SDL_SetRenderDrawColor(renderer(),5,5,5,0);
        SDL_RenderFillRect(renderer(),&InventoryMain);



        //Equipped Items //todo single them out further


        SDL_Rect EquipR =
                {
                        static_cast<int>((SidebarIcons.Right.position.x * windowSize.x*0.01)),
                        static_cast<int>(SidebarIcons.Right.position.y*windowSize.y*0.01),
                        static_cast<int>(SidebarIcons.Right.position.h*windowSize.x*0.01),
                        static_cast<int>(SidebarIcons.Right.position.w*windowSize.x*0.01),

                };
        std::pair<Item*, Item*>currentEquipment = currentCharacter->GetEquipment();
        if(get<1>(currentEquipment)!= nullptr)
        {
            //fmt::println("{} in right hand", get<0>(currentEquipment)->GetName());
            //if sth equipped in 0, render icon,


            RenderItemIcon(renderer(),get<1>(currentEquipment),Icons[0],Icons,SpriteData.BagIconScale,EquipR);

        }
        else
        {
            SDL_RenderCopy(renderer(), emptyItem, &SpriteData.BagIconScale, &EquipR);
            //SDL_SetRenderDrawColor(renderer(),100,5,30,0);
            //SDL_RenderFillRect(renderer(),&EquipR);
            //fmt::println("nothing in right hand");
        }

        SDL_Rect EquipL =
                {
                        static_cast<int>((SidebarIcons.Left.position.x * windowSize.x*0.01)),
                        static_cast<int>(SidebarIcons.Left.position.y*windowSize.y*0.01),
                        static_cast<int>(SidebarIcons.Left.position.h*windowSize.x*0.01),
                        static_cast<int>(SidebarIcons.Left.position.w*windowSize.x*0.01),

                };

        if(get<0>(currentEquipment)!= nullptr || (get<1>(currentEquipment)!= nullptr && get<1>(currentEquipment)->GetHandsNeeded()==2))
        {
            RenderItemIcon(renderer(),get<0>(currentEquipment),Icons[0],Icons,SpriteData.BagIconScale,EquipL);

        }
        else
        {
            //fmt::println("nothing in left hand");
            SDL_RenderCopy(renderer(), emptyItem, &SpriteData.BagIconScale, &EquipL);
        }

        if(bShowLeftItemInfo)
        {
            RenderInventorySelectionNoOption(mouseOverX,mouseOverY,windowSize.x,windowSize.y, true);
        }
        if(bShowRightItemInfo)
        {
            RenderInventorySelectionNoOption(mouseOverX,mouseOverY,windowSize.x,windowSize.y,false);
        }

        //fmt::println("{} items in inventory", currentCharacter->GetInventory().size());

        //Render Inventory Button
        SDL_Rect InventoryButton = {
                static_cast<int>(SidebarLayout.InventoryIconStart.x*0.01*windowSize.x),
                static_cast<int>(SidebarLayout.InventoryIconStart.y*0.01*windowSize.y+SidebarLayout.InventoryItemScale.y*0.01*windowSize.x),
                static_cast<int>(SidebarLayout.InventoryIconScale.x*0.01*windowSize.x),
                static_cast<int>(SidebarLayout.InventoryIconScale.y*0.01*windowSize.x)

        };
        if (Phase == GamePhases::ENCOUNTER || bInJournal)
        {
            SDL_RenderCopy(renderer(),bagIconOff,&SpriteData.BagIconScale,&InventoryButton);
        }
        else if(IsMouseInsideRect(InventoryButton,mouseOverX,mouseOverY))
        {
            SDL_RenderCopy(renderer(),bagIconMouseover,&SpriteData.BagIconScale,&InventoryButton);
        }
        else
            SDL_RenderCopy(renderer(),bagIconOn,&SpriteData.BagIconScale,&InventoryButton);

        //Questlog Button
        SDL_Rect JournalButton ={
                static_cast<int>(SidebarLayout.JournalIconStart.x*0.01*windowSize.x),
                static_cast<int>(SidebarLayout.JournalIconStart.y*0.01*windowSize.y+SidebarLayout.JournalIconScale.y*0.01*windowSize.x),
                static_cast<int>(SidebarLayout.JournalIconScale.x*0.01*windowSize.x),
                static_cast<int>(SidebarLayout.JournalIconScale.y*0.01*windowSize.x)};
        if (bInInventory)
        {
            SDL_RenderCopy(renderer(),journalIconOff,&SpriteData.BagIconScale,&JournalButton);
        }
        else if(IsMouseInsideRect(JournalButton,mouseOverX,mouseOverY))
        {
            SDL_RenderCopy(renderer(),journalIconMouseover,&SpriteData.BagIconScale,&JournalButton);
        }
        else
            SDL_RenderCopy(renderer(),journalIcon,&SpriteData.BagIconScale,&JournalButton);

        SDL_DestroyTexture(SidebarText);
        SidebarText = nullptr;
    }
    void BeasthoodState::RenderInventorySelection(int mouseX, int mouseY, int screenWidth, int screenHeight) {

        if(inventoryScreen.currentPage.MouseOverIcon->referencedItem)
        {
        SDL_Rect Selection{static_cast<int>(screenWidth *
                                            (inventoryScreen.currentPage.StartPoint.x - ItemDetailedView.Dimensions.x) *
                                            0.01),
                           static_cast<int>(screenHeight * (inventoryScreen.currentPage.StartPoint.y) * 0.01),
                           static_cast<int>(screenWidth * ItemDetailedView.Dimensions.x * 0.01),
                           static_cast<int>(screenWidth * ItemDetailedView.Dimensions.y * 0.01)};


        //open submenu pop-up/lock pop-up in place, if implemented in hover
            SDL_SetRenderDrawColor(renderer(),5,5,5,0);
            SDL_RenderFillRect(renderer(), &Selection);


        SDL_Rect ButtonEquipRight = {
                static_cast<int>(Selection.x + ItemDetailedView.EquipRightPos.x * 0.01 * screenWidth),
                static_cast<int>(Selection.y + ItemDetailedView.EquipRightPos.y * 0.01 * screenWidth),
                static_cast<int>(ItemDetailedView.ButtonScale.x * 0.01 * screenWidth),
                static_cast<int>(ItemDetailedView.ButtonScale.y * 0.01 * screenWidth)
        };

        SDL_Rect ButtonEquipLeft = {
                static_cast<int>(Selection.x + ItemDetailedView.EquipLeftPos.x * 0.01 * screenWidth),
                static_cast<int>(Selection.y + ItemDetailedView.EquipLeftPos.y * 0.01 * screenWidth),
                static_cast<int>(ItemDetailedView.ButtonScale.x * 0.01 * screenWidth),
                static_cast<int>(ItemDetailedView.ButtonScale.y * 0.01 * screenWidth)
        };
        SDL_SetRenderDrawColor(renderer(), 240, 0, 0, 0);
        SDL_RenderFillRect(renderer(), &ButtonEquipRight);

        SDL_RenderFillRect(renderer(), &ButtonEquipLeft);


        Texture *DisplayText{};
        Item *ItemToDisplay = inventoryScreen.currentPage.MouseOverIcon->referencedItem;



            DisplayText = textToTexture(ItemToDisplay->GetName().c_str());

            renderText({Selection.x, static_cast<int>(Selection.y), 10, 10}, DisplayText); //Todo move text a bit to the right, add borders
            SDL_DestroyTexture(DisplayText);




            DisplayText = textToTexture(
                    (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::FIGHT)) + " FIGHT").c_str());
            renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.02), 10, 10}, DisplayText);
            SDL_DestroyTexture(DisplayText);

            DisplayText = textToTexture(
                    (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::SPEED)) + " SPEED").c_str());
            renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.03), 10, 10}, DisplayText);
            SDL_DestroyTexture(DisplayText);

            DisplayText = textToTexture(
                    (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::SNEAK)) + " SNEAK").c_str());
            renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.04), 10, 10}, DisplayText);
            SDL_DestroyTexture(DisplayText);

            DisplayText = textToTexture(
                    (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::WILLPOWER)) + " WILLPOWER").c_str());
            renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.05), 10, 10}, DisplayText);
            SDL_DestroyTexture(DisplayText);

            DisplayText = textToTexture(
                    (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::FAITH)) + " FAITH").c_str());
            renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.06), 10, 10}, DisplayText);
            SDL_DestroyTexture(DisplayText);

            DisplayText = textToTexture(
                    (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::OCCULT)) + " OCCULT").c_str());
            renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.07), 10, 10}, DisplayText);
            SDL_DestroyTexture(DisplayText);


            if (ItemToDisplay->GetAbility()) {
                switch (ItemToDisplay->GetAbility()->GetName()) {
                    case (AbilityID::DrawExtraItem):
                        DisplayText = textToTexture("Draw Extra Item - change to sth different, drawing too abstract");
                        break;
                    case (AbilityID::ReduceStaminaLoss):
                        DisplayText = textToTexture("Reduce Stamina Loss");
                        break;
                    default:
                        DisplayText = textToTexture("unknown or no ability?");
                        break;

                }
                renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.085), 10, 10}, DisplayText);
                SDL_DestroyTexture(DisplayText);
            }
        }
    }






    //todo check if same bug is present as in upper version
    void BeasthoodState::RenderInventorySelectionNoOption(int mouseX, int mouseY, int screenWidth, int screenHeight, bool left_item)
    {
        SDL_Rect Selection {static_cast<int>(mouseX-static_cast<int>(screenWidth*ItemDetailedView.Dimensions.x*0.01)),
                            static_cast<int>(mouseY-static_cast<int>(screenWidth*ItemDetailedView.Dimensions.y*0.01)),
                            static_cast<int>(screenWidth*ItemDetailedView.Dimensions.x*0.01),
                            static_cast<int>(screenWidth*ItemDetailedView.Dimensions.y*0.01)};


        //open submenu pop-up/lock pop-up in place, if implemented in hover
        SDL_SetRenderDrawColor(renderer(),5,5,5,0);
        SDL_RenderFillRect(renderer(),&Selection);

        Texture * DisplayText {};
        Item * ItemToDisplay = nullptr;
        if(left_item){
             ItemToDisplay= currentCharacter->GetEquipment().first;
        }
        else
        {
            ItemToDisplay= currentCharacter->GetEquipment().second;
        }
        DisplayText = textToTexture(ItemToDisplay->GetName().c_str());

        renderText({Selection.x,static_cast<int>(Selection.y), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText); //todo there is a better way surely



        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::FIGHT))+" FIGHT").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.02), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);

        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::SPEED))+" SPEED").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.03), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);

        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::SNEAK))+" SNEAK").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.04), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);

        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::WILLPOWER))+" WILLPOWER").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.05), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);

        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::FAITH))+" FAITH").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.06), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);

        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::OCCULT))+" OCCULT").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.07), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);


        if( ItemToDisplay->GetAbility())
         {
             switch (ItemToDisplay->GetAbility()->GetName()) {
                 case(AbilityID::DrawExtraItem):
                     DisplayText = textToTexture("Draw Extra Item - change to sth different, drawing too abstract");
                     break;
                 case(AbilityID::ReduceStaminaLoss):
                     DisplayText = textToTexture("Reduce Stamina Loss");
                     break;
                 default:
                     DisplayText = textToTexture("unknown or no ability?");
                     break;

             }
             renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.085), 10,10 },DisplayText);
             SDL_DestroyTexture(DisplayText);
         }



        DisplayText = nullptr;
        //ItemToDisplay = nullptr;



    }
    void BeasthoodState::RenderInventory()
    {
        inventoryScreen.currentPage.RenderInventoryPage(renderer(),windowSize.x,windowSize.y, emptyInventoryItem, Icons,SpriteData.BagIconScale);

        if(inventoryScreen.currentPage.bIconHover || inventoryScreen.currentPage.bIconSelected)
        {
            RenderInventorySelection(mouseOverX,mouseOverY,windowSize.x,windowSize.y); //todo externalize
        }
    }

    void BeasthoodState::RenderTurnButton(bool bIsActive)
    {
        SDL_Rect buttonPlacement =
                {static_cast<int>(SidebarLayout.EndTurnButtonStart.x*windowSize.x*0.01 - 0.5*(SidebarLayout.EndTurnbuttonHeight*SpriteData.Turn_Button.x/SpriteData.Turn_Button.y*windowSize.y*0.01)),
                 static_cast<int>(SidebarLayout.EndTurnButtonStart.y*windowSize.y*0.01),
                 static_cast<int>(SidebarLayout.EndTurnbuttonHeight*SpriteData.Turn_Button.x/SpriteData.Turn_Button.y*windowSize.y*0.01),
                 static_cast<int>(SidebarLayout.EndTurnbuttonHeight*windowSize.y*0.01)
                };
        SDL_Rect srcRect = {0,0,SpriteData.Turn_Button.x,SpriteData.Turn_Button.y};
        if(bIsActive && !bInInventory && !bInJournal)
        {
            if(IsMouseInsideRect(buttonPlacement, mouseOverX,mouseOverY))
            {
                SDL_RenderCopy(renderer(),endTurnButtonMouseover,&srcRect,&buttonPlacement);
            }
            else
            {
                SDL_RenderCopy(renderer(),endTurnButtonOn,&srcRect,&buttonPlacement);
            }
        }
        else
        {

            SDL_RenderCopy(renderer(),endTurnButtonOff,&srcRect,&buttonPlacement);
        }
    }

    void BeasthoodState::Render(const u64 frame, const u64 totalMSec, const f32 deltaT) {
        if(tempHealth>=1.)
        {
            tempHealth=0.;
        }
        tempHealth += deltaT*0.05;


        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);//TODO WINDOWSIZE HERE - fix redundancy

        SDL_SetRenderDrawColor(renderer(), 0x7F, 0x00, 0x7F, 0x00);
        SDL_RenderClear(renderer());

        if (Phase == GamePhases::UPKEEP || Phase == GamePhases::MOVEMENT) {

            //set color for connected path lines
            SDL_SetRenderDrawColor(renderer(), 0x00, 0x7F, 0x00, 0x00);

            for (const auto &e: locationManager.GetAllItems()) {
                //render the locations
                // renderFromSpritesheet(e->GetMapSlot()->locationRect, forestLocationIconTexture);


                if (e->fog_of_war) {
                    //find the relevant location textures using LocationID enum
                    auto it = locationTextureMap.find(e->GetLocationID());
                    if (it != locationTextureMap.end()) {
                        SDL_Texture *icon = it->second.iconTexture;
                        SDL_Texture *name = it->second.nameTexture;

                        renderFromSpritesheet(e->GetMapSlot()->locationRect, icon);
                        renderText(e->GetMapSlot()->locationRect, name);
                        if(currentCharacter->GetCurrentLocationID() == e->GetLocationID()){
                            renderFromSpritesheet(e->GetMapSlot()->playerRects[2],playerMapIconTexture);
                        }

                        //renders the icon of the monsters in the location
                        if(!e->monsters.empty()){
                            for(int i = 0;i< e->monsters.size();i++){
                                renderFromSpritesheet(e->GetMapSlot()->enemyRects[i],monsterIDtoTextureMap[e->monsters[i].id]);
                            }
                        }

                    }
                    if (e->quest_marker) {}


                    //render connections
                    for (auto c: e->GetActiveConnections()) {
                        SDL_RenderDrawLine(renderer(), e->GetMapSlot()->position.x, e->GetMapSlot()->position.y,
                                           map.GetSlotByID(c)->position.x, map.GetSlotByID(c)->position.y);
                    }
                }
                //render character icon on map
                if (character1->GetCurrentLocationID() != LocationID::UNASSIGNED) {
                    //  renderFromSpritesheet(character1->GetRect(), playerMapIconTexture);
                }
            }
            RenderSidebar();
            RenderTurnButton(true);
        }

        if (Phase == GamePhases::ENCOUNTER) {

            if (eTracker.szene != 255) {

                SDL_SetRenderDrawColor(renderer(),0,0,0,0);
                SDL_Rect sceneWindow = {0,0,static_cast<int>(windowSize.x*EncounterLayout.SceneEnd.x*0.01),static_cast<int>(windowSize.y*EncounterLayout.SceneEnd.y*0.01)};
                //SDL_RenderFillRect(renderer(),&sceneWindow);

                switch(eTracker.activeEncounter->scenes[eTracker.szene].background)//todo make separate once switch bigger
                {
                    case EnvironmentType::DenseForest:
                    {
                        renderFromSpritesheet(sceneWindow, denseForestBG);
                        break;
                    }
                    case EnvironmentType::MonasteryPath:
                    {
                        renderFromSpritesheet(sceneWindow,monasteryPathBG);
                        break;
                    }
                    case EnvironmentType::Village:
                    {
                        renderFromSpritesheet(sceneWindow,village1);
                        break;
                    }
                    case EnvironmentType::Village2:
                    {
                        renderFromSpritesheet(sceneWindow,village2);
                        break;
                    }
                    case EnvironmentType::HeartApproach:
                    {
                        renderFromSpritesheet(sceneWindow,forestPathToHeartBG);
                        break;
                    }
                    case EnvironmentType::ForestHeart:
                    {
                        renderFromSpritesheet(sceneWindow,forestHeartBG);
                        break;
                    }case EnvironmentType::ForestClearing:
                    {
                        renderFromSpritesheet(sceneWindow,forestClearingBG);
                        break;
                    }
                    case EnvironmentType::HermitLodge:
                    {
                        renderFromSpritesheet(sceneWindow,forestHermitLodge);
                        break;
                    }
                    case EnvironmentType::ForestLake:
                    {
                        renderFromSpritesheet(sceneWindow,forestLakeBG);
                        break;
                    }
                    case EnvironmentType::HunterCamp:
                    {
                        renderFromSpritesheet(sceneWindow,hunterCamp);
                        break;
                    }
                    case EnvironmentType::OakPath:
                    {
                        renderFromSpritesheet(sceneWindow,oakPath);
                        break;
                    }
                    case EnvironmentType::WindmillOutskirts:
                    {
                        renderFromSpritesheet(sceneWindow,windmillOutskirts);
                        break;
                    }
                    case EnvironmentType::ForestOutskirts:
                    {
                        renderFromSpritesheet(sceneWindow,outskirtsPath);
                        break;
                    }
                    case EnvironmentType::MonasteryOutside:
                        renderFromSpritesheet(sceneWindow,monasteryApproachBG);
                        break;
                    case EnvironmentType::MonasteryGate:
                        renderFromSpritesheet(sceneWindow,monasteryGateBG);
                        break;
                    case EnvironmentType::MonasteryInterior:
                        renderFromSpritesheet(sceneWindow,monasteryInteriorBG);
                        break;
                    case EnvironmentType::Ravine:
                        renderFromSpritesheet(sceneWindow,ravineBG);
                        break;
                    case EnvironmentType::SheepTree:
                        renderFromSpritesheet(sceneWindow,sheep_treeBG);
                        break;


                    default:SDL_RenderFillRect(renderer(),&sceneWindow);
                }


                RenderSceneComposition(eTracker.activeEncounter->scenes[eTracker.szene].compositionVector,eTracker.activeEncounter->scenes[eTracker.szene].background);


                //Render Foreground //todo decouple from bg, if needed?
                switch(eTracker.activeEncounter->scenes[eTracker.szene].background)
                {
                    case EnvironmentType::DenseForest:
                    {
                        renderFromSpritesheet(sceneWindow, denseForestFG);
                        break;
                    }
                    case EnvironmentType::HeartApproach:
                    {
                        renderFromSpritesheet(sceneWindow, forestPathToHeartFG);
                        break;
                    }
                    default: break;
                }

                //Render Healthbar

                if(eTracker.activeEncounter->id == EncounterID::Combat_Encounter)
                {
                    RenderHealthbar(tempHealth);
                }


                //Render Text Field Background todo Find a Texture
                SDL_SetRenderDrawColor(renderer(),13,13,10,0);
                SDL_Rect txtField = {0,static_cast<int>(windowSize.y*EncounterLayout.DialogueBoxStart.y*0.01),
                                     static_cast<int>(windowSize.x*EncounterLayout.DialogueBoxEnd.x*0.01),static_cast<int>(windowSize.y*EncounterLayout.DialogueBoxEnd.y*0.01)};
                SDL_RenderFillRect(renderer(),&txtField);
                // fmt::println("Screensize: x {}, y {}", windowSize.x, windowSize.y);

                Texture * sceneText = textToTexture(eTracker.activeEncounter->scenes[eTracker.szene].sceneText);

                SDL_Rect DialogueMainField = {static_cast<int>(windowSize.x*EncounterLayout.DialogueMainTextStart.x*0.01),static_cast<int>(windowSize.y*EncounterLayout.DialogueMainTextStart.y*0.01),
                                              static_cast<int>(windowSize.x*EncounterLayout.DialogueMainTextEnd.x*0.01),static_cast<int>(windowSize.y*EncounterLayout.DialogueMainTextEnd.y*0.01)};

                renderText(DialogueMainField,sceneText);
                SDL_DestroyTexture(sceneText); //prevent leak
                sceneText= nullptr;

                RenderSidebar();
                RenderTurnButton(false);
                //renderDicerollAnimation(ske);


                std::vector<SDL_Rect> OptionVector= {};


                switch (eTracker.diaPhase) {
                    case DialoguePhase::Scene:
                        if(eTracker.bShowPreviousDicerolls)
                        {
                            renderDicerollAnimation(ske); //TODO check for problems/missing flase-setters
                        }
                        if(!eTracker.alreadyDisplayedText) {


                            std::cout << eTracker.activeEncounter->scenes[eTracker.szene].sceneText << std::endl;
                            std::cout.flush();



                            for (const SceneOption &o: eTracker.activeEncounter->scenes[eTracker.szene].options) {


                                if (o.isSkillCheck) {
                                    fmt::println("[{}] {}", StatToString(o.skill), o.text);
                                    std::cout.flush();

                                } else {
                                    fmt::println("{}", o.text);
                                    std::cout.flush();


                                }
                            }
                            eTracker.alreadyDisplayedText = true;
                        }
                        for (const SceneOption &o: eTracker.activeEncounter->scenes[eTracker.szene].options) {
                            //TODO requirements
                            bool bMeetsCriteria = true;
                            if(o.bHasRequirements)
                            {

                                //loop over all requirements and check if fulfilled
                                for(const std::tuple<RequirementFlags, int>& req: o.requirements)
                                {
                                    if(!bOptionRequirementMet(req))
                                       bMeetsCriteria = false;
                                }

                            }

                            if(bMeetsCriteria)
                            {
                                OptionVector.push_back({static_cast<int>((EncounterLayout.DialogueMainTextStart.x*0.01*windowSize.x)) ,
                                                        static_cast<int>((EncounterLayout.DialogueMainTextEnd.y*0.01+OptionVector.size()*EncounterLayout.DialogueOptionFieldScale.y*0.01)*windowSize.y),
                                                        static_cast<int>((EncounterLayout.DialogueMainTextEnd.x*0.01*windowSize.x)),
                                                        static_cast<int>(EncounterLayout.DialogueOptionFieldScale.y*0.01*windowSize.y)});
                                Texture * optionText;
                                //renderText(DialogueMainField,optionText);



                                if (o.isSkillCheck) {
                                    String fullOptionText = "["+StatToString(o.skill)+ "] " + o.text;
                                    optionText = textToTexture(fullOptionText.c_str());
                                    //fmt::println("[{}] {}", StatToString(o.skill), o.text);
                                    //std::cout.flush();

                                } else {
                                    optionText = textToTexture(o.text);
                                    //fmt::println("{}", o.text);
                                    //std::cout.flush();

                                }

                                if(IsMouseInsideRect(OptionVector.back(),mouseOverX,mouseOverY))
                                {

                                    renderText(OptionVector.back(),optionText, 10);
                                }
                                else
                                {

                                    renderText(OptionVector.back(),optionText,7);
                                }




                                SDL_DestroyTexture(optionText); //prevent leak
                                optionText= nullptr;
                            }
                            else
                            {
                                fmt::println("dropped option");
                            }


                        }
                        break;
                    case DialoguePhase::DieRoll:
                        if(!eTracker.alreadyDisplayedText) {
                            renderDicerollAnimation(ske);

                            //TODO MAIN TEXT - "You failed etc..."

                            if(ske.getSuccesses() >= ske.getDifficulty()) {
                                eTracker.diaPhase = DialoguePhase::Scene; //TODO MOVE TO UPDATE?
                            }else
                            {

                                //eTracker.alreadyDisplayedText = true;



                                OptionVector.push_back({static_cast<int>((EncounterLayout.DialogueMainTextStart.x*0.01*windowSize.x)) ,
                                                        static_cast<int>((EncounterLayout.DialogueMainTextEnd.y*0.01)*windowSize.y),
                                                        static_cast<int>((EncounterLayout.DialogueMainTextEnd.x*0.01*windowSize.x)),
                                                        static_cast<int>(EncounterLayout.DialogueOptionFieldScale.y*0.01*windowSize.y)});
                                OptionVector.push_back({static_cast<int>((EncounterLayout.DialogueMainTextStart.x*0.01*windowSize.x)) ,
                                                        static_cast<int>((EncounterLayout.DialogueMainTextEnd.y*0.01+EncounterLayout.DialogueOptionFieldScale.y*0.01)*windowSize.y),
                                                        static_cast<int>((EncounterLayout.DialogueMainTextEnd.x*0.01*windowSize.x)),
                                                        static_cast<int>(EncounterLayout.DialogueOptionFieldScale.y*0.01*windowSize.y)});
                                Texture * optionTextYes;
                                Texture * optionTextNo;
                                Texture * optionText;

                                optionText = textToTexture(("You failed a Difficulty "+ std::to_string(ske.getDifficulty()) +" check. Spend 1 Will Point to add one more dice?").c_str());
                                SDL_SetRenderDrawColor(renderer(),13,13,10,0);
                                SDL_RenderFillRect(renderer(),&txtField);

                                renderText(DialogueMainField,optionText);

                                optionTextYes = textToTexture("Yes. (-1 WP)");
                                optionTextNo = textToTexture("No.");




                                if(IsMouseInsideRect(OptionVector[0],mouseOverX,mouseOverY))
                                {
                                    SDL_SetRenderDrawColor(renderer(),0,255,0,0);
                                    SDL_RenderFillRect(renderer(),&OptionVector[0]);
                                    renderText(OptionVector[0],optionTextYes, 10);
                                }
                                else
                                {
                                    SDL_SetRenderDrawColor(renderer(),0,0,200,0);
                                    SDL_RenderFillRect(renderer(),&OptionVector[0]);
                                    renderText(OptionVector[0],optionTextYes,7);
                                }
                                if(IsMouseInsideRect(OptionVector[1],mouseOverX,mouseOverY))
                                {
                                    SDL_SetRenderDrawColor(renderer(),255,0,0,0);
                                    SDL_RenderFillRect(renderer(),&OptionVector[1]);
                                    renderText(OptionVector[1],optionTextNo, 10);
                                }
                                else
                                {
                                    SDL_SetRenderDrawColor(renderer(),0,0,200,0);
                                    SDL_RenderFillRect(renderer(),&OptionVector[1]);
                                    renderText(OptionVector[1],optionTextNo,7);
                                }



                                //fmt::println("OptionVector size {}", OptionVector.size());
                                SDL_DestroyTexture(optionTextYes); //prevent leak
                                optionTextYes= nullptr;
                                SDL_DestroyTexture(optionTextNo); //prevent leak
                                optionTextNo= nullptr;
                                SDL_DestroyTexture(optionText); //prevent leak
                                optionText= nullptr;





                            }
                        }
                        //todo if fail render question
                        break;
                    case DialoguePhase::FateReroll:
                        if(!eTracker.alreadyDisplayedText) {
                            renderFateDieAnimation(ske);
                            renderDicerollAnimation(ske);
                            eTracker.diaPhase = DialoguePhase::Scene;
                            //todo exit after roll result? do we want to allow the spending of all wp in one check?

                        }

                        break;

                }
            }


            // SDL_RenderPresent( renderer() );



        }
        if(bInInventory)
        {
            RenderInventory();
        }
        if(bInJournal)
        {
            RenderJournal();
        }

    }




    void BeasthoodState::renderFromSpritesheet(int targetX, int targetY, int targetW, int targetH, SDL_Texture *t,
                                               const Rect *clip, double angle,
                                               SDL_Point *center, SDL_RendererFlip flip, bool useClipsize) {
        SDL_Rect renderQuad = {targetX, targetY, targetW, targetH};

        if (clip != nullptr && useClipsize) {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        SDL_RenderCopyEx(renderer(), t, clip, &renderQuad, angle, center, flip);
    }

//Version using a SDL_Rect to pull values from. Added for utility and because everything should have a Rect
    void BeasthoodState::renderFromSpritesheet(Rect values, SDL_Texture *t, SDL_Rect *clip, double angle, SDL_Point *center,
                                               SDL_RendererFlip flip, bool useClipSize) {
        SDL_Rect renderQuad = {values.x, values.y, values.w, values.h};

        if (clip != nullptr && useClipSize) {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        SDL_RenderCopyEx(renderer(), t, clip, &renderQuad, angle, center, flip);
    }

//result should be saved in a texture related to a object within MortalFlawState.
// Surface Width/Height should match player width/height otherwise texture needs to be scaled.
    Texture *BeasthoodState::loadFromFile(const std::string &path) {

        Texture *newTexture = nullptr;
        Surface *loadedSurface = IMG_Load(path.c_str());

        if (loadedSurface == nullptr) {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        } else {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

            newTexture = SDL_CreateTextureFromSurface(renderer(), loadedSurface);
            if (!newTexture) {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            }

            SDL_FreeSurface(loadedSurface);
        }

        return newTexture;
    }

//outputs a texture of the input text. Should be saved in a texture *
    Texture *BeasthoodState::textToTexture(const char *text) {

        //Point windowSize;
        //SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);

        Texture *newTexture = nullptr;

        Surface *surf = TTF_RenderUTF8_Blended_Wrapped(_font, text, white, windowSize.x - 2 * _p.x);
        newTexture = SDL_CreateTextureFromSurface(renderer(), surf);
        if (!newTexture) {
            printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(surf);

        return newTexture;
    }

//renders text and adds a shadow as in intro state
    void BeasthoodState::renderText(Rect values, SDL_Texture *t) {

        u32 fmt;
        int access;
        SDL_QueryTexture(t, &fmt, &access, &_blendedTextSize.x, &_blendedTextSize.y);

        SDL_SetTextureColorMod(t, outlineColor.r, outlineColor.g, outlineColor.b);
        for (const Point &offset: HSNR64::ShadowOffset::Rhombus) {
            const Rect dst_rect = Rect{values.x, values.y + _blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y} + offset;
            SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);
        }
        const Color &color = HSNR64::Palette(_colorIndex);
        SDL_SetTextureColorMod(t, color.r, color.g, color.b);
        const Rect dst_rect = {values.x, values.y +_blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y};
        SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);

    }
    //renders text and adds a shadow as in intro state, with selectable color index
    void BeasthoodState::renderText(Rect values, SDL_Texture *t, int colorIndex){
        u32 fmt;
        int access;
        SDL_QueryTexture(t, &fmt, &access, &_blendedTextSize.x, &_blendedTextSize.y);

        SDL_SetTextureColorMod(t, outlineColor.r, outlineColor.g, outlineColor.b);
        for (const Point &offset: HSNR64::ShadowOffset::Rhombus) {
            const Rect dst_rect = Rect{values.x, values.y + _blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y} + offset;
            SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);
        }
        const Color &color = HSNR64::Palette(colorIndex);
        SDL_SetTextureColorMod(t, color.r, color.g, color.b);
        const Rect dst_rect = {values.x, values.y +_blendedTextSize.y, _blendedTextSize.x, _blendedTextSize.y};
        SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);

    }

    void BeasthoodState::PopulateEventManager(){
        Encounter FirstEncounter{
                EncounterID::Forest_Thievery, // Replace with the actual EncounterID from your global enums
                EncounterTypeID::Tutorial,  // Replace with the appropriate type from your global enums
                {
                        {
                                "Scene 0 \n This is a test scene. You may pay in blood to pass, or try convincing whatever is in front of you.",
                                EnvironmentType::Village,
                                {
                                        {
                                                "MoveTo 1 - Pay in blood",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 3}},
                                                {},
                                                1,
                                                -1,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                                "MoveTo 2 - Skillcheck",
                                                true,
                                                StatNames::FIGHT,
                                                2,
                                                {{ExecuteFlags::RegainSan, 1}},
                                                {{ExecuteFlags::Wound, 3}},
                                                2,
                                                3,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                            "Test Scene assets- needs MSQ",
                                            false,
                                            StatNames::FIGHT,
                                            0,
                                            {{ExecuteFlags::Wound, 3}},
                                            {},
                                            4,
                                            -1,
                                            {}, // rewardItemIDs
                                            {},  // failureItemIDs
                                            {{RequirementFlags::hasQuest,1}},
                                            true
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterAtBottomMain},
                                        {SceneCompositionEntities::Wolf,SceneCompositionSlots::NPCAtBottomMain}

                                }
                        },
                        {
                                "Scene 1",
                                EnvironmentType::MonasteryPath,
                                {

                                        {
                                                "Leave",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                255,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                                "Retry",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                0,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain}
                                }
                        },
                        {
                                "Scene 2 - You succeeded",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Leave",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                255,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                                "Retry",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                0,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain}
                                }
                        },
                        {
                                "Scene 3 - You failed and injured yourself",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Retry",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                0,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Wolf,SceneCompositionSlots::Enemy_2},
                                        {SceneCompositionEntities::Werewolf,SceneCompositionSlots::CharacterFront},
                                        {SceneCompositionEntities::Wolf,SceneCompositionSlots::Enemy_3}
                                }
                        },
                        {
                                "Scene 4 -village 1",
                                EnvironmentType::Village,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                5,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Villager2,SceneCompositionSlots::CharacterFront}

                                }
                        },
                        {
                                "Scene 5 -village 2",
                                EnvironmentType::Village2,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                6,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::VillagerCouple,SceneCompositionSlots::EnemyMain}

                                }
                        },
                        {
                                "Scene Windmills",
                                EnvironmentType::WindmillOutskirts,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                7,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Villager1,SceneCompositionSlots::Enemy_2}

                                }
                        },
                        {
                                "HunterCamp",
                                EnvironmentType::HunterCamp,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                8,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Hunter,SceneCompositionSlots::EnemyMain}

                                }
                        },
                        {
                                "OakPAth",
                                EnvironmentType::OakPath,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                9,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Hunter,SceneCompositionSlots::Enemy_2}

                                }
                        },
                        {
                                "Forest Outskirts",
                                EnvironmentType::ForestOutskirts,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                10,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain}

                                }
                        },
                        {
                                "Clearing",
                                EnvironmentType::ForestClearing,
                                {

                                        {
                                                "Pick up the skull - later a will/occult check?",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::GainItem,1}},
                                                {},
                                                11,
                                                255,
                                                {ItemID::RitualSkull}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::RitualSkullOverlay,SceneCompositionSlots::OverlayMainPoint}

                                }
                        },
                        {
                                "Lake",
                                EnvironmentType::ForestLake,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                12,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterAtBottomMain},
                                        {SceneCompositionEntities::Bear,SceneCompositionSlots::NPCAtBottomMain}

                                }
                        },
                        {
                                "Heart Approach",
                                EnvironmentType::HeartApproach,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::Wound, 1}},
                                                {},
                                                13,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterAtBottomMain},
                                        {SceneCompositionEntities::Wolf,SceneCompositionSlots::NPCAtBottomMain}

                                }
                        },
                        {
                                "Hermit",
                                EnvironmentType::HermitLodge,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::StartQuest, 6}},
                                                {},
                                                14,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterFront},
                                        {SceneCompositionEntities::Hermit,SceneCompositionSlots::EnemyMain}

                                }
                        },
                        {
                                "Heart of the Forest",
                                EnvironmentType::ForestHeart,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::AdvanceQuestStage, 6070}}, //set quest 6 to 70%
                                                {},
                                                15,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character, SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Werewolf, SceneCompositionSlots::CharacterFront}

                                }
                        },
                        {
                            "Ravine",
                            EnvironmentType::Ravine,
                            {

                                {
                                                        "Continue",
                                                        false,
                                                        StatNames::FIGHT,
                                                        0,
                                                        {{ExecuteFlags::AdvanceQuestStage, 6070}}, //set quest 6 to 70%
                                                        {},
                                                        16,
                                                        255,
                                                        {}, // rewardItemIDs
                                                        {}  // failureItemIDs
                                }
                                },
                                {
                                                {SceneCompositionEntities::Character,
                                                 SceneCompositionSlots::CharacterMain},
                                                {SceneCompositionEntities::SpearSkeleton,
                                                 SceneCompositionSlots::CharacterFront}
                                        }

                        },
                        {
                                "Shepherd and Bandit",
                                EnvironmentType::SheepTree,
                                {

                                        {
                                                "Continue",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::AdvanceQuestStage, 6070}}, //set quest 6 to 70%
                                                {},
                                                255,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,
                                         SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Mercenary,
                                         SceneCompositionSlots::EnemyMain}
                                }

                        }
                },
                DialoguePhase::Scene // Starting dialogue phase
        };
        encounterManager.addEncounter(FirstEncounter.id,FirstEncounter);
        encounterManager.addEncounter(monasteryMain.id,monasteryMain);
        encounterManager.addEncounter(testingCombat.id,testingCombat);

        //  encounterManager.addEncounter(CombatEncounter.id,CombatEncounter);
    }

    void BeasthoodState::PopulateMonsterManager(){
        Monster mon1("Werwolf",
                     LocationID::UNASSIGNED,
                     MonsterID::Werewolf,
                     MonsterType::Beast,
                     MovementType::Fast,
                     10,
                     4,
                     -3,
                     2,
                     -2,
                     3,
                     AbilityID::WerwolfCorruptionEffects,
                     1);
        monsterManager.addMonster(mon1);
        mon1 = {"Wolf",
                LocationID::UNASSIGNED,
                MonsterID::Wolf,
                MonsterType::Beast,
                MovementType::Stalking,
                3,
                2,
                0,
                0,
                -1,
                2,
                AbilityID::WolfPackAttack,
                6};
        monsterManager.addMonster(mon1);
        mon1 = {"Bear",
                LocationID::UNASSIGNED,
                MonsterID::Bear,
                MonsterType::Beast,
                MovementType::Stalking,
                4,
                1,
                -1,
                2,
                -1,
                3,
                AbilityID::NONE,
                3};
        monsterManager.addMonster(mon1);
    }


    void BeasthoodState::PopulateLocationEvents(){

        /// TODO add more events
        // locationManager.GetItem(LocationID::Forest)->related_events.push_back(EncounterID::Combat_Encounter);
        locationManager.GetItem(LocationID::Forest)->related_events.push_back(EncounterID::Forest_Thievery);
        locationManager.GetItem(LocationID::Monastery)->related_events.push_back(EncounterID::MonasteryMain); //TODO TESTING ENCOUNTERS
        locationManager.GetItem(LocationID::Smith)->related_events.push_back(EncounterID::Testing_Combat);

    }


    //input character sheets here, maybe add intro choices to modify these TODO
    //examples on how to fill a character sheet here
    void BeasthoodState::PopulateBlueprints() {

        std::vector<Item *> temp;
        temp.push_back(itemManager.GetItem(ItemID::Halberd));
        blueprintManager.AddBlueprint(std::make_shared<CharacterBlueprint>(
                "Landsknecht",
                8, 6,
                Stats(3, 2, 4, 3, 0, 1),
                Stats(5, 4, 6, 4, 3, 3),
                2,
                abilityManager.GetAbility(AbilityID::ReduceStaminaLoss),
                "Gain a fate point after defeating a boss",
                temp
        ));

        blueprintManager.AddBlueprint(std::make_shared<CharacterBlueprint>(
                "Monk",
                5, 8,
                Stats(4, 2, 1, 6, 6, 1),
                Stats(4, 5, 4, 6, 6, 4),
                3,
                abilityManager.GetAbility(AbilityID::DrawExtraItem),
                "Gain a fate point after casting 3 spells in a turn",
                temp
        ));
    }

    bool BeasthoodState::IsMouseInsideRect(const SDL_Rect &rect, int mouseX, int mouseY) {
        return mouseX >= rect.x && mouseX < (rect.x + rect.w) &&
               mouseY >= rect.y && mouseY < (rect.y + rect.h);
    }

    //todo placeholder functions
    void BeasthoodState::renderDicerollAnimation( SkillChallengeEngine& skillCheck)
    {
        SDL_Rect targetRect {static_cast<int>(EncounterLayout.DiceFieldStart.x*windowSize.x*0.01),
                             static_cast<int>(EncounterLayout.DiceFieldStart.y*0.01*windowSize.y),
                             static_cast<int>(5*windowSize.x*0.01),static_cast<int>(5*windowSize.x*0.01)};
        SDL_Rect srcRect {0,0,128,128};
        for(unsigned char currentRoll : skillCheck.currentRolls)
        {
            targetRect.x += static_cast<int>(5*windowSize.x*0.01);
            switch (currentRoll) {
                case 1:SDL_RenderCopy(renderer(),dice1,&srcRect,&targetRect);
                    break;
                case 2:SDL_RenderCopy(renderer(),dice2,&srcRect,&targetRect);
                    break;
                case 3:SDL_RenderCopy(renderer(),dice3,&srcRect,&targetRect);
                    break;
                case 4:SDL_RenderCopy(renderer(),dice4,&srcRect,&targetRect);
                    break;
                case 5:SDL_RenderCopy(renderer(),dice5,&srcRect,&targetRect);
                    break;
                case 6:SDL_RenderCopy(renderer(),dice6,&srcRect,&targetRect);
                    break;
                default: fmt::println("impossible dice result");
                    break; //should be impossible

            }

        }



        //fmt::println("rendering DICE");

    }
    void BeasthoodState::renderFateDieAnimation(const SkillChallengeEngine& ske)
    {
        fmt::println("Will fate bend to mortal will?");
        //renderDicerollAnimation(ske);
        for(uint8_t roll : ske.currentRolls)
        {
            fmt::print("{} ", roll);
        }
        fmt::println("{} Successes for Difficulty {}.", ske.getSuccesses(), ske.getDifficulty());
        if (ske.getSuccesses() >= ske.getDifficulty()) //todo you can get true from the skillcheck being called-> can save result in WS!
        {
            fmt::println("Passed!");
        }
        else
        {
            fmt::println("No matter your struggle: You failed.");
        }
    }

    std::string BeasthoodState::StatToString(StatNames stat)
    {
        switch (stat) {

            case StatNames::FIGHT:
                return "Fight";
                // return currentCharacter.Combat;
            case StatNames::SNEAK:
                return "Sneak";
                // return currentCharacter.Stealth;
            case StatNames::SPEED:
                return "Speed";
                //return currentCharacter.Speech;
            case StatNames::WILLPOWER:
                return "Willpower";
            case StatNames::OCCULT:
                return "Knowledge";
            case StatNames::FAITH:
                return "Luck";

        }
    }
    void BeasthoodState::UpdateCombatEncounter(){
        encounterManager.removeEncounter(EncounterID::Combat_Encounter);
        SceneCompositionEntities currentEnemy;
        //matches the monster ID to the correspondig SCE and gets the correct texture this way
        switch(cTracker.monID) {
            case MonsterID::Wolf:
                currentEnemy = SceneCompositionEntities::Wolf;
                break;
            case MonsterID::Werewolf:
                currentEnemy = SceneCompositionEntities::Werewolf;
                break;
            case MonsterID::Bear:
                currentEnemy = SceneCompositionEntities::Bear;
                break;
            default:
                currentEnemy = SceneCompositionEntities::Character;

                //add more as needed
        }
        Encounter CombatEncounter{
                EncounterID::Combat_Encounter,
                EncounterTypeID::Tutorial,  // Replace
                {
                        {
                                "You are confronted by a Monster. Its presence chills you to the bone. Do you try to evade it or stand your ground?",
                                EnvironmentType::DenseForest,
                                {
                                        {
                                                "Evade the monster (SNEAK)" ,
                                                true,
                                                StatNames::SNEAK,
                                                cTracker.awareness,
                                                {},
                                                {},
                                                5,
                                                7,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                                "Face the monster head-on. (FIGHT)",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                1,
                                                1,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {currentEnemy,SceneCompositionSlots::EnemyMain}

                                }
                        },
                        {
                                "The Monsters nightmarish visage fills your mind with dread. You must summon your will to avoid breaking down.",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Make a Willpower check",
                                                true,
                                                StatNames::WILLPOWER,
                                                1,
                                                {},
                                                {{ExecuteFlags::SanityLoss,cTracker.horrorDamage}},
                                                2,
                                                8,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {currentEnemy,SceneCompositionSlots::CharacterFront}
                                }
                        },
                        {
                                "With a surge of courage, you attempt to slay the Monster. Can you overpower the beast?",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Make a Fight check",
                                                true,
                                                StatNames::FIGHT,
                                                cTracker.toughness,
                                                {},
                                                {{ExecuteFlags::Wound,cTracker.combatDamage}},
                                                4,
                                                3,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                                "Shoot that sucker.",
                                                false,
                                                StatNames::FIGHT,
                                                cTracker.toughness,
                                                {{ExecuteFlags::UnloadLeadBullet,1}},
                                                {},
                                                4,
                                                3,
                                                {}, // rewardItemIDs
                                                {},  // failureItemIDs
                                                {{RequirementFlags::LeadBulletLoaded,1}},
                                                true
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {currentEnemy,SceneCompositionSlots::CharacterFront}
                                }
                        },
                        {
                                "<failed check> Having failed your attempt the Monster takes advantage and strikes you with brutal ferocity.",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Continue fighting (Retry Combat Check)",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                2,
                                                2,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                                "Attempt to Escape (SNEAK)",
                                                true,
                                                StatNames::SNEAK,
                                                cTracker.awareness,
                                                {},
                                                {{ExecuteFlags::Wound,cTracker.combatDamage}},
                                                5,
                                                3,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {currentEnemy,SceneCompositionSlots::CharacterFront}
                                }
                        },
                        {
                                "You defeat the Monster, its body crumpling to the ground. The threat has been eliminated, but at what cost?",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Leave the area.",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {{ExecuteFlags::FinishedCombatWIN,0}},
                                                {},
                                                255,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                      //  {SceneCompositionEntities::Wolf,SceneCompositionSlots::Enemy_2},
                                        //{SceneCompositionEntities::Wolf,SceneCompositionSlots::Enemy_3}
                                }
                        },
                        {
                                "<STEALTH check success> You manage to get away from the Monster, either through cunning or sheer luck. For now, you are safe.",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Move on.",
                                                false,
                                                StatNames::NONE,
                                                0,
                                                {{ExecuteFlags::FinishedCombatLOSS,0}},
                                                {},
                                                255,
                                                255,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain}
                                }
                        },
                        {
                                "<WILLPOWER check failed> Both mind and body are ravaged as the Monster spots you in your attempted cowardice!",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Steel yourself and fight (FIGHT)",
                                                false,
                                                StatNames::FIGHT,
                                                0,
                                                {},
                                                {},
                                                2,
                                                2,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        },
                                        {
                                                "Attempt to Escape again (SNEAK)",
                                                true,
                                                StatNames::SNEAK,
                                                cTracker.awareness,
                                                {},
                                                {{ExecuteFlags::Wound,cTracker.combatDamage}},
                                                5,
                                                3,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {currentEnemy,SceneCompositionSlots::CharacterFront},
                                }
                        },
                        {
                                "<STEALTH check failed> Failing to evade its gaze, you attempt to guard your mind from slipping into panic as the creatures horrifying form ravages your body!",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Steel yourself (Willpower Check)",
                                                true,
                                                StatNames::WILLPOWER,
                                                1,
                                                {{ExecuteFlags::Wound,cTracker.combatDamage}},
                                                {{ExecuteFlags::SanityLoss,cTracker.horrorDamage},{ExecuteFlags::Wound,cTracker.combatDamage}},
                                                3,
                                                6,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {currentEnemy,SceneCompositionSlots::CharacterFront}
                                }
                        },
                        {
                                "<WILLPOWER check failed> Your mind writhes in abject horror as the creatures visage meets your gaze.",
                                EnvironmentType::DenseForest,
                                {

                                        {
                                                "Gather your Courage and continue",
                                                false,
                                                StatNames::WILLPOWER,
                                                0,
                                                {},
                                                {},
                                                2,
                                                2,
                                                {}, // rewardItemIDs
                                                {}  // failureItemIDs
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {currentEnemy,SceneCompositionSlots::CharacterFront}
                                }
                        }

                },
                DialoguePhase::Scene // Starting dialogue phase
        };
        encounterManager.addEncounter(EncounterID::Combat_Encounter,CombatEncounter);
    }

    bool BeasthoodState::bOptionRequirementMet(std::tuple<RequirementFlags, int> requirement)
    {

        switch (get<0>(requirement)) {
            case RequirementFlags::stamina:
                if(currentCharacter->GetStamina()>=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::sanity:
                if(currentCharacter->GetSanity()>=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::sneak:
                if(currentCharacter->GetCurrentStats().GetStat(SNEAK) >=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::speed:
                if(currentCharacter->GetCurrentStats().GetStat(SPEED) >=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::occult:
                if(currentCharacter->GetCurrentStats().GetStat(OCCULT) >=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::faith:
                if(currentCharacter->GetCurrentStats().GetStat(FAITH) >=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::fight:
                if(currentCharacter->GetCurrentStats().GetStat(FIGHT) >=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::willpower:
                if(currentCharacter->GetCurrentStats().GetStat(WILLPOWER) >=get<1>(requirement))
                {return true;}
                else
                {return false;}
            case RequirementFlags::isPhysicallyWounded:
                if(currentCharacter->GetStamina() < currentCharacter->GetBaseStamina())
                {return true;}
                else
                {return false;}
            case RequirementFlags::isMentallyWounded:
                if(currentCharacter->GetSanity() < currentCharacter->GetBaseSanity())
                {return true;}
                else
                {return false;}
            case RequirementFlags::hasQuestOnStage:

                if(Questlog.getQuestStage(get<1>(requirement)/1000) == get<1>(requirement) % 1000)
                {return true;}
                else
                {
                    int qID = get<1>(requirement)/1000;
                    int qStage = get<1>(requirement) % 1000;
                    fmt::println("Quest requirement not passed: Req: {}", get<1>(requirement));
                    fmt::println("Needed QuestID: {}, Stage: {}",qID,qStage);
                    return false;}
            case RequirementFlags::notOnQuest:
                if(Questlog.bHasQuest(get<1>(requirement) ))
                {return false;}
                else
                { return true;}
            case RequirementFlags::hasQuest:
                if(Questlog.bHasQuest(get<1>(requirement) ))
                {return true;}
                else
                { return false;}
            case RequirementFlags::notOnStage:

                if(Questlog.getQuestStage(get<1>(requirement)/1000) == get<1>(requirement) % 1000)
                {return false;}
                else
                {
                    int qID = get<1>(requirement)/1000;
                    int qStage = get<1>(requirement) % 1000;
                    return true;}
            case RequirementFlags::SilverBulletLoaded:
                return ((currentCharacter->GetEquipment().first && currentCharacter->GetEquipment().first->GetItemID()==ItemID::LoadedGunSilver) ||
                (currentCharacter->GetEquipment().second && currentCharacter->GetEquipment().second->GetItemID()==ItemID::LoadedGunSilver));

            case RequirementFlags::LeadBulletLoaded:
                return ((currentCharacter->GetEquipment().first && currentCharacter->GetEquipment().first->GetItemID()==ItemID::LoadedGunLead) ||
                        (currentCharacter->GetEquipment().second && currentCharacter->GetEquipment().second->GetItemID()==ItemID::LoadedGunLead));

            default:
                return false; //TODO Item and Quest not yet implemented, may need more complex approach

        }

    }
    void BeasthoodState::RenderJournal()
    {
        SDL_Rect QL_Rect { static_cast<int>(QuestlogLayout.QL_Layout.x*0.01*windowSize.x),
                           static_cast<int>(QuestlogLayout.QL_Layout.y*0.01*windowSize.x),
                           static_cast<int>(QuestlogLayout.QL_Layout.w*0.01*windowSize.x),
                           static_cast<int>(QuestlogLayout.QL_Layout.h*0.01*windowSize.x)
        };
        SDL_SetRenderDrawColor(renderer(),5,5,5,0);
        SDL_RenderFillRect(renderer(),&QL_Rect);
        Texture * QuestTitle;
        Texture * QuestDescription;
        Texture * QuestStage;
        SDL_Rect TargetRect {static_cast<int>(QuestlogLayout.QL_ContentStart.x*0.01*windowSize.x),
                             static_cast<int>(QuestlogLayout.QL_ContentStart.y*0.01*windowSize.x),
                             static_cast<int>(5*0.01*windowSize.x),
                             static_cast<int>(5*0.01*windowSize.x)
                             };
        for(Quest q: Questlog.activeQuests)
        {
            QuestTitle = textToTexture(q.questName.c_str());
            renderText(TargetRect,QuestTitle);
            TargetRect.y +=static_cast<int>(2*0.01*windowSize.x);
            QuestDescription = textToTexture(q.description.c_str());
            renderText(TargetRect,QuestDescription);
            TargetRect.y +=static_cast<int>(1.5*0.01*windowSize.x);

            for (std::pair<int, String> Stage : q.questStages) {
                if(Stage.first == q.currentQuestStage)
                    QuestStage= textToTexture(Stage.second.c_str());
            }
            if(!QuestStage)
            {
                QuestStage= textToTexture("ERROR - Undefined quest stage");
            }


            renderText(TargetRect,QuestStage);
            TargetRect.y +=static_cast<int>(1.5*0.01*windowSize.x);


        }

        SDL_DestroyTexture(QuestTitle);
        SDL_DestroyTexture(QuestStage);
        SDL_DestroyTexture(QuestDescription);
        QuestStage= nullptr;
        QuestDescription= nullptr;
        QuestTitle= nullptr;

    }
    void BeasthoodState::RenderHealthbar(float currentHealth)
    {
        //Render Combat Encounter specifics
        SDL_Rect HealthBG{
                static_cast<int>(EncounterLayout.HealthbarBorderStart.x*0.01*windowSize.x),
                static_cast<int>(EncounterLayout.HealthbarBorderStart.y*0.01*windowSize.y),
                static_cast<int>(EncounterLayout.HealthbarBorderScale.x*0.01*windowSize.x),
                static_cast<int>(EncounterLayout.HealthbarBorderScale.y*0.01*windowSize.y),

        };
        renderFromSpritesheet(HealthBG,healtbarBG);


        //SDL_SetRenderDrawColor(renderer(),200,10,10,0);
        SDL_Rect HealthBarVariablePart = {static_cast<int>(EncounterLayout.HealthBarStart.x*0.01*windowSize.x),
                                          static_cast<int>(EncounterLayout.HealthBarStart.y*0.01*windowSize.y),
                                          static_cast<int>(EncounterLayout.HealthBarScale.x*0.01*windowSize.x*currentHealth),
                                          static_cast<int>(EncounterLayout.HealthBarScale.y*0.01*windowSize.y)
        };
        SDL_Rect HealthbarRedPart {
            0,0,
            static_cast<int>(1152*currentHealth),
            8
        };
        SDL_RenderCopy(renderer(),healtbarRed,&HealthbarRedPart,&HealthBarVariablePart);
        //SDL_RenderFillRect(renderer(),&HealthBarVariablePart);
        SDL_Rect HealthbarEdge {
                static_cast<int>(EncounterLayout.HealthbarBorderStart.x*0.01*windowSize.x + EncounterLayout.HealthBarScale.x*0.01*windowSize.x*currentHealth),
                static_cast<int>(EncounterLayout.HealthbarBorderStart.y*0.01*windowSize.y),
                static_cast<int>(0.01*windowSize.x*1),
                static_cast<int>(EncounterLayout.HealthbarBorderScale.y*0.01*windowSize.y)

        };
        if (currentHealth<1.)
        {
//            SDL_SetRenderDrawColor(renderer(),0,0,0,0);
//            SDL_RenderFillRect(renderer(),&HealthbarEdge);
            renderFromSpritesheet(HealthbarEdge,healthbarEdge);
        }

        TTF_SetFontSize(_font,static_cast<int>(20*windowSize.y/1080));

        Texture * enemyName = textToTexture("Wolf"); //Todo find good way to pass name of enemy
        SDL_Rect TextTarget {
            static_cast<int>(EncounterLayout.HealthBarTitleStart.x*0.01*windowSize.x),
            static_cast<int>(EncounterLayout.HealthBarTitleStart.y*0.01*windowSize.y),
            static_cast<int>(EncounterLayout.HealthbarTitleScale.x*0.01*windowSize.x),
                static_cast<int>(EncounterLayout.HealthbarTitleScale.y*0.01*windowSize.y)


        };
        renderText(TextTarget,enemyName);
        TTF_SetFontSize(_font,static_cast<int>(15*windowSize.y/1080));


    }
    void BeasthoodState::CleanupMonsterTextures() {
        for (auto& pair : monsterIDtoTextureMap) {
            SDL_DestroyTexture(pair.second);
        }
        monsterIDtoTextureMap.clear();
    }


}