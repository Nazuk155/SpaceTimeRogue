//
// Created by Prince of Brass on 03.02.2025.
//
#include "../global.hpp"
#include "item.h"
#include "character.h"


#ifndef SDL_BASE_INVENTORY_COMPONENTS_H
#define SDL_BASE_INVENTORY_COMPONENTS_H

struct InventoryIcon //maybe not
{
  bool active = false;
  SDL_Rect position{};
  Item* referencedItem = nullptr;
};

class Button {
    SDL_Rect ButtonRect;
    std::unique_ptr<SDL_Texture> ButtonImg;
    std::unique_ptr<SDL_Texture> ButtonMouseoverImg;
    std::unique_ptr<SDL_Texture> ButtonDisbledImg;

    bool bMouseOverEvent;
    //todo Mouseover render?

    //what do event?
    //use enum class? + identifier?

};

struct
{
    SDL_Point StartPoint;
    SDL_Point Dimensions {15,15};



    //String Name = referencedItem->GetName(); //possibly redundant? more readable
    //String Text; //todo add descriptions/loretext to items

    SDL_Point EquipRightPos{1,11};
    SDL_Point EquipLeftPos {9,11};
    SDL_Point ButtonScale {5,3};
    //Button EquipRight;
    //Button EquipLeft;

} ItemDetailedView;


class InventoryPage
{

    //8x*5y icons - 40?
public:
    Character* currentCharacter = nullptr; //todo this is a mess
    std::array<InventoryIcon,40> icons;
    SDL_Point StartPoint{20,20};
    SDL_Point Dimensions{60,60};
    InventoryIcon* MouseOverIcon = nullptr;

    bool bIconHover = false;
    bool bIconSelected = false;

//public:
    void RenderInventoryPage(SDL_Renderer*renderer, int screenWidth, int screenHeight)
    {
        SDL_Rect window = {static_cast<int>(StartPoint.x*screenWidth*0.01), static_cast<int>(StartPoint.y*screenHeight*0.01),
                           static_cast<int>(Dimensions.x*screenWidth*0.01),static_cast<int>(Dimensions.y*screenHeight*0.01)};

        SDL_SetRenderDrawColor(renderer,200,10,10,0);
        SDL_RenderFillRect(renderer,&window);
        //iterate icons
        SDL_Rect icon {0,
                       0,
                       static_cast<int>(0.07*screenWidth),
                       static_cast<int>(0.07*screenWidth)
        };
        for(int i = 0; i < 8; i++)
        {
            for(int j=0;j<5;j++)
            {
                icon.x=static_cast<int>(window.x + ((0.0025+0.0725)*screenWidth)*i);
                icon.y=static_cast<int>(window.y + ((0.0025+0.0725)*screenWidth)*j);
                icons[i+8*j].position=icon;

                if(icons[i+8*j].active)
                {
                    SDL_SetRenderDrawColor(renderer,0,200,10,0);
                    SDL_RenderFillRect(renderer,&icon);

                }
                else
                {
                    SDL_SetRenderDrawColor(renderer,10,10,10,0);
                    SDL_RenderFillRect(renderer,&icon);
                }



            }
        }

    }
    void MouseOver(int mouseX, int mouseY)
    {

        //iterate over icons
        for(InventoryIcon &icon : icons)
        {
            if(mouseX >= icon.position.x && mouseX < (icon.position.x + icon.position.w) &&
               mouseY >= icon.position.y && mouseY < (icon.position.y + icon.position.h) &&
               icon.active && !bIconSelected) //mouse in icon, icon has meaning and not clicked
            {

                MouseOverIcon=&icon;
                bIconHover=true;
                return;

            }
            else
            {
                if(!bIconSelected)
                    MouseOverIcon = nullptr;
                bIconHover=false;

            }
        }
        //no else, hovering nowhere is irrelevant
    }
    void Click(int mouseX, int mouseY, int screenWidth, int screenHeight)
    {

        if(bIconSelected )
        {
            //fmt::println("Clicked while selection locked");


            SDL_Rect ButtonRect //Right
            ={
                    static_cast<int>((screenWidth*0.01)*(StartPoint.x -ItemDetailedView.Dimensions.x + ItemDetailedView.EquipRightPos.x)),
                    static_cast<int>((screenHeight*(StartPoint.y )*0.01)+ItemDetailedView.EquipRightPos.y*0.01*screenWidth),
                    static_cast<int>(ItemDetailedView.ButtonScale.x*0.01*screenWidth),
                    static_cast<int>(ItemDetailedView.ButtonScale.y*0.01*screenWidth)

            };
            if(mouseX >= ButtonRect.x && mouseX < (ButtonRect.x + ButtonRect.w) &&
               mouseY >= ButtonRect.y && mouseY < (ButtonRect.y + ButtonRect.h))
            {

                if(MouseOverIcon->referencedItem->IsEquipped())
                {
                    if(currentCharacter->GetEquipment().first==MouseOverIcon->referencedItem)
                    {
                        currentCharacter->UnequipItem(true);
                    }
                    else if(currentCharacter->GetEquipment().second==MouseOverIcon->referencedItem)
                    {
                        currentCharacter->UnequipItem(false);
                    }
                }

                if(currentCharacter->GetEquipment().second)
                {
                    currentCharacter->UnequipItem(false);
                }
                if(currentCharacter->GetEquipment().first && MouseOverIcon->referencedItem->GetHandsNeeded()==2)
                {
                    currentCharacter->GetEquipment().first->Unequip();
                }

                fmt::println("Clicked equip {} in Right Hand",MouseOverIcon->referencedItem->GetName());
                currentCharacter->EquipItem(MouseOverIcon->referencedItem,false);
                return;
            }

            ButtonRect //Left
                    ={
                    static_cast<int>((screenWidth*0.01)*(StartPoint.x -ItemDetailedView.Dimensions.x + ItemDetailedView.EquipLeftPos.x)),
                    static_cast<int>((screenHeight*(StartPoint.y )*0.01)+ItemDetailedView.EquipRightPos.y*0.01*screenWidth),
                    static_cast<int>(ItemDetailedView.ButtonScale.x*0.01*screenWidth),
                    static_cast<int>(ItemDetailedView.ButtonScale.y*0.01*screenWidth)

            };
            if(mouseX >= ButtonRect.x && mouseX < (ButtonRect.x + ButtonRect.w) &&
               mouseY >= ButtonRect.y && mouseY < (ButtonRect.y + ButtonRect.h))
            {

                if(MouseOverIcon->referencedItem->IsEquipped())
                {
                    if(currentCharacter->GetEquipment().first==MouseOverIcon->referencedItem)
                    {
                        currentCharacter->UnequipItem(true);
                    }
                    else if(currentCharacter->GetEquipment().second==MouseOverIcon->referencedItem)
                    {
                        currentCharacter->UnequipItem(false);
                    }
                }

                if(currentCharacter->GetEquipment().first)
                {
                    currentCharacter->UnequipItem(true);
                }
                if(currentCharacter->GetEquipment().second && MouseOverIcon->referencedItem->GetHandsNeeded()==2)
                {
                    currentCharacter->GetEquipment().second->Unequip();
                }

                fmt::print("Clicked equip {} in Left Hand",MouseOverIcon->referencedItem->GetName());
                currentCharacter->EquipItem(MouseOverIcon->referencedItem,true); //todo 2-handed handling

                return;
            }




        }


        //iterate over icons
        for(InventoryIcon &icon : icons)
        {
            if(mouseX >= icon.position.x && mouseX < (icon.position.x + icon.position.w) &&
               mouseY >= icon.position.y && mouseY < (icon.position.y + icon.position.h) &&
               icon.active && !bIconSelected) //mouse in icon, icon has meaning and not clicked
            {

                MouseOverIcon=&icon;
                bIconHover=true;
                bIconSelected = true;
                return;

            }
            else
            {
                MouseOverIcon = nullptr;
                bIconHover=false;
                bIconSelected = false;

            }
        }
    }



};

class InventoryScreen
{

    std::vector<InventoryPage> pages;
    public:
    Character* currentCharacter = nullptr;
    InventoryPage currentPage;

    //on init and update -> calculate pages
    InventoryScreen()
    {
        currentCharacter= nullptr;
    }
    explicit InventoryScreen(Character* chara)
    {

        currentCharacter = chara;
        BuildInventory();

    }

    void BuildInventory() //TODO currently 40 item max, build other pages, deal with potential memory leak form that expansion
    {
        if(currentCharacter->GetInventory().size() <= 40)
        {
            currentPage.currentCharacter = currentCharacter; //todo this is beyond stupid
            for (int i = 0; i < currentCharacter->GetInventory().size(); i++) {
                currentPage.icons[i] = {true};
                currentPage.icons[i].referencedItem = currentCharacter->GetInventory()[i];
                fmt::println("Assigned item {}", currentPage.icons[i].referencedItem->GetName() );

            }
            for(int i = currentCharacter->GetInventory().size(); i < 40; i++)
            {
                currentPage.icons[i] = {false};
            }
            pages.push_back(currentPage);
        }
        else //TODO
        {
            for (int i = 0; i < 40; i++) {
               // currentPage.icons[i] = currentCharacter->GetInventory()[i]
            }
            if (currentCharacter->GetInventory().size() > 40) {

            }
        }
    }

};






#endif //SDL_BASE_INVENTORY_COMPONENTS_H
