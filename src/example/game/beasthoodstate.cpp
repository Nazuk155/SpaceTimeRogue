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
#include "ReduceStaminaLoss_ability.h"
#include "DrawExtraItem_ability.h"
#include "item_manager.h"
#include "item.h"
#include "character.h"
#include "encounter.h"
#include "skillCheckEngine.h"
#include "layout.h"


// TODO item class as well as character ability and fate refill then do events and event manager

namespace JanSordid::SDL_Example {
    struct {

        InventoryIcon Left {false,SidebarLayout.EquippedItemsStart.x,SidebarLayout.InventoryStart.y,7,7};

        InventoryIcon Right {false,SidebarLayout.EquippedItemsStart.x+SidebarLayout.InventoryScale.x-7,
                             SidebarLayout.InventoryStart.y,
                             7,7};

    }SidebarIcons; //todo move somwhwew



    void BeasthoodState::Init() {
        using std::string;

        Base::Init();

        if (!_font) {
            _font = TTF_OpenFont(BasePath "asset/font/RobotoSlab-Bold.ttf", (int) (10.0f * _game.scalingFactor()));
            TTF_SetFontHinting(_font, TTF_HINTING_LIGHT);
            if (!_font)
                print(stderr, "TTF_OpenFont failed: {}\n", TTF_GetError());
        }


        //Paths for Image Assets
        string forestLocationIconPath = BasePath "/src/example/game/Ressources/Image_assets/token_1.png";
        string playerMapIconPath = BasePath "/src/example/game/Ressources/Image_assets/Landsknecht.jpg";

        string playerMainSpritePath = BasePath "/src/example/game/Ressources/Image_assets/lk_sprite.png";

        string enemyWereWolfMainSpritePath = BasePath "/src/example/game/Ressources/Image_assets/entities/garou_sprite.png";
        string errorIMGPath = BasePath "/src/example/game/Ressources/Image_assets/entities/ERROR.png";

        string denseForestBGPath = BasePath "/src/example/game/Ressources/Image_assets/backgrounds/dense_forest_test.png";
        string denseForestFGPath = BasePath "/src/example/game/Ressources/Image_assets/foregrounds/dense_forest_test_fg.png";

        string endTurnButtonOnPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/clock_button_PLACEHOLDER.png";
        string endTurnButtonOffPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/clock_disabled_PLACEHOLDER.png";
        string endTurnButtonMouseoverPath = BasePath "/src/example/game/Ressources/Image_assets/buttons/clock_mouseover_PLACEHOLDER.png";

        //--------------- load textures from file
        forestLocationIconTexture = loadFromFile(forestLocationIconPath);
        playerMapIconTexture = loadFromFile(playerMapIconPath);
        playerMainSpite = loadFromFile(playerMainSpritePath);
        denseForestBG = loadFromFile(denseForestBGPath);
        denseForestFG = loadFromFile(denseForestFGPath);

        enemyWereWolfMainSprite = loadFromFile(enemyWereWolfMainSpritePath);
        errorIMG = loadFromFile(errorIMGPath);

        endTurnButtonOn = loadFromFile(endTurnButtonOnPath);
        endTurnButtonOff = loadFromFile(endTurnButtonOffPath);
        endTurnButtonMouseover = loadFromFile(endTurnButtonMouseoverPath);


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

        locationTextureMap[LocationID::Monastery].iconTexture = loadFromFile(forestLocationIconPath);
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
        Ability *reduceStaminaLoss = abilityManager.GetAbility(AbilityName::ReduceStaminaLoss);
        if (reduceStaminaLoss) {
            reduceStaminaLoss->Activate();
        }

        Ability *drawExtraItem = abilityManager.GetAbility(AbilityName::DrawExtraItem);
        if (drawExtraItem) {
            drawExtraItem->Activate();
        }




        // Create and add an ability
        auto staminaAbility = std::make_unique<ReduceStaminaLossAbility>();
        Ability *staminaAbilityPtr = staminaAbility.get();
        abilityManager.AddAbility(std::move(staminaAbility));

        // Create and add items
        auto sword = std::make_unique<Item>(ItemName::Halbert, ItemType::Weapon, "Halbert of Valor", 1);
        sword->SetStats({0, 0, 5, 0, 0, 0}); // Attack 10
        sword->SetAbility(staminaAbilityPtr); // Associate ability with item
        itemManager.AddItem(std::move(sword));

        // Access and use an item
        Item *item = itemManager.GetItem(ItemName::Halbert);
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
        std::cout << "Stats: " << Landsknecht.GetCurrentStats().GetStat(FIGHT);
        std::cout.flush();

        character1 = new Character(*landsknechtBlueprint);


        PopulateEventManager();
        PopulateLocationEvents();


        // CurrentEncounter = e;


       // dialoguePhase = DialoguePhase::Scene;
       // CurrentEncounter = FirstEncounter;
        character1->RefillFatePoints();
        currentCharacter = character1;

        inventoryScreen = InventoryScreen(currentCharacter);

        // get character into SKE
        ske.changeCharacter(currentCharacter);
        fmt::println("Fate available: {}",
                     character1->GetFatePoints()); //todo 0 fate dialogue makes no sense, prints options that should not be printed
        std::cout.flush();



    }

    void BeasthoodState::Destroy() {
        SDL_DestroyTexture(forestLocationIconTexture);
        SDL_DestroyTexture(playerMapIconTexture);
        SDL_DestroyTexture(playerMainSpite);
        SDL_DestroyTexture(denseForestBG);
        SDL_DestroyTexture(denseForestFG);
        SDL_DestroyTexture(errorIMG);

        SDL_DestroyTexture(endTurnButtonOff);
        SDL_DestroyTexture(endTurnButtonOn);
        SDL_DestroyTexture(endTurnButtonMouseover);

        SDL_DestroyTexture(enemyWereWolfMainSprite);

        for (auto e: locationTextureMap) {
            SDL_DestroyTexture(e.second.iconTexture);
            SDL_DestroyTexture(e.second.nameTexture);
        }

        forestLocationIconTexture = nullptr;
        playerMapIconTexture = nullptr;
        playerMainSpite = nullptr;
        denseForestBG = nullptr;
        denseForestFG= nullptr;
        enemyWereWolfMainSprite = nullptr;
        errorIMG = nullptr;

        endTurnButtonOff = nullptr;
        endTurnButtonMouseover = nullptr;
        endTurnButtonOn = nullptr;

        Base::Destroy();
    }

    bool BeasthoodState::HandleEvent(const Event &event) {

        if (event.type == SDL_MOUSEMOTION ) {
            //int mouseX, mouseY;
            SDL_GetMouseState(&mouseOverX, &mouseOverY);
            inventoryScreen.currentPage.MouseOver(mouseOverX,mouseOverY);
            SDL_Rect equipIcon= //Equip R
                    {
                            static_cast<int>((SidebarIcons.Right.position.x * windowSize.x*0.01)),
                            static_cast<int>(SidebarIcons.Right.position.y*windowSize.y*0.01),
                            static_cast<int>(SidebarIcons.Right.position.w*windowSize.y*0.01),
                            static_cast<int>(SidebarIcons.Right.position.h*windowSize.y*0.01),

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
                //SidebarIcons.Right.referencedItem = nullptr;
                //inventoryScreen.currentPage.MouseOverIcon = nullptr;
                bShowRightItemInfo = false;
            }
            equipIcon= //Equip L
                    {
                            static_cast<int>((SidebarIcons.Left.position.x * windowSize.x*0.01)),
                            static_cast<int>(SidebarIcons.Left.position.y*windowSize.y*0.01),
                            static_cast<int>(SidebarIcons.Left.position.w*windowSize.y*0.01),
                            static_cast<int>(SidebarIcons.Left.position.h*windowSize.y*0.01),

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
                //inventoryScreen.currentPage.MouseOverIcon = nullptr;
                //SidebarIcons.Left.referencedItem = nullptr;
            }
        }


        if(bInInventory) //todo expand functionality of inventory screen
        {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //int mouseX, mouseY;
                SDL_GetMouseState(&mouseOverX, &mouseOverY);
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    inventoryScreen.currentPage.Click(mouseOverX,mouseOverY,windowSize.x,windowSize.y);
                }
            }



            if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                        case SDLK_i:
                        bInInventory=!bInInventory;
                        break;
                }
            }

        }
        else {
            if (Phase == GamePhases::MOVEMENT) {
                if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            //endMovementConfirmation = true;
                            break;
                        case SDLK_i:
                            bInInventory=!bInInventory;
                            break;
                    }
                }
                if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                    //int mouseX, mouseY;
                    SDL_GetMouseState(&mouseOverX, &mouseOverY);
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
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
                                }, mouseOverX, mouseOverY)) { endMovementConfirmation = true; }
                    }

                    for (auto e: map.slots) {
                        if (IsMouseInsideRect(e.rect, mouseOverX, mouseOverY)) {
                            if (event.type == SDL_MOUSEMOTION) {
                                std::cout << "Mouse moved inside the rectangle.\n";
                                std::cout.flush();

                            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                                if (movementPoints > 0) {
                                    //mausklick reagiert nur wenn die location einen pfad zum aktuellen standort des characters hat
                                    for (auto c: e.connections) {
                                        //durchsuchen die aktiven connections der aktuellen node nach einam pfad zum character
                                        if (character1->GetCurrentLocationID() ==
                                            map.GetSlotByID(c.first)->location_id &&
                                            c.second == true) {
                                            std::cout << "Mouse clicked inside the rectangle.\n";
                                            //setzen location vom charakter und pos auf das aktuelle e da dies die node ist die gecklickt wurde
                                            moveTarget = e.location_id;
                                            playerMoved = true;


                                            std::cout.flush();
                                        }
                                    }

                                }


                            }
                        } else if (!IsMouseInsideRect(e.rect, mouseOverX, mouseOverY)) {
                            if (event.type == SDL_MOUSEMOTION) {
                                std::cout << "Mouse moved OUTSIDE the rectangle. " << e.id;
                                std::cout << " \n";
                                std::cout.flush();
                            }
                        }
                    }
                }
            }

            if (Phase == GamePhases::ENCOUNTER) {

                //Build Option Rects
                std::vector<SDL_Rect> OptionVector = {};
                for (const SceneOption &o: eTracker.activeEncounter->scenes[eTracker.szene].options) {
                    OptionVector.push_back(
                            {static_cast<int>((EncounterLayout.DialogueMainTextStart.x * 0.01 * windowSize.x)),
                             static_cast<int>((EncounterLayout.DialogueMainTextEnd.y * 0.01 +
                                               OptionVector.size() * EncounterLayout.DialogueOptionFieldScale.y *
                                               0.01) * windowSize.y),
                             static_cast<int>((EncounterLayout.DialogueMainTextEnd.x * 0.01 * windowSize.x)),
                             static_cast<int>((EncounterLayout.DialogueOptionFieldScale.y * 0.01) * windowSize.y)});
                }


                if (awaitingInput) {
                    if (event.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&mouseOverX, &mouseOverY); //TODO REDUNDANCY
                    }

                }

                if (!eTracker.chooseFateReroll && awaitingInput) {

                    if (event.type == SDL_MOUSEBUTTONDOWN) {

                        //int mouseX, mouseY;
                        SDL_Rect button;
                        SDL_GetMouseState(&mouseOverX, &mouseOverY);
                        fmt::println("MouseButtonDownn Mouse x= {}, Mouse Y = {}", mouseOverX, mouseOverY);
                        for (int i = 0; i < OptionVector.size(); i++) {
                            button = OptionVector[i];
                            fmt::println("Checking button {}", i);
                            fmt::println("x1 = {}, y1 = {}, x2 = {}, y2 = {}", button.x, button.y, button.w, button.h);
                            //SDL_SetRenderDrawColor(renderer(),255,0,0,0);
                            //SDL_RenderFillRect(renderer(),&button);
                            //SDL_Delay(150);

                            if (IsMouseInsideRect(button, mouseOverX, mouseOverY)) {
                                fmt::println("Clicked option {}", i);
                                eTracker.selectedOption = i;
                                awaitingInput = false;
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


                        }
                    }
                    if (event.type == SDL_MOUSEBUTTONDOWN) {

                        //int mouseX, mouseY;
                        SDL_Rect button;
                        SDL_GetMouseState(&mouseOverX, &mouseOverY);
                        fmt::println("MouseButtonDownn Mouse x= {}, Mouse Y = {}", mouseOverX, mouseOverY);
                        for (int i = 0; i < OptionVector.size(); i++) {
                            button = OptionVector[i];
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

        if (Phase == GamePhases::UPKEEP) {

            //place character somewhere if not placed
            if (character1->GetCurrentLocationID() == LocationID::UNASSIGNED) {
                character1->SetCurrentLocation(LocationID::Forest);
                character1->SetPos(locationManager.GetItem(LocationID::Forest)->GetMapSlot()->rect);
            }

            movementPoints = currentCharacter->GetCurrentStats().GetStat(SPEED);
            Phase = GamePhases::MOVEMENT;
        }


        if (Phase == GamePhases::MOVEMENT) {

            if (movementPoints > 0) {
                if (playerMoved) {
                    character1->SetCurrentLocation(moveTarget);
                    character1->SetPos(locationManager.GetItem(moveTarget)->GetMapSlot()->rect);
                    movementPoints--;
                }
            }
            if(movementPoints == 0 || endMovementConfirmation) {
                Phase = GamePhases::ENCOUNTER;
                endMovementConfirmation = false;
                awaitingInput = true;
                playerMoved = false;

                eTracker.encounterID = locationManager.GetEncounterID(currentCharacter->GetCurrentLocationID());
                eTracker.activeEncounter = encounterManager.getEncounter(eTracker.encounterID);
                eTracker.diaPhase = DialoguePhase::Scene;
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
                        //check if the input is viable within the options provided
                        if (eTracker.selectedOption <=
                            eTracker.activeEncounter->scenes[eTracker.szene].options.size()-1 && eTracker.selectedOption != -1) {
                            //resolve skillcheck if the option triggers one
                            if (eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].isSkillCheck) {
                                ske.setDifficulty(
                                        eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].difficulty);
                                ske.setModifier(0); //todo figure out what gives a modifier? Map Aura? Temporary Buffs?
                                ske.setSkill(eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].skill);
                                //if the skillcheck is not successful we ask if the player wants to spend fate
                                if (!ske.checkSkill()) {
                                    eTracker.diaPhase = DialoguePhase::DieRoll;
                                        awaitingInput = true;
                                        eTracker.chooseFateReroll = true;
                                        eTracker.alreadyDisplayedText = false;
                                }else{
                                    //if successfull we resolve the outcome and set the next scene as well as showing the rolls
                                    eTracker.diaPhase = DialoguePhase::DieRoll;
                                    encounterManager.iterateOverOutcomes(eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].rewardItemIDs,
                                                                         eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].successOutcomes,
                                                                         *currentCharacter);
                                    eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetSuccess;
                                    eTracker.selectedOption = -1;
                                    eTracker.alreadyDisplayedText = false;
                                    awaitingInput = true;

                                }
                            }else{
                                ///TODO add alternative to skillchecks in encounter. Check for item or quest progresss for example
                                encounterManager.iterateOverOutcomes(eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].rewardItemIDs,
                                                                     eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].successOutcomes,
                                                                     *currentCharacter);
                                eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetSuccess;
                                eTracker.selectedOption = -1;
                                eTracker.alreadyDisplayedText = false;
                                awaitingInput = true;
                            }
                        }else{if(eTracker.selectedOption != -1){std::cerr << "Selected Input not viable! Choose from displayed options!" << "\n";eTracker.selectedOption = -1;awaitingInput = true;}}
                    }

                } else {
                    //if we hit a 255 jump we reset the encounterTracker and activate the next Game Phase
                    eTracker.szene = 0;
                    awaitingInput = false;
                    eTracker.diaPhase = DialoguePhase::Scene;

                    Phase = GamePhases::DISASTER;
                    //continue with next phase
                }
            }else{
                if(eTracker.fateRerollChoice == 0 && currentCharacter->GetFatePoints() > 0){
                    currentCharacter->SpendFate();
                    if(ske.addFateDice()){
                        encounterManager.iterateOverOutcomes(eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].rewardItemIDs,
                                                             eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].successOutcomes,
                                                             *currentCharacter);
                        eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetSuccess;
                        eTracker.alreadyDisplayedText = false;
                        eTracker.chooseFateReroll = false;
                        eTracker.fateRerollChoice = -1;
                        eTracker.diaPhase = DialoguePhase::Scene;
                        awaitingInput = true;
                    }else{
                        if (currentCharacter->GetFatePoints() > 0) {
                            eTracker.diaPhase = DialoguePhase::DieRoll;
                            eTracker.alreadyDisplayedText = false;
                            eTracker.fateRerollChoice = -1;
                        }

                    }
                }
                if(eTracker.fateRerollChoice == 1 || currentCharacter->GetFatePoints() <= 0) {
                    encounterManager.iterateOverOutcomes(eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].failureItemIDs,
                                                         eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].failureOutcomes,
                                                         *currentCharacter);
                    eTracker.szene = eTracker.activeEncounter->scenes[eTracker.szene].options[eTracker.selectedOption].jumpTargetFail;
                    eTracker.alreadyDisplayedText = false;
                    eTracker.chooseFateReroll = false;
                    eTracker.fateRerollChoice = -1;
                    eTracker.diaPhase = DialoguePhase::Scene;
                    awaitingInput = true;
                    eTracker.selectedOption = -1;
                }
            }


        }
        if(Phase == GamePhases::DISASTER){
            std::cout << "DISASTER PHASE REACHED \n";
            std::cout.flush();

        }


        // std::cout << "Item: " << character1->GetInventory().back()->GetName();
        // std::cout << "\n";
    }

    std::map<SceneCompositionSlots,SDL_Point> sceneCompositionTarget //  TODO EXPAND AS NEEDED
            {
                    {SceneCompositionSlots::CharacterMain, EncounterLayout.characterMainPoint},
                    {SceneCompositionSlots::CharacterFront,{EncounterLayout.characterMainPoint.x+10,EncounterLayout.characterMainPoint.y}},
                    {SceneCompositionSlots::EnemyMain,EncounterLayout.enemyMainPoint},
                    {SceneCompositionSlots::Enemy_2,{EncounterLayout.enemyMainPoint.x+6,EncounterLayout.enemyMainPoint.y+10}},
                    {SceneCompositionSlots::Enemy_3,{EncounterLayout.enemyMainPoint.x+2,EncounterLayout.enemyMainPoint.y-5}},
                    {SceneCompositionSlots::InteractionMain,EncounterLayout.enemyMainPoint}
            };
    void BeasthoodState::RenderSceneComposition(const std::vector<std::tuple<SceneCompositionEntities,SceneCompositionSlots>>& compositionVector)
    {
        SDL_Rect targetRect;

        for(std::tuple<SceneCompositionEntities,SceneCompositionSlots> compElement: compositionVector)
        {
            switch(get<0>(compElement))
            {
                case SceneCompositionEntities::Character:
                    targetRect.x = windowSize.x * (sceneCompositionTarget[get<1>(compElement)].x*0.01);
                    targetRect.y = static_cast<int>(windowSize.y*(sceneCompositionTarget[SceneCompositionSlots::CharacterMain].y )*0.01-(SpriteData.ScalingvalueLKY*windowSize.y));
                    targetRect.w = static_cast<int>(SpriteData.ScalingvalueLKX*windowSize.x); // fix res dependence TODO differenciate between different player sprites
                    targetRect.h = static_cast<int>(SpriteData.ScalingvalueLKY*windowSize.y);
                    renderFromSpritesheet(targetRect,playerMainSpite);

                    break;
                case SceneCompositionEntities::Werewolf:

                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(EncounterLayout.characterMainPoint.y )*0.01-(SpriteData.ScalingValueGarouY*windowSize.y));
                    targetRect.w = SpriteData.ScalingValueGarouX*windowSize.x;
                    //fmt::println("Garou X: {}", SpriteData.ScalingValueGarouX*windowSize.x);
                    targetRect.h = static_cast<int>(SpriteData.ScalingValueGarouY*windowSize.y);
                    //fmt::println("Garou Y: {} = {} * {} * {}", SpriteData.ScalingValueGarouY*windowSize.y,SpriteData.Garou_IMG.y,SpriteData.ScalingValueGarouY,windowSize.y);
                    renderFromSpritesheet(targetRect,enemyWereWolfMainSprite);


                    break;
                default:
                    targetRect.x = windowSize.x * sceneCompositionTarget[get<1>(compElement)].x/100;
                    targetRect.y = static_cast<int>(windowSize.y*(EncounterLayout.characterMainPoint.y )*0.01-(SpriteData.ScalingValueGarouY*windowSize.y));
                    targetRect.w = SpriteData.ScalingValueGarouX*windowSize.x;
                    //fmt::println("Garou X: {}", SpriteData.ScalingValueGarouX*windowSize.x);
                    targetRect.h = static_cast<int>(SpriteData.ScalingValueGarouY*windowSize.y);
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

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y; //todo make font size variable
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Health   "+ std::to_string(currentCharacter->GetStamina())).c_str());
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
        SidebarText = textToTexture(("Knowledge   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::KNOWLEDGE))).c_str());
        renderText(SidebarTextTarget,SidebarText);

        SidebarTextTarget.y += SidebarLayout.SkillTextScale.y*0.01*windowSize.y;
        SDL_DestroyTexture(SidebarText);
        SidebarText = textToTexture(("Luck   "+ std::to_string(currentCharacter->GetCurrentStats().GetStat(StatNames::LUCK))).c_str());
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
                        static_cast<int>(SidebarIcons.Right.position.h*windowSize.y*0.01),
                        static_cast<int>(SidebarIcons.Right.position.w*windowSize.y*0.01),

                };
        std::pair<Item*, Item*>currentEquipment = currentCharacter->GetEquipment();
        if(get<1>(currentEquipment)!= nullptr)
        {
            //fmt::println("{} in right hand", get<0>(currentEquipment)->GetName());
            //if sth equipped in 0, render icon,
            SDL_SetRenderDrawColor(renderer(),5,5,100,0);
            SDL_RenderFillRect(renderer(),&EquipR);
            //if mouse over icon render mouseover
        }
        else
        {
            SDL_SetRenderDrawColor(renderer(),100,5,30,0);
            SDL_RenderFillRect(renderer(),&EquipR);
            //fmt::println("nothing in right hand");
        }

        SDL_Rect EquipL =
                {
                        static_cast<int>((SidebarIcons.Left.position.x * windowSize.x*0.01)),
                        static_cast<int>(SidebarIcons.Left.position.y*windowSize.y*0.01),
                        static_cast<int>(SidebarIcons.Left.position.h*windowSize.y*0.01),
                        static_cast<int>(SidebarIcons.Left.position.w*windowSize.y*0.01),

                };

        if(get<0>(currentEquipment)!= nullptr || (get<1>(currentEquipment)!= nullptr && get<1>(currentEquipment)->GetHandsNeeded()==2))
        {
            //fmt::println("{} in left hand", get<0>(currentEquipment)->GetName());
            //if sth equipped in 0, render icon,


            SDL_SetRenderDrawColor(renderer(),5,5,100,0);
            SDL_RenderFillRect(renderer(),&EquipL);
            //if mouse over icon render mouseover
        }
        else
        {
            //fmt::println("nothing in left hand");
            SDL_SetRenderDrawColor(renderer(),100,5,30,0);
            SDL_RenderFillRect(renderer(),&EquipL);
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


        SDL_DestroyTexture(SidebarText);
        SidebarText = nullptr;
    }
    void BeasthoodState::RenderInventorySelection(int mouseX, int mouseY, int screenWidth, int screenHeight) {


        SDL_Rect Selection{static_cast<int>(screenWidth *
                                            (inventoryScreen.currentPage.StartPoint.x - ItemDetailedView.Dimensions.x) *
                                            0.01),
                           static_cast<int>(screenHeight * (inventoryScreen.currentPage.StartPoint.y) * 0.01),
                           static_cast<int>(screenWidth * ItemDetailedView.Dimensions.x * 0.01),
                           static_cast<int>(screenWidth * ItemDetailedView.Dimensions.y * 0.01)};


        //open submenu pop-up/lock pop-up in place, if implemented in hover
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

        renderText({Selection.x, static_cast<int>(Selection.y), 10, 10}, DisplayText);
        SDL_DestroyTexture(DisplayText); //todo there is a better way surely

        //todo parse and render item


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
                (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::LUCK)) + " LUCK").c_str());
        renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.06), 10, 10}, DisplayText);
        SDL_DestroyTexture(DisplayText);

        DisplayText = textToTexture(
                (std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::KNOWLEDGE)) + " KNOWLEDGE").c_str());
        renderText({Selection.x, static_cast<int>(Selection.y + screenHeight * 0.07), 10, 10}, DisplayText);
        SDL_DestroyTexture(DisplayText);


        if (ItemToDisplay->GetAbility()) {
            switch (ItemToDisplay->GetAbility()->GetName()) {
                case (AbilityName::DrawExtraItem):
                    DisplayText = textToTexture("Draw Extra Item - change to sth different, drawing too abstract");
                    break;
                case (AbilityName::ReduceStaminaLoss):
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







    void BeasthoodState::RenderInventorySelectionNoOption(int mouseX, int mouseY, int screenWidth, int screenHeight, bool left_item)
    {
        SDL_Rect Selection {static_cast<int>(mouseX-static_cast<int>(screenWidth*ItemDetailedView.Dimensions.x*0.01)),
                            static_cast<int>(mouseY-static_cast<int>(screenWidth*ItemDetailedView.Dimensions.y*0.01)),
                            static_cast<int>(screenWidth*ItemDetailedView.Dimensions.x*0.01),
                            static_cast<int>(screenWidth*ItemDetailedView.Dimensions.y*0.01)};


        //open submenu pop-up/lock pop-up in place, if implemented in hover
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

        //todo parse and render item


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

        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::LUCK))+" LUCK").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.06), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);

        DisplayText = textToTexture((std::to_string(ItemToDisplay->GetStats().GetStat(StatNames::KNOWLEDGE))+" KNOWLEDGE").c_str());
        renderText({Selection.x,static_cast<int>(Selection.y+screenHeight*0.07), 10,10 },DisplayText);
        SDL_DestroyTexture(DisplayText);


        if( ItemToDisplay->GetAbility())
         {
             switch (ItemToDisplay->GetAbility()->GetName()) {
                 case(AbilityName::DrawExtraItem):
                     DisplayText = textToTexture("Draw Extra Item - change to sth different, drawing too abstract");
                     break;
                 case(AbilityName::ReduceStaminaLoss):
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
        inventoryScreen.currentPage.RenderInventoryPage(renderer(),windowSize.x,windowSize.y);

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
        if(bIsActive)
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


        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);//TODO WINDOWSIZE HERE - fix redundancy

        SDL_SetRenderDrawColor(renderer(), 0x7F, 0x00, 0x7F, 0x00);
        SDL_RenderClear(renderer());

        if (Phase == GamePhases::UPKEEP || Phase == GamePhases::MOVEMENT) {

            //set color for connected path lines
            SDL_SetRenderDrawColor(renderer(), 0x00, 0x7F, 0x00, 0x00);

            for (const auto &e: locationManager.GetAllItems()) {
                //render the locations
                // renderFromSpritesheet(e->GetMapSlot()->rect, forestLocationIconTexture);


                if (e->fog_of_war) {
                    //find the relevant location textures using LocationID enum
                    auto it = locationTextureMap.find(e->GetLocationID());
                    if (it != locationTextureMap.end()) {
                        SDL_Texture *icon = it->second.iconTexture;
                        SDL_Texture *name = it->second.nameTexture;

                        renderFromSpritesheet(e->GetMapSlot()->rect, icon);
                        renderText(e->GetMapSlot()->rect, name);

                        /*
            switch (e->GetLocationID()) {
                case LocationID::Forest:
                    renderFromSpritesheet(e->GetMapSlot()->rect, forestLocationIconTexture);
                    renderText(e->GetMapSlot()->rect,forestNameTexture);break;
                        case LocationID::Church:
                            // Handle Church
                            break;
                        case LocationID::River:
                            // Handle River
                            break;
                        case LocationID::Smith:
                            // Handle Smith
                            break;
                        case LocationID::Windmill:
                            // Handle Windmill
                            break;
                        case LocationID::Crossroads:
                            // Handle Crossroads
                            break;
                        case LocationID::Cave:
                            // Handle Cave
                            break;
                        case LocationID::Monastery:
                            // Handle Monastery
                            break;
                        case LocationID::Farm:
                            // Handle Farm
                            break;
                        case LocationID::Clearing:
                            // Handle Clearing
                            break;
                        case LocationID::Townhall:
                            // Handle Townhall
                            break;
                        case LocationID::Thicket:
                            // Handle Thicket
                            break;
                        case LocationID::UNASSIGNED:
                            // Handle UNASSIGNED
                            break;
                        default:
                            // Handle unknown cases
                            break;
                    }
    */
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
                    renderFromSpritesheet(character1->GetRect(), playerMapIconTexture);
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
                    default:SDL_RenderFillRect(renderer(),&sceneWindow);
                }

                RenderSceneComposition(eTracker.activeEncounter->scenes[eTracker.szene].compositionVector);


                //Render Foreground //todo decouple from bg, if needed?
                switch(eTracker.activeEncounter->scenes[eTracker.szene].background)
                {
                    case EnvironmentType::DenseForest:
                    {
                        renderFromSpritesheet(sceneWindow, denseForestFG);
                        break;
                    }
                    default:SDL_RenderFillRect(renderer(),&sceneWindow);
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



                std::vector<SDL_Rect> OptionVector= {};


                switch (eTracker.diaPhase) {
                    case DialoguePhase::Scene:
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
                                //SDL_SetRenderDrawColor(renderer(),255,0,0,0);
                                //SDL_RenderFillRect(renderer(),&OptionVector.back());
                                renderText(OptionVector.back(),optionText, 10);
                            }
                            else
                            {
                                //SDL_SetRenderDrawColor(renderer(),0,0,200,0);
                                //SDL_RenderFillRect(renderer(),&OptionVector.back());
                                renderText(OptionVector.back(),optionText,7);
                            }



                            //fmt::println("OptionVector size {}", OptionVector.size());
                            SDL_DestroyTexture(optionText); //prevent leak
                            optionText= nullptr;

                        }
                        break;
                    case DialoguePhase::DieRoll:
                        if(!eTracker.alreadyDisplayedText) {
                            //renderDicerollAnimation(ske);
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
                                    //renderText(DialogueMainField,optionText);

                                optionTextYes = textToTexture("Yes. (-1 WP)");
                                optionTextNo = textToTexture("No.");




                                if(IsMouseInsideRect(OptionVector[0],mouseOverX,mouseOverY))
                                {
                                    SDL_SetRenderDrawColor(renderer(),255,0,0,0);
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





                            }
                        }
                        //todo if fail render question
                        break;
                    case DialoguePhase::FateReroll:
                        if(!eTracker.alreadyDisplayedText) {
                            renderFateDieAnimation(ske);
                            eTracker.diaPhase = DialoguePhase::Scene;

                        }

                        break;

                }
            }


            // SDL_RenderPresent( renderer() );

            //TODO TEST

        }
        if(bInInventory)
        {
            RenderInventory();
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

        Point windowSize;
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);

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
                                EnvironmentType::DenseForest,
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
                                        }
                                },
                                {
                                        {SceneCompositionEntities::Character,SceneCompositionSlots::CharacterMain},
                                        {SceneCompositionEntities::Werewolf,SceneCompositionSlots::EnemyMain}

                                }
                        },
                        {
                                "Scene 1",
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
                        }
                },
                DialoguePhase::Scene // Starting dialogue phase
        };
    encounterManager.addEncounter(FirstEncounter.id,FirstEncounter);
    }

    void BeasthoodState::PopulateLocationEvents(){

        locationManager.GetItem(LocationID::Forest)->related_events.push_back(EncounterID::Forest_Thievery);
    }


    //input character sheets here, maybe add intro choices to modify these TODO
    //examples on how to fill a character sheet here
    void BeasthoodState::PopulateBlueprints() {

        std::vector<Item *> temp;
        temp.push_back(itemManager.GetItem(ItemName::Halbert));
        blueprintManager.AddBlueprint(std::make_shared<CharacterBlueprint>(
                "Landsknecht",
                8, 6,
                Stats(5, 1, 6, 1, 3, 0),
                Stats(5, 4, 6, 4, 3, 3),
                2,
                abilityManager.GetAbility(AbilityName::ReduceStaminaLoss),
                "Gain a fate point after defeating a boss",
                temp
        ));

        blueprintManager.AddBlueprint(std::make_shared<CharacterBlueprint>(
                "Monk",
                5, 8,
                Stats(4, 2, 1, 6, 6, 1),
                Stats(4, 5, 4, 6, 6, 4),
                3,
                abilityManager.GetAbility(AbilityName::DrawExtraItem),
                "Gain a fate point after casting 3 spells in a turn",
                temp
        ));
    }

    bool BeasthoodState::IsMouseInsideRect(const SDL_Rect &rect, int mouseX, int mouseY) {
        return mouseX >= rect.x && mouseX < (rect.x + rect.w) &&
               mouseY >= rect.y && mouseY < (rect.y + rect.h);
    }

    //todo placeholder functions
    void BeasthoodState::renderDicerollAnimation(SkillChallengeEngine& ske)
    {
        fmt::println("Testing: {}",ske.currentSkillName());
        for(uint8_t roll : ske.currentRolls)
        {
            fmt::print("{} ", roll);
        }
        fmt::println(" - {} Successes for Difficulty {}.", ske.getSuccesses(), ske.getDifficulty());
        if (ske.getSuccesses() >= ske.getDifficulty()) //todo you can get true from the skillcheck being called-> can save result in WS!
        {
            fmt::println("Passed!");
        }
        else
        {
            //Todo check if FP available
            fmt::println("Failed! Spend a Will point to roll one more die?");
            fmt::println("1. Yes");
            fmt::println("2. No");
        }

    }
    void BeasthoodState::renderFateDieAnimation(const SkillChallengeEngine& ske)
    {
        fmt::println("Will fate bend to mortal will?");
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
            case StatNames::KNOWLEDGE:
                return "Knowledge";
            case StatNames::LUCK:
                return "Luck";

        }
    }
}