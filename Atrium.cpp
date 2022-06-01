/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the atrium class. It is derived from the space 
                class. The functions defined are used within the room for displaying events and modifying the
                player's stats.
***********************************************************************************************************/

#include "Space.hpp"
#include "Atrium.hpp"
#include "Menu.hpp"
#include "Person.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/***********************************************************************************************************
** Description: Function that is called when the user selects the generator option
***********************************************************************************************************/
void Atrium::generator_event(Person &player)
{
    int menu_choice;

    cout << endl;
    if (player.item_check(LIGHTNING_GAUNTLET))
    {
        cout << "Would you like to equip your Lightning Gauntlet and use the stored energy in the" << endl;
        cout << "runes to activate the generator." << endl;

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
                    cout << "With the power of electricity crackling around you, you raise your" << endl;
                    cout << "hand to the generator and release the stored energy within the gauntlet." << endl;
                    cout << "The generator whirls to life." << endl;
                    cout << "\t--Your mana is drained by 2 points by using the gauntlet--" << endl;
                    player.decrease_mana(2);
                    generator_on = true;
                }
                break;
            }
            case 2: // user does not equip gauntlets
            {
                cout << "You are hesitant to act in fear of a trap." << endl;
                break;
            }
        }
    }
    else
    {
        cout << "\t**You think to yourself, there must be a magical item I can get to activate" << endl;
        cout << "\tthe generator." << endl;
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the vine option
***********************************************************************************************************/
void Atrium::vine_event(Person &player)
{
    int menu_choice;

    cout << endl;
    if (player.item_check(FIRE_GAUNTLET))
    {
        cout << "Would you like to equip your Fire Gauntlet and use the stored energy in the" << endl;
        cout << "runes to burn the vines to ashes." << endl;

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
                    cout << "With the power of burning fire radiating from your hand, you raise your" << endl;
                    cout << "hand to the vines and release the stored energy within the gauntlet." << endl;
                    cout << "The vines catch fire and quickly burn away revealing a dimly lit hallway." << endl;
                    cout << "\t--Your mana is drained by 2 points by using the gauntlet--" << endl;
                    player.decrease_mana(2);
                    vines_cleared = true;
                }
                break;
            }
            case 2: // user does not equip gauntlets
            {
                cout << "You are hesitant to act in fear of a trap." << endl;
                break;
            }
        }
    }
    else
    {
        cout << "\t**You think to yourself, there must be a magical item I can get to clear" << endl;
        cout << "\tthe vines." << endl;
    }    
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the portal option
***********************************************************************************************************/
void Atrium::portal_event()
{
    cout << endl;
    cout << "You walk down the hallway and in the distance you see the portal glowing with power." << endl;
    cout << "You reach the end and step through the portal." << endl;
    entered_portal = true;
}

/***********************************************************************************************************
** Description: Function that returns the room the user wants to move to
***********************************************************************************************************/
Room_Name Atrium::move_menu()
{
    int choice;

    Menu move;
    move.set_menu_header("Which room would you like to move to?");
    move.add_menu_option("Foyer");
    move.add_menu_option("Stay in Outdoor Atrium");
    move.display_menu();
    choice = move.get_choice();

    switch (choice)
    {
        case 1: // user moved to foyer room
        {
            cout << endl << "\tMoving to the Foyer..." << endl;
            return FOYER;
        }
        case 2: // user stayed atrium
        {
            return ATRIUM;
        }
    }
}

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Atrium::Atrium()
{
    vines_cleared = false;
    generator_on = false;
    fog_cleared = true;
    entered_portal = false;
    name = "Outdoor Atrium";

    this->top = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->bottom = nullptr;
}

/***********************************************************************************************************
** Description: Function used in displaying the foyer map. The map is read from a txt file that has the
                map printed within.
***********************************************************************************************************/
void Atrium::display_room()
{
    string line;
    std::ifstream infile;

    infile.open("atrium.txt");

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
Room_Name Atrium::display_room_events(Person &player)
{
    int menu_choice;

    if (!vines_cleared && !generator_on)
    {
        cout << endl << "\t--You are in the Outdoor Atrium--" << endl << endl;
        cout << "You have finally made it beyond the locked door and into the Outdoor Atrium." << endl;
        cout << "Looking around the area, you see lots of plants and flowers. You see a small" << endl;
        cout << "pond in the corner of the area. Next to the pond you see a silent generator." << endl;
        cout << "And on the North wall you see a bunch of vines covering, what looks like a" << endl;
        cout << "hallway. You figure down that hallway is the location of the portal." << endl;

        Menu atrium_menu;
        atrium_menu.set_menu_header("What will you do?");
        atrium_menu.add_menu_option("Examine the Vines");
        atrium_menu.add_menu_option("Examine the generator");
        atrium_menu.add_menu_option("Move to a different room");
        atrium_menu.add_menu_option("Pause Menu");
        atrium_menu.display_menu();
        menu_choice = atrium_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user examines the vines
            {
                vine_event(player);
                return ATRIUM;
            }
            case 2: // user examines the vines
            {
                generator_event(player);
                return ATRIUM;
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
    if (vines_cleared && !generator_on)
    {
        cout << endl << "\t--You are in the Outdoor Atrium--" << endl << endl;
        cout << "With the vines cleared you walk down the hallway to the end. You do not see" << endl;
        cout << "any other rooms or exits. However you do see a rune circle built into the" << endl;
        cout << "ground. You walk back out into the atrium looking for a way to turn the" << endl;
        cout << "portal on." << endl;

        Menu atrium_menu;
        atrium_menu.set_menu_header("What will you do?");
        atrium_menu.add_menu_option("Examine the generator");
        atrium_menu.add_menu_option("Move to a different room");
        atrium_menu.add_menu_option("Pause Menu");
        atrium_menu.display_menu();
        menu_choice = atrium_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user examines the generator
            {
                generator_event(player);
                return ATRIUM;
            }
            case 2: // user wants to move rooms
            {
                return move_menu();
            }
            case 3: // user paused the game
            {
                return PAUSE;
            }
        }
    }
    if (!vines_cleared && generator_on)
    {
        cout << endl << "\t--You are in the Outdoor Atrium--" << endl << endl;
        cout << "After turning the generator on you hear a humming sound coming from down the" << endl;
        cout << "hallway. **That must be the portal you think to yourself. Just need to find" << endl;
        cout << "a way down there." << endl;

        Menu atrium_menu;
        atrium_menu.set_menu_header("What will you do?");
        atrium_menu.add_menu_option("Examine the Vines");
        atrium_menu.add_menu_option("Move to a different room");
        atrium_menu.add_menu_option("Pause Menu");
        atrium_menu.display_menu();
        menu_choice = atrium_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user examines the vines
            {
                vine_event(player);
                return ATRIUM;
            }
            case 2: // user wants to move rooms
            {
                return move_menu();
            }
            case 3: // user paused the game
            {
                return PAUSE;
            }
        }
    }
    if (vines_cleared && generator_on)
    {
        cout << endl << "\t--You are in the Outdoor Atrium--" << endl << endl;
        cout << "Everything is clear and the portal is on." << endl;

        Menu atrium_menu;
        atrium_menu.set_menu_header("What will you do?");
        atrium_menu.add_menu_option("Enter Portal");
        atrium_menu.add_menu_option("Move to a different room");
        atrium_menu.add_menu_option("Pause Menu");
        atrium_menu.display_menu();
        menu_choice = atrium_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user enters portal
            {
                portal_event();
                return ATRIUM;
            }
            case 2: // user wants to move rooms
            {
                return move_menu();
            }
            case 3: // user paused the game
            {
                return PAUSE;
            }
        }
    }

}