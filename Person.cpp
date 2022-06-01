/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the person class. There are numerous functions used
                that manipulate the players status. See each function description.
***********************************************************************************************************/

#include "Person.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "Space.hpp"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Person::Person()
{
    name = "";
    set_health(100);
    set_mana(100);
    this->position = nullptr;
    max_inventory = 8;
}

/***********************************************************************************************************
** Description: setter for the health
***********************************************************************************************************/
void Person::set_health(int h)
{
    health = h;
}

/***********************************************************************************************************
** Description: Function that will increase player's health. Parameter is the amount added
***********************************************************************************************************/
void Person::increase_health(int h_up)
{
    health = health + h_up;
    // won't allow health to go above maximum health of 100
    if (health > 100)
    {
        health = 100;
    }
}

/***********************************************************************************************************
** Description: Function that will decrease player's health. Parameter is the amount subtracted
***********************************************************************************************************/
void Person::decrease_health(int h_down)
{
    health = health - h_down;
    // will not allow health to go negative
    if (health < 0)
    {
        health = 0;
    }
}

/***********************************************************************************************************
** Description: setter for the mana
***********************************************************************************************************/
void Person::set_mana(int m)
{
    mana = m;
}

/***********************************************************************************************************
** Description: Function that will increase player's mana. Parameter is the amount to be added
***********************************************************************************************************/
void Person::increase_mana(int h_up)
{
    mana = mana + h_up;
    // caps mana at 100
    if (mana > 100)
    {
        mana = 100;
    }
}

/***********************************************************************************************************
** Description: Function that will decrease player's mana. Parameter is the amount subtracted
***********************************************************************************************************/
void Person::decrease_mana(int h_down)
{
    mana = mana - h_down;
    // stops at 0 mana
    if (mana < 0)
    {
        mana = 0;
    }
}

/***********************************************************************************************************
** Description: setter for the player's name
***********************************************************************************************************/
void Person::set_name(string name_in)
{
    name = name_in;
}

/***********************************************************************************************************
** Description: setter for the player's location. Parameter is the room to locate the player in. Function
                only used at the initial creation of the game.
***********************************************************************************************************/
void Person::set_position(Space *new_location)
{
    this->position = new_location;
}

/***********************************************************************************************************
** Description: Moves the player according to the room passed in
***********************************************************************************************************/
void Person::move_top(Space *room)
{
    position = room->get_top();
}

/***********************************************************************************************************
** Description: Moves the player according to the room passed in
***********************************************************************************************************/
void Person::move_left(Space *room)
{
    position = room->get_left();
}

/***********************************************************************************************************
** Description: Moves the player according to the room passed in
***********************************************************************************************************/
void Person::move_right(Space *room)
{
    position = room->get_right();
}

/***********************************************************************************************************
** Description: Moves the player according to the room passed in
***********************************************************************************************************/
void Person::move_bottom(Space *room)
{
    position = room->get_bottom();
}

/***********************************************************************************************************
** Description: Function that will display the player's inventory
***********************************************************************************************************/
void Person::display_inventory()
{
    for (int i = 0; i < inventory.size(); i++)
    {
        cout << "  [" << print_enum(inventory[i]) << "]";
    }
    cout << endl << endl;
    cout << "\t--The maximum amount of items your satchel can hold is " << max_inventory << " items--" << endl;
    cout << "\t\t--You have " << max_inventory - inventory.size() << " spots remaining--" << endl;
}

/***********************************************************************************************************
** Description: Function that will add an item to the player's inventory. Parameter is the item to be
                entered into the vector
***********************************************************************************************************/
void Person::add_item(Game_Items item_in)
{
    // resets inventory flag
    exit_inventory_menu = false;

    // checks if inventory is full
    // if not full then item is added to vector
    if (check_inventory_limit())
    {
        inventory.push_back(item_in);
    }
    // if full then user is prompted to pick an item to remove
    else
    {
        cout << endl;
        cout << "\t~ Inventory is at max capacity. You must choose an item to remove. ~" << endl;

        // loop that will run until an item is dropped or the user decides not to pick up item
        while (!exit_inventory_menu)
        {
            // inventory menu object...creates a menu depending on which items the player is carrying
            Menu inventory_menu;
            inventory_menu.set_menu_header("Which item will be dropped?");
            for (int i = 0; i < inventory.size(); i++)
            {
                string temp_item = print_enum(inventory[i]);
                inventory_menu.add_menu_option(temp_item);
            }
            inventory_menu.add_menu_option("Do not remove an item");
            inventory_menu.display_menu();
            int menu_choice = inventory_menu.get_choice();

            switch (menu_choice)
            {
                case 1: 
                {
                    remove_item(inventory[0]);
                    break;
                }
                case 2: 
                {
                    remove_item(inventory[1]);
                    break;
                }
                case 3: 
                {
                    remove_item(inventory[2]);
                    break;
                }
                case 4: 
                {
                    remove_item(inventory[3]);
                    break;
                }
                case 5: 
                {
                    remove_item(inventory[4]);
                    break;
                }
                case 6: 
                {
                    remove_item(inventory[5]);
                    break;
                }
                case 7: 
                {
                    remove_item(inventory[6]);
                    break;
                }
                case 8: 
                {
                    remove_item(inventory[7]);
                    break;
                }
                case 9:
                {
                    cout << "You have chosen not to remove an item." << endl;
                    exit_inventory_menu = true;
                    break;
                }
            }
        }
    }
}

/***********************************************************************************************************
** Description: Function that will remove an item. Parameter is the item that will be removed from the
                vector.
***********************************************************************************************************/
void Person::remove_item(Game_Items item_out)
{
    // checks to see if the item to be removed is a key item. If it is, the user will be unable to drop
    // the item
    if (item_out == MAP || item_out == FIRE_GAUNTLET || item_out == LIGHTNING_GAUNTLET || 
        item_out == MAGNETIC_GAUNTLET || item_out == WIND_GAUNTLET || item_out == PASSCODE)
    {
        cout << endl;
        cout << "~ That is a key item that is required to complete the training. Unable to ~" << endl;
        cout << "~ drop item. Please select another item to drop. ~" << endl;
    }
    // if an item that is allowed to be dropped it will be removed from the vector
    else
    {
        cout << endl;
        cout << "You will be dropping the [" << print_enum(item_out) << "] It can not be re-obtained." << endl;
        for (int i = 0; i < inventory.size(); i++)
        {
            if (inventory[i] == item_out)
            {
                inventory.erase(inventory.begin() + i);
            }
        }
        exit_inventory_menu = true;
    }
}

/***********************************************************************************************************
** Description: Function that will check for a full inventory. True will be returned if there is room
***********************************************************************************************************/
bool Person::check_inventory_limit()
{
    if (inventory.size() < max_inventory)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/***********************************************************************************************************
** Description: Function that checks for a specific item in the vector. Parameter is the item searched for
***********************************************************************************************************/
bool Person::item_check(Game_Items item_check)
{
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i] == item_check)
        {
            return true;
        }
    }
    return false;
}

/***********************************************************************************************************
** Description: getter for player's health
***********************************************************************************************************/
int Person::get_health()
{
    return health;
}

/***********************************************************************************************************
** Description: getter for player's mana
***********************************************************************************************************/
int Person::get_mana()
{
    return mana;
}

/***********************************************************************************************************
** Description: getter for player's name
***********************************************************************************************************/
string Person::get_name()
{
    return name;
}

/***********************************************************************************************************
** Description: getter for name of player's location
***********************************************************************************************************/
string Person::get_position()
{
    return position->get_name();
}

/***********************************************************************************************************
** Description: Function that returns the enum as a string
***********************************************************************************************************/
string Person::print_enum(Game_Items item)
{
    if (item == MAP)
    {
        return "Map";
    }
    else if (item == FIRE_GAUNTLET)
    {
        return "Fire Gauntlet";
    }
    else if (item == LIGHTNING_GAUNTLET)
    {
        return "Lightning Gauntlet";
    }
    else if (item == MAGNETIC_GAUNTLET)
    {
        return "Magnetic Gauntlet";
    }
    else if (item == WIND_GAUNTLET)
    {
        return "Wind Gauntlet";
    }
    else if (item == PASSCODE)
    {
        return "Passcode";
    }
    else if (item == BOOKS)
    {
        return "Books";
    }
    else if (item == SWORD_SHIELD)
    {
        return "Sword and Shield";
    }
    else if (item == FANCY_ROBES)
    {
        return "Fancy Robes";
    }
    else if (item == SKULL_HEAD)
    {
        return "Skull Head";
    }
    else if (item == HEALTH_POTION)
    {
        return "Health Potion";
    }
    else
    {
        return "Mana Potion";
    }
}