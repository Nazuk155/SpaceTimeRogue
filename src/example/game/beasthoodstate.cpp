//
// Created by max on 15.01.25.
//
#include "example_game.hpp"
#include <hsnr64/offset.hpp>
#include "map.h"

#include <hsnr64/palette.hpp>
#include <iostream>


#include "ability_manager.h"
#include "ReduceStaminaLoss_ability.h"
#include "DrawExtraItem_ability.h"
#include "item_manager.h"
#include "item.h"
#include "character.h"



// TODO item class as well as character ability and fate refill then do events and event manager
namespace JanSordid::SDL_Example
{
    void BeasthoodState::Init()
    {
        Base::Init();

        font = TTF_OpenFont( BasePath "asset/font/MonkeyIsland-1991-refined.ttf", _game.scalingFactor() * 16 );
        TTF_SetFontHinting( font, TTF_HINTING_NONE );

        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

        const Point resolution = windowSize / Scale;

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
            for (int i = 1; i <= 12; ++i) {
                map.AddSlot(i,{i * 100, i * 100});
            }

            // Add connections
            map.ConnectSlots(1, 2);
            map.ConnectSlots(1, 3);
            map.ConnectSlots(1, 4);
            map.ConnectSlots(1, 5);
            map.ConnectSlots(1, 6);
            map.ConnectSlots(6, 7);
            map.ConnectSlots(7, 8);
            map.ConnectSlots(7, 9);
            map.ConnectSlots(7, 10);
            map.ConnectSlots(7, 11);
            map.ConnectSlots(7, 12);

            // Create and assign locations
            std::vector<Location> locations;
            for (int i = 1; i <= 12; ++i) {
                locations.emplace_back( "Location " + std::to_string(i),i);
                map.SetLocation(i, locations.back());
            }

            // Verify connections and location setup
            for (int i = 1; i <= 12; ++i) {
                Map_Slot* slot = map.GetSlotByID(i);
                if (slot) {
                    std::cout << "Map_Slot ID: " << slot->id << ", Connections: ";
                    std::cout.flush();

                    for (std::pair<int, bool> connected_id : slot->connections) {
                        std::cout << connected_id.first << " ";
                        std::cout.flush();

                    }
                    std::cout << "\n";

                    map.SetConnectionStatus(3,1,false);

                    Location* loc = &locations[i - 1];
                    std::cout << "  Location: " << loc->name
                              << ", Active Connections: ";
                    std::cout.flush();


                    if (loc->GetMapSlot()) {
                        for (int connected_id : loc->GetActiveConnections()) {
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
            Ability* reduceStaminaLoss = abilityManager.GetAbility(AbilityName::ReduceStaminaLoss);
            if (reduceStaminaLoss) {
                reduceStaminaLoss->Activate();
            }

            Ability* drawExtraItem = abilityManager.GetAbility(AbilityName::DrawExtraItem);
            if (drawExtraItem) {
                drawExtraItem->Activate();
            }




            // Create and add an ability
            auto staminaAbility = std::make_unique<ReduceStaminaLossAbility>();
            Ability* staminaAbilityPtr = staminaAbility.get();
            abilityManager.AddAbility(std::move(staminaAbility));

            // Create and add items
            auto sword = std::make_unique<Item>(ItemName::Halbert, ItemType::Weapon, "Halbert of Valor", 1);
            sword->SetStats({0, 0, 5, 0,0,0}); // Attack 10
            sword->SetAbility(staminaAbilityPtr); // Associate ability with item
            itemManager.AddItem(std::move(sword));

            // Access and use an item
            Item* item = itemManager.GetItem(ItemName::Halbert);
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








    }

    void BeasthoodState::Destroy()
    {
        Base::Destroy();
    }

    bool BeasthoodState::HandleEvent( const Event & event )
    {
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

    bool BeasthoodState::Input()
    {
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

    void BeasthoodState::Update( const u64 frame, const u64 totalMSec, const f32 deltaT )
    {

    }

    void BeasthoodState::Render( const u64 frame, const u64 totalMSec, const f32 deltaT )
    {

        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

        const int offsetFromLeft = (int)(30 * _game.scalingFactor());
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
        */

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
    }




void BeasthoodState::renderFromSpritesheet(int targetX,int targetY,int targetW,int targetH,SDL_Texture* t,const Rect* clip, double angle,
                                            SDL_Point* center, SDL_RendererFlip flip,bool useClipsize)
{
    SDL_Rect renderQuad = { targetX,targetY,targetW,targetH};

    if( clip != nullptr && useClipsize)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( renderer(), t,clip, &renderQuad, angle, center, flip );
}

//Version using a SDL_Rect to pull values from. Added for utility and because everything should have a Rect
void BeasthoodState::renderFromSpritesheet(Rect values,SDL_Texture* t, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip,bool useClipSize){
    SDL_Rect renderQuad = {values.x,values.y,values.w,values.h};

    if( clip != nullptr && useClipSize)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( renderer(), t,clip, &renderQuad, angle, center, flip );
}

//result should be saved in a texture related to a object within MortalFlawState.
// Surface Width/Height should match player width/height otherwise texture needs to be scaled.
Texture* BeasthoodState::loadFromFile(const std::string& path){

    Texture * newTexture = nullptr;
    Surface * loadedSurface =  IMG_Load(path.c_str());

    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer(), loadedSurface );
        if( !newTexture  )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}



    //input character sheets here, maybe add intro choices to modify these TODO
    //examples on how to fill a character sheet here
    void BeasthoodState::PopulateBlueprints() {

        std::vector<Item*> temp;
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

}