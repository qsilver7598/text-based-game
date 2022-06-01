/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the slchemist room class. It is derived from the space 
                class. The functions defined are used within the room for displaying events and modifying the
                player's stats.
***********************************************************************************************************/

#include "Space.hpp"
#include "Alchemist_Room.hpp"
#include "Menu.hpp"
#include "Person.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/***********************************************************************************************************
** Description: Function that is called when the user selects the red potion option
***********************************************************************************************************/
void Alchemist_Room::red_potion_event()
{
    cout << endl;
    cout << "You walk over to the red potion sitting on the workbench. Upon inspection you see" << endl;
    cout << "the words health etched into the bottle." << endl;
    cout << "\t**Sweet, health potion you think to yourself." << endl;
    cout << "\t--You place the health potion into your satchel--" << endl;
    health_potion_obt = true;
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the blue potion option
***********************************************************************************************************/
void Alchemist_Room::blue_potion_event()
{
    cout << endl;
    cout << "You grab the blue potion that is sitting upon the shelf. You can't make out the" << endl;
    cout << "exact wording but from your studies, the most common blue potion is the mana potion." << endl;
    cout << "There is another blue potion that is similar which transforms you into a majestic" << endl;
    cout << "llama. However that is one of the rarest out there. You decide to take your chances." << endl;
    cout << "\t--You place the assumed mana potion into your satchel--" << endl;
    mana_potion_obt = true;
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the wardrobe option
***********************************************************************************************************/
void Alchemist_Room::wardrobe_event(Person &player)
{
    int choice;

    cout << endl;
    if (fancy_robes_obt)
    {
        cout << "You have already searched the wardrobe. The only thing left is the old dirty lab" << endl;
        cout << "coat. You have no use for that." << endl;
    }
    else
    {
        cout << "You search through the wardrobe and find a nice set of wizardary robes. You wonder" << endl;
        cout << "how you would look wearing those. You very well might need them after you pass" << endl;
        cout << "this exam. You also spot an old dirty lab coat." << endl;
        cout << "\t**That has seen better days, you say out loud to yourself." << endl;

        Menu cabinet_menu;
        cabinet_menu.set_menu_header("What will you do?");
        cabinet_menu.add_menu_option("Take the fancy robes");
        cabinet_menu.add_menu_option("Leave the robes in the closet");
        cabinet_menu.display_menu();
        choice = cabinet_menu.get_choice();

        cout << endl;
        switch (choice)
        {
            case 1: // user gets robes
            {
                cout << "\t--You place the fancy robes into your satchel--" << endl;
                player.add_item(FANCY_ROBES);
                if (player.item_check(FANCY_ROBES))
                {
                    fancy_robes_obt = true;
                }
                break;
            }
            case 2: // user leaves robes alone
            {
                cout << "You decide the robes probably wouldn't fit your chiseled physique." << endl;
                break;
            }
        }
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the cabinet option
***********************************************************************************************************/
void Alchemist_Room::cabinet_event(Person &player)
{    
    int choice;

    cout << endl;
    if (skull_head_obt)
    {
        cout << "You have already collected the skull head. You don't see anything else inside" << endl;
        cout << "the cabinet." << endl;
    }
    else if (cabinet_checked)
    {
        cout << "You reflect upon the last time you opened the cabinet and your face still" << endl;
        cout << "burns from the memory." << endl;
        cout << "\t**I better not go through that again, you think to yourself." << endl;
    }
    else
    {
        cout << "As you approach the cabinet, you notice unfamilier runes enscribed along the" << endl;
        cout << "border of the cabinet. You open the door and your face is suddenly engulfed" << endl;
        cout << "in a blue fire. It burns but strangely the sensation is ice cold. After a few" << endl;
        cout << "seconds the fire dissipates and you are greeted with a (I kid you not) a" << endl;
        cout << "laughing skull. 'I get a kick out of that everytime' the skull said. 'My name" << endl;
        cout << "is Bob. I am your arcane crime fighting sidekick now. You know, since you found" << endl;
        cout << "me and all. So what do you say. Can I come with?'" << endl;

        Menu cabinet_menu;
        cabinet_menu.set_menu_header("What will you do?");
        cabinet_menu.add_menu_option("Grab the talking head");
        cabinet_menu.add_menu_option("Close the cabinet as fast as you can");
        cabinet_menu.display_menu();
        choice = cabinet_menu.get_choice();

        cout << endl;
        switch (choice)
        {
            case 1: // user gets skull
            {
                cout << "\t--You place the talkin head into your satchel--" << endl;
                cout << "\t**You hear muffled talking. Sounds like it said 'Cozy'. Well good to" << endl;
                cout << "\t**know he enjoys it in there, you say to yourself." << endl;
                cout << "\t--You lost 20 health points due to Bob's hilarious prank--" << endl;
                player.decrease_health(20);
                player.add_item(SKULL_HEAD);
                if (player.item_check(SKULL_HEAD))
                {
                    skull_head_obt = true;
                }
                cabinet_checked = true;
                break;
            }
            case 2: // user closes door
            {
                cout << "You hastily close the door and back away from the cabinet." << endl;
                cout << "--You lost 20 health points due to the assualt from the talking head--" << endl;
                player.decrease_health(20);
                cabinet_checked = true;
                break;
            }
        }
    }
    cabinet_checked = true;
}

/***********************************************************************************************************
** Description: Function that returns the room the user wants to move to
***********************************************************************************************************/
Room_Name Alchemist_Room::move_menu()
{
    int choice;

    Menu move;
    move.set_menu_header("Which room would you like to move to?");
    move.add_menu_option("Library");
    move.add_menu_option("Stay in Alchemist Room");
    move.display_menu();
    choice = move.get_choice();

    switch (choice)
    {
        case 1: // user moved to puzzle room
        {
            cout << endl << "\tMoving to the Library..." << endl;
            return LIBRARY;
        }
        case 2: // user stayed alchemist room
        {
            return ALCHEMIST;
        }
    }
}

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Alchemist_Room::Alchemist_Room()
{
    fancy_robes_obt = false;
    skull_head_obt = false;
    health_potion_obt = false;
    mana_potion_obt = false;
    cabinet_checked = false;
    fog_cleared = false;
    entered_portal = false;
    name = "Alchemist Room";

    this->top = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->bottom = nullptr;
}

/***********************************************************************************************************
** Description: Function used in displaying the foyer map. The map is read from a txt file that has the
                map printed within.
***********************************************************************************************************/
void Alchemist_Room::display_room()
{
    string line;
    std::ifstream infile;

    if (fog_cleared)
    {
        infile.open("special_alchemist.txt");
    }
    else
    {
        infile.open("alchemist.txt");
    }

    if (!infile.is_open())
    {
        cout << "There was an error opening the file." << endl;
    }
    else 
    {
        while (getline(infile, line))
        {
            cout << line << endl;
        }
    }

    infile.close();
}

/***********************************************************************************************************
** Description: Function controls the flow of the room. Parameter is a reference to the player object
***********************************************************************************************************/
Room_Name Alchemist_Room::display_room_events(Person &player)
{
    int menu_choice;

    if (!fog_cleared)
    {
        cout << endl << "\t--You are in the Alchemist Room--" << endl << endl;
        cout << "Your eyes are burning by the magical fog that is covering this place. If only you" << endl;
        cout << "had a way to clear out the room." << endl;

        if (player.item_check(WIND_GAUNTLET))
        {
            cout << endl;
            cout << "Would you like to equip your Wind Gauntlet and use the stored energy in the" << endl;
            cout << "runes to clear out the fog in this room." << endl;

            Menu yes_no;
            yes_no.set_menu_header("What is your decision.");
            yes_no.add_menu_option("Yes");
            yes_no.add_menu_option("No");
            yes_no.display_menu();
            menu_choice = yes_no.get_choice();

            switch (menu_choice)
            {
                case 1: // user equips gauntlets
                {
                    if (player.get_mana() < 2)
                    {
                        cout << endl;
                        cout << "~ You do not have enough mana to activate the gauntlet. You must find ~" << endl;
                        cout << "~ a way to recover your lifeforce. ~" << endl;
                    }
                    else
                    {
                        cout << endl;
                        cout << "With the power of wind surging through you, you are able to clear" << endl;
                        cout << "out the fog from within the Alchemist Room revealing a wizards lab." << endl;
                        cout << "There are beakers and potions and all kinds of magical artifacts" << endl;
                        cout << "scattered throughout the room." << endl;
                        cout << "\t--Your mana is drained by 2 points by using the gauntlet--" << endl;
                        player.decrease_mana(2);
                        fog_cleared = true;
                    }
                    return ALCHEMIST;
                }
                case 2: // user does not equip gauntlets
                {
                    cout << endl;
                    cout << "Unfortunately with the suffocating fog you are forced to retreat" << endl;
                    cout << "back into the Library." << endl;
                    return LIBRARY;
                }
            }
        }
        else
        {
            cout << endl;
            cout << "\t**You think to yourself, there must be a magical item I can get to remove" << endl;
            cout << "\tall of this fog. You retreat back into the Library." << endl;
            return LIBRARY;
        }
    }
    else
    {
        if (!health_potion_obt && !mana_potion_obt)
        {
            cout << endl << "\t--You are in the Alchemist Room--" << endl << endl;
            cout << "Looking around this crazy cool lab, you spot all sorts of things to check" << endl;
            cout << "out. However you force yourself to stick to the mission at hand. You spot" << endl;
            cout << "two beakers of familiar looking potions. One of the beakers is sitting on" << endl;
            cout << "the on the workstation and the other is up on the shelf across the room." << endl;
            cout << "You notice a large cabinet and a wardrobe within the room. There could be" << endl;
            cout << "things of interest stored in there." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Grab red potion");
            library_menu.add_menu_option("Grab blue potion");
            library_menu.add_menu_option("Search the Wardrobe");
            library_menu.add_menu_option("Search the cabinets");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user grabs red potion
                {
                    red_potion_event();
                    player.add_item(HEALTH_POTION);
                    if (player.item_check(HEALTH_POTION))
                    {
                        health_potion_obt = true;
                    }
                    return ALCHEMIST;
                }
                case 2: // user grabs blue potion
                {
                    blue_potion_event();
                    player.add_item(MANA_POTION);
                    if (player.item_check(MANA_POTION))
                    {
                        mana_potion_obt = true;
                    }
                    return ALCHEMIST;
                }
                case 3: // user checks wardrobe
                {
                    wardrobe_event(player);
                    return ALCHEMIST;
                }
                case 4: // user checks cabinets
                {
                    cabinet_event(player);
                    return ALCHEMIST;
                }
                case 5: // user wants to move rooms
                {
                    return move_menu();
                }
                case 6: // user paused the game
                {
                    return PAUSE;
                }
            }
        }
        if (health_potion_obt && !mana_potion_obt)
        {
            cout << endl << "\t--You are in the Alchemist Room--" << endl << endl;
            cout << "After obtaining the health potion you feel much better about your chances" << endl;
            cout << "of succeeding this mission. Let's keep exploring." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Grab blue potion");
            library_menu.add_menu_option("Search the Wardrobe");
            library_menu.add_menu_option("Search the cabinets");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user grabs blue potion
                {
                    blue_potion_event();
                    player.add_item(MANA_POTION);
                    if (player.item_check(MANA_POTION))
                    {
                        mana_potion_obt = true;
                    }
                    return ALCHEMIST;
                }
                case 2: // user checks wardrobe
                {
                    wardrobe_event(player);
                    return ALCHEMIST;
                }
                case 3: // user checks cabinets
                {
                    cabinet_event(player);
                    return ALCHEMIST;
                }
                case 4: // user wants to move rooms
                {
                    return move_menu();
                }
                case 5: // user paused the game
                {
                    return PAUSE;
                }
            }
        }
        if (!health_potion_obt && mana_potion_obt)
        {
            cout << endl << "\t--You are in the Alchemist Room--" << endl << endl;
            cout << "After obtaining the mana potion you feel much better about your chances" << endl;
            cout << "of succeeding this mission. Let's keep exploring." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Grab red potion");
            library_menu.add_menu_option("Search the Wardrobe");
            library_menu.add_menu_option("Search the cabinets");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user grabs red potion
                {
                    red_potion_event();
                    player.add_item(HEALTH_POTION);
                    if (player.item_check(HEALTH_POTION))
                    {
                        health_potion_obt = true;
                    }
                    return ALCHEMIST;
                }
                case 2: // user checks wardrobe
                {
                    wardrobe_event(player);
                    return ALCHEMIST;
                }
                case 3: // user checks cabinets
                {
                    cabinet_event(player);
                    return ALCHEMIST;
                }
                case 4: // user wants to move rooms
                {
                    return move_menu();
                }
                case 5: // user paused the game
                {
                    return PAUSE;
                }
            }
        }
        if (health_potion_obt && mana_potion_obt)
        {
            cout << endl << "\t--You are in the Alchemist Room--" << endl << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Search the Wardrobe");
            library_menu.add_menu_option("Search the cabinets");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user checks wardrobe
                {
                    wardrobe_event(player);
                    return ALCHEMIST;
                }
                case 2: // user checks cabinets
                {
                    cabinet_event(player);
                    return ALCHEMIST;
                }
                case 3: // user wants to move rooms
                {
                    return move_menu();
                }
                case 4: // user paused the game
                {
                    return PAUSE;
                }
            }
        }
    }
}