//
// Created by max on 15.01.25.
//
#include "example_game.hpp"
#include <hsnr64/offset.hpp>
#include "../global.hpp"
#include "map.h"

#include <hsnr64/palette.hpp>
#include <iostream>
#include "ability_manager.h"
#include "ReduceStaminaLoss_ability.h"
#include "DrawExtraItem_ability.h"
#include "item_manager.h"
#include "item.h"
#include "character.h"
#include "encounter.h"
#include "skillCheckEngine.h"


// TODO item class as well as character ability and fate refill then do events and event manager
void iterateOverOutcomes(const std::vector<std::tuple<ExecuteFlags, int8_t>> &outcomes);

namespace JanSordid::SDL_Example {

    Encounter FirstEncounter{
            {{"Scene 0 \n This is a test scene. You may pay in blood to pass, or try convincing whatever is in front of you.",
              {
                      {"MoveTo 1 - Pay in blood", false, StatNames::FIGHT, 0, {{ExecuteFlags::Wound, 3}}, {}, 1, -1},
                      {"MoveTo 2 Skillcheck", true, StatNames::FIGHT, 2, {{ExecuteFlags::RegainSan, 1}},
                       {{ExecuteFlags::Wound, 3}}, 2, 3}
              }
             },
             {"Scene 1",
              {
                      {"Leave", false, StatNames::FIGHT, 0, {}, {}, 255, 255},
                      {"Retry", false, StatNames::FIGHT, 0, {}, {}, 0, 255}
              }
             },
             {"Scene 2 - You succeded",
              {
                      {"Leave", false, StatNames::FIGHT, 0, {}, {}, 255, 255}, //todo make leave premade
                      {"Retry", false, StatNames::FIGHT, 0, {}, {}, 0, 255}
              }

             },
             {"Scene 3 - you failed and injured yourself",
              {
                      {"Retry", false, StatNames::FIGHT, 0, {{ExecuteFlags::Wound, 1}}, {}, 0,
                       255} //todo make leave premade
              }

             }

            }
    };

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

        //--------------- load textures from file
        forestLocationIconTexture = loadFromFile(forestLocationIconPath);
        playerMapIconTexture = loadFromFile(playerMapIconPath);


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

        Point windowSize;
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



        // CurrentEncounter = e;


        dialoguePhase = DialoguePhase::Scene;
        CurrentEncounter = FirstEncounter;
        character1->RefillFatePoints();
        currentCharacter = character1;

        // get character into SKE
        ske.changeCharacter(currentCharacter);
        fmt::println("Fate available: {}",
                     character1->GetFatePoints()); //todo 0 fate dialogue makes no sense, prints options that should not be printed
        std::cout.flush();

        bInDialogue = true;



    }

    void BeasthoodState::Destroy() {
        SDL_DestroyTexture(forestLocationIconTexture);
        SDL_DestroyTexture(playerMapIconTexture);
        for (auto e: locationTextureMap) {
            SDL_DestroyTexture(e.second.iconTexture);
            SDL_DestroyTexture(e.second.nameTexture);
        }

        forestLocationIconTexture = nullptr;
        playerMapIconTexture = nullptr;

        Base::Destroy();
    }

    bool BeasthoodState::HandleEvent(const Event &event) {

        if (!bInDialogue) {
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);


                for (auto e: map.slots) {
                    if (IsMouseInsideRect(e.rect, mouseX, mouseY)) {
                        if (event.type == SDL_MOUSEMOTION) {
                            std::cout << "Mouse moved inside the rectangle.\n";
                            std::cout.flush();

                        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                            //mausklick reagiert nur wenn die location einen pfad zum aktuellen standort des characters hat
                            for (auto c: e.connections) {
                                //durchsuchen die aktiven connections der aktuellen node nach einam pfad zum character
                                if (character1->GetCurrentLocationID() == map.GetSlotByID(c.first)->location_id &&
                                    c.second == true) {
                                    std::cout << "Mouse clicked inside the rectangle.\n";
                                    //setzen location vom charakter und pos auf das aktuelle e da dies die node ist die gecklickt wurde
                                    character1->SetCurrentLocation(e.location_id);
                                    character1->SetPos(e.rect);


                                    std::cout.flush();
                                }

                            }
                        }
                    } else if (!IsMouseInsideRect(e.rect, mouseX, mouseY)) {
                        if (event.type == SDL_MOUSEMOTION) {
                            std::cout << "Mouse moved OUTSIDE the rectangle. " << e.id;
                            std::cout << " \n";
                            std::cout.flush();
                        }
                    }
                }
            }
        }



        /*
        switch( event.type )
        {
            case SDL_MOUSEWHEEL:
                brightness += event.wheel.y * 3;
                return true;
        }
*/
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
        if (bNeedInput) {
            int n;
            std::cin >> n;
            CurrentInput = n;
        }
        return false;

    }

    void BeasthoodState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {
        if (character1->GetCurrentLocationID() == LocationID::UNASSIGNED) {
            character1->SetCurrentLocation(LocationID::Forest);
            character1->SetPos(locationManager.GetItem(LocationID::Forest)->GetMapSlot()->rect);
        }

        if(bInDialogue)
        {
            updateDialogue();
        }

        // std::cout << "Item: " << character1->GetInventory().back()->GetName();
        // std::cout << "\n";
    }

    void BeasthoodState::Render(const u64 frame, const u64 totalMSec, const f32 deltaT) {

        Point windowSize;
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);

        SDL_SetRenderDrawColor(renderer(), 0x7F, 0x00, 0x7F, 0x00);
        SDL_RenderClear(renderer());

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

            if(bInDialogue)
            {
                switch (dialoguePhase) {
                    case DialoguePhase::Scene:
                        std::cout << CurrentEncounter.Scenes[CurrentScene].SceneText << std::endl;
                        std::cout.flush();

                        for(const SceneOption& o :  CurrentEncounter.Scenes[CurrentScene].Options) {
                            if (o.bIsSkillCheck) {
                                fmt::println("[{}] {}", "Fight", o.Text);
                                std::cout.flush();

                            } else {
                                fmt::println("{}", o.Text);
                                std::cout.flush();


                            }
                        }
                        break;
                    case DialoguePhase::DieRoll:
                        renderDicerollAnimation(ske);
                        //todo if fail render question
                        break;
                    case DialoguePhase::FateReroll:
                        renderFateDieAnimation(ske);
                        break;

                }
            }


            // SDL_RenderPresent( renderer() );

/*
        // Prepare the text as Texture
        if( blendedText == nullptr )
        {
            constexpr const char * text =
                    "Use mouse-wheel or [DOWN] and [UP] arrow keys\n"
                    "   to change the brightness and colorization\n"
                    "                  of the plasma effect!";

            if( blendedText != nullptr )
                SDL_DestroyTexture( blendedText );

            constexpr const Color white = HSNR64::Palette( HSNR64::NamedColorIndex::White );
            Surface * surf = TTF_RenderUTF8_Blended_Wrapped( font, text, white, windowSize.x - 2 * offsetFromLeft );
            blendedText = SDL_CreateTextureFromSurface( renderer(), surf );
            SDL_FreeSurface( surf );

            u32 fmt;
            int access;
            SDL_QueryTexture( blendedText, &fmt, &access, &blendedTextSize.x, &blendedTextSize.y );
        }


        // Draw the text on top of the plasma effect
        {
            const Point p {
                    offsetFromLeft,
                    windowSize.y - (int)(100 * _game.scalingFactor())
            };

            const int shadowOffsetFactor = (int)(1.0f*_game.scalingFactor());
            //const int shadowOffsetFactor = (int)(2.0f*_game.scalingFactor()); // chonky shadow

            // Draw the shadow
            SDL_SetTextureColorMod( blendedText, 0, 0, 0 );
            for( const Point & offset : HSNR64::ShadowOffset::Rhombus )
            {
                const Rect dst_rect = Rect{ p.x, p.y, blendedTextSize.x, blendedTextSize.y } + (offset * shadowOffsetFactor);
                SDL_RenderCopy( renderer(), blendedText, EntireRect, &dst_rect );
            }

            SDL_SetTextureColorMod( blendedText, 255, 255, 255 );
            const Rect dst_rect = p + Rect{ 0, 0, blendedTextSize.x, blendedTextSize.y };
            SDL_RenderCopy( renderer(), blendedText, EntireRect, &dst_rect );


        }
        */
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
    void
    BeasthoodState::renderFromSpritesheet(Rect values, SDL_Texture *t, SDL_Rect *clip, double angle, SDL_Point *center,
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
            const Rect dst_rect = Rect{values.x, values.y - 10, _blendedTextSize.x, _blendedTextSize.y} + offset;
            SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);
        }
        const Color &color = HSNR64::Palette(_colorIndex);
        SDL_SetTextureColorMod(t, color.r, color.g, color.b);
        const Rect dst_rect = {values.x, values.y - 10, _blendedTextSize.x, _blendedTextSize.y};
        SDL_RenderCopy(renderer(), t, EntireRect, &dst_rect);

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


    void BeasthoodState::iterateOverOutcomes(const std::vector<std::tuple<ExecuteFlags, int8_t>> &outcomes) {
        for (std::tuple<ExecuteFlags, int8_t> outcome: outcomes) {

            switch (get<0>(outcome)) {
                case ExecuteFlags::Wound:

                    fmt::print("Debug- Injury");
                    currentCharacter->AdjustHealth(-get<1>(outcome));
                    break;
                case ExecuteFlags::GainItem:
                    //TODO ITEM SYSTEM
                    break;
                case ExecuteFlags::Heal:
                    currentCharacter->AdjustHealth(get<1>(outcome));
                    break;
                case ExecuteFlags::SanityLoss:
                    currentCharacter->AdjustSanity(-get<1>(outcome)); //todo fix this mess/warning
                    break;
                case ExecuteFlags::RegainSan:
                    currentCharacter->AdjustSanity(get<1>(outcome));
                    break;

            }
        }
    }

    void BeasthoodState::updateDialogue() {
        switch (dialoguePhase) {
            case DialoguePhase::Scene:
                bNeedInput = true;
                if (bNeedInput && CurrentInput != -1) {
                    if (CurrentInput <= CurrentEncounter.Scenes[CurrentScene].Options.size()) {

                        ChosenOption = CurrentInput - 1;
                        if (!CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput - 1].bIsSkillCheck) {
                            //if Jump Target is escape value TODO define further behavior, construct Combat encounter encoding and Jump
                            if (CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput - 1].JumpTargetSuccess ==
                                255)
                               bool bRunning = false; //TODO this no longer does anything
                            else
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput -
                                                                                             1].JumpTargetSuccess;
                        } else {


                            //ske.bIsActive=true; todo put flag in other place
                            ske.setDifficulty(
                                    CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput - 1].difficulty);
                            ske.setModifier(0);
                            ske.setSkill(CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput - 1].skill);


                            if (ske.checkSkill()) {//Skillcheck Passed
                                iterateOverOutcomes(
                                        CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].SuccessOutcomes);
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetSuccess;
                                bNeedInput = false;

                            } else {
                                //Not Passed TODO
                                if (currentCharacter->GetFatePoints() > 0) { // can spend will
                                    bNeedInput = true;
                                } else {
                                    bNeedInput = false;
                                    iterateOverOutcomes(
                                            CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].FailureOutcomes);
                                    CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetFail;
                                }


                            }
                            dialoguePhase = DialoguePhase::DieRoll;
                        }


                    }

                    CurrentInput = -1;
                }
                break;
            case DialoguePhase::DieRoll: // misnomer
                //???
                if (bNeedInput) {
                    //if any WP avalkable
                    switch (CurrentInput) {
                        case 1: // todo move to reroll phase?
                            character1->SpendFate();
                            dialoguePhase = DialoguePhase::FateReroll;
                            bNeedInput = false;
                            if (ske.addFateDice()) //todo seems broken
                            {
                                //Passed after Fateroll
                                iterateOverOutcomes(
                                        CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].SuccessOutcomes);
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetSuccess;
                            } else {
                                fmt::println("Debug fate fail!");
                                iterateOverOutcomes(
                                        CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].FailureOutcomes);
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetFail;
                            }

                            break;
                        case 2:
                            //Choose to fail/not roll
                            iterateOverOutcomes(
                                    CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput - 1].FailureOutcomes);
                            CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetFail;

                            dialoguePhase = DialoguePhase::Scene;
                            break;
                        default:;


                    }
                    CurrentInput = -1;

                } else {
                    dialoguePhase = DialoguePhase::Scene;
                    bNeedInput = true;
                }


                break;
            case DialoguePhase::FateReroll:


                dialoguePhase = DialoguePhase::Scene;
                CurrentInput = -1;
                bNeedInput = true;
                break;

        }
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
}