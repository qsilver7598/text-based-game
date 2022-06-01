/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the foyer class. It is derived from the space class.
                The functions defined are used within the room for displaying events and modifying the
                player's stats.
***********************************************************************************************************/

#include "Space.hpp"
#include "Foyer.hpp"
#include "Menu.hpp"
#include "Person.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/***********************************************************************************************************
** Description: Function that is called when the user selects the map option
***********************************************************************************************************/
void Foyer::map_event()
{
    cout << endl;
    cout << "You walk over to the small table and pick up the map. The moment your hands touch" << endl;
    cout << "the map you hear large hissing from either side of you. Your gaze quickly jumps" << endl;
    cout << "up to the side of the room and you see the fog clearing out of the room. Behind" << endl;
    cout << "the smoke, two doors on either side are revealed." << endl;
    cout << "\t--You place the map in your satchel--" << endl;
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the fountain option
***********************************************************************************************************/
void Foyer::fountain_event()
{
    cout << endl;
    cout << "You take a drink from the refreshing fountain. You feel the rejuvinating energies" << endl;
    cout << "return lifeforce to your body." << endl;
    cout << "\t--You recover 8 mana points--" << endl;
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the gauntlet option
***********************************************************************************************************/
void Foyer::gauntlet_event()
{
    cout << endl;
    cout << "You walk over to the pedestal and pick up the gauntlet prepared for an Indiana" << endl;
    cout << "Jones like run from a boulder. Surprisingly, nothing happens. You examine the" << endl;
    cout << "gauntlet and discover some runes with wind energy weaved into them. You try the" << endl;
    cout << "metal gloves on and can feel the wind energy coursing through your body." << endl;
    cout << "\t--You place the Wind Gauntlet in your satchel--" << endl;
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the atrium option. Parameter is a reference
                to the player object
***********************************************************************************************************/
void Foyer::check_atrium(Person &player)
{
    cout << endl;
    cout << "You walk over to the door and try to open it. It's locked! There appears" << endl;
    cout << "to be a passcode that needs to be entered on the door." << endl;
    // executes this part if the player had received the passcode from the puzzle room
    if (player.item_check(PASSCODE))
    {
        cout << "\tYou enter the code written on the scroll." << endl;
        cout << "\t--The Outdoor Atrium door opens!--" << endl;
        atrium_unlocked = true;
    }
    else
    {
        cout << "\t**I need to find this passcode. It might be important," << endl;
        cout << "\tyou think to yourself." << endl;
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the rubble option
***********************************************************************************************************/
void Foyer::rubble_event()
{
    cout << endl;
    if (rubble_checked)
    {
        cout << "You remember that strange encounter with the butterfly and prefer not to attempt" << endl;
        cout << "to wake the flutter of butterflys potentially hiding amongst the rubble." << endl;
    }
    else
    {
        cout << "You check through the stair rubble for anything you could use." << endl;
        cout << "\tYou are attacked by a startled butterfly." << endl;
        cout << "\t--You take 10 points of damage to your health.--" << endl;
        cout << "\t**That was weird you think to yourself." << endl;
        rubble_checked = true;
    }
}

/***********************************************************************************************************
** Description: Function that will return which room the player wants to move to
***********************************************************************************************************/
Room_Name Foyer::move_menu()
{
    int choice;

    // move menu object
    Menu move;
    move.set_menu_header("Which room would you like to move to?");
    move.add_menu_option("Puzzle Room");
    move.add_menu_option("Library");
    move.add_menu_option("Outdoor Atrium");
    move.add_menu_option("Stay in Foyer");
    move.display_menu();
    choice = move.get_choice();

    switch (choice)
    {
        case 1: // user moved to puzzle room
        {
            cout << endl << "\tMoving to the Puzzle Room..." << endl;
            return PUZZLE;
        }
        case 2: // user moved to library
        {
            cout << endl << "\tMoving to the Library..." << endl;
            return LIBRARY;
        }
        case 3: // user moved to outdoor atrium
        {
            if (atrium_unlocked)
            {
                cout << endl << "\tMoving to the Outdoor Atrium..." << endl;
                return ATRIUM;
            }
            else
            {
                cout << endl << "The Outdoor Atrium is still locked." << endl;
                return FOYER;
            }
        }
        case 4: // user stayed in foyer
        {
            return FOYER;
        }
    }
}

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Foyer::Foyer()
{
    wind_gaunt_obt = false;
    map_obt = false;
    atrium_unlocked = false;
    rubble_checked = false;
    fog_cleared = true;
    entered_portal = false;
    name = "Foyer";

    this->top = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->bottom = nullptr;
}

/***********************************************************************************************************
** Description: Function used in displaying the foyer map. The map is read from a txt file that has the
                map printed within.
***********************************************************************************************************/
void Foyer::display_room()
{
    string line;
    std::ifstream infile;

    if (atrium_unlocked)
    {
        infile.open("special_foyer.txt");
    }
    else
    {
        infile.open("foyer.txt");
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
Room_Name Foyer::display_room_events(Person &player)
{
    int menu_choice;

    // runs if the map and the gauntlet have not been picked up. also if the atrium is still locked
    if (!map_obt && !wind_gaunt_obt && !atrium_unlocked)
    {
        cout << endl << "\t--You are in the Foyer--" << endl << endl;
        cout << "Your first look upon the Foyer is an unpleasant one. There are dark shadows eerily" << endl;
        cout << "dancing all around you created by the lighted torches upon the wall. You walk over" << endl;
        cout << "to one of the torches and attempt to pry it off the wall. It doesn't budge. They" << endl;
        cout << "are bolted on pretty tight. You notice a second floor jutting out above and all" << endl;
        cout << "around you. You know you won't be able to go that way because the stairs are" << endl;
        cout << "nothing more than rubble at this point. You see on the far side of the room a " << endl;
        cout << "door labled 'Outdoor Atrium' and a golden light shining down upon a pedestal which" << endl;
        cout << "houses a shiny gauntlet. You also spot a small map located on a small table" << endl;
        cout << "next to you. Finally you see a fountain to your left." << endl;

        Menu foyer_menu;
        foyer_menu.set_menu_header("What will you do?");
        foyer_menu.add_menu_option("Pick up map");
        foyer_menu.add_menu_option("Pick up gauntlet");
        foyer_menu.add_menu_option("Check the Atrium Door");
        foyer_menu.add_menu_option("Search through the rubble around the stairs");
        foyer_menu.add_menu_option("Check fountain");
        foyer_menu.add_menu_option("Pause Menu");
        foyer_menu.display_menu();
        menu_choice = foyer_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user picked up map
            {
                map_event();
                player.add_item(MAP);
                if (player.item_check(MAP))
                {
                    map_obt = true;
                }
                return FOYER;
            }
            case 2: // user picked up gauntlet
            {
                gauntlet_event();
                player.add_item(WIND_GAUNTLET);
                if (player.item_check(WIND_GAUNTLET))
                {
                    wind_gaunt_obt = true;
                }
                return FOYER;
            }
            case 3: // user checked the door
            {
                check_atrium(player);
                return FOYER;
            }
            case 4: // user searched through the rubble
            {
                rubble_event();
                player.decrease_health(10);
                return FOYER;
            }
            case 5: // user checked the fountain
            {
                fountain_event();
                player.increase_mana(8);
                return FOYER;
            }
            case 6: // user paused the game
            {
                return PAUSE;
            }
        }
    }
    
    // runs if map picked up and gauntlets still in the room. Also with atrium locked
    if (map_obt && !wind_gaunt_obt && !atrium_unlocked)
    {
        cout << endl << "\t--You are in the Foyer--" << endl << endl;
        cout << "There are multiple rooms to explore. However, the soft glow of the gauntlet" << endl;
        cout << "keeps grabbing your attention." << endl;

        Menu foyer_menu;
        foyer_menu.set_menu_header("What will you do?");
        foyer_menu.add_menu_option("Pick up gauntlet");
        foyer_menu.add_menu_option("Check the Atrium Door");
        foyer_menu.add_menu_option("Search through the rubble around the stairs");
        foyer_menu.add_menu_option("Check Fountain");
        foyer_menu.add_menu_option("Move to a different room");
        foyer_menu.add_menu_option("Pause Menu");
        foyer_menu.display_menu();
        menu_choice = foyer_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user picked up gauntlet
            {
                gauntlet_event();
                player.add_item(WIND_GAUNTLET);
                if (player.item_check(WIND_GAUNTLET))
                {
                    wind_gaunt_obt = true;
                }
                return FOYER;
            }
            case 2: // user checked the door
            {
                check_atrium(player);
                return FOYER;
            }
            case 3: // user searched through the rubble
            {
                rubble_event();
                player.decrease_health(10);
                return FOYER;
            }
            case 4: // user checked the fountain
            {
                fountain_event();
                player.increase_mana(8);
                return FOYER;
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

    // runs if the map and gauntlet has been picked up with the door locked
    if (map_obt && wind_gaunt_obt && !atrium_unlocked)
    {
        cout << endl << "\t--You are in the Foyer--" << endl << endl;
        cout << "\t**Now I just need to figure out how to get that door open." << endl;

        Menu foyer_menu;
        foyer_menu.set_menu_header("What will you do?");
        foyer_menu.add_menu_option("Check the Atrium Door");
        foyer_menu.add_menu_option("Search through the rubble around the stairs");
        foyer_menu.add_menu_option("Check Fountain");
        foyer_menu.add_menu_option("Move to a different room");
        foyer_menu.add_menu_option("Pause Menu");
        foyer_menu.display_menu();
        menu_choice = foyer_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user checked the door
            {
                check_atrium(player);
                return FOYER;
            }
            case 2: // user searched through the rubble
            {
                rubble_event();
                player.decrease_health(10);
                return FOYER;
            }
            case 3: // user checked the fountain
            {
                fountain_event();
                player.increase_mana(8);
                return FOYER;
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

    // runs with the gauntlet picked up and the map still in the room with the atrium locked
    if (!map_obt && wind_gaunt_obt && !atrium_unlocked)
    {
        cout << endl << "\t--You are in the Foyer--" << endl << endl;
        cout << "\t**With the power of wind in hand, It's time to get exploring." << endl;

        Menu foyer_menu;
        foyer_menu.set_menu_header("What will you do?");
        foyer_menu.add_menu_option("Pick up map");
        foyer_menu.add_menu_option("Check the Atrium Door");
        foyer_menu.add_menu_option("Search through the rubble around the stairs");
        foyer_menu.add_menu_option("Check Fountain");
        foyer_menu.add_menu_option("Pause Menu");
        foyer_menu.display_menu();
        menu_choice = foyer_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user picked up map
            {
                map_event();
                player.add_item(MAP);
                if (player.item_check(MAP))
                {
                    map_obt = true;
                }
                return FOYER;
            }
            case 2: // user checked the door
            {
                check_atrium(player);
                return FOYER;
            }
            case 3: // user searched through the rubble
            {
                rubble_event();
                player.decrease_health(10);
                return FOYER;
            }
            case 4: // user checked the fountain
            {
                fountain_event();
                player.increase_mana(8);
                return FOYER;
            }
            case 5: // user paused the game
            {
                return PAUSE;
            }
        }
    }

    // runs if map and gauntlet obtained and atrium unlocked
    if (map_obt && wind_gaunt_obt && atrium_unlocked)
    {
        cout << endl << "\t--You are in the Foyer--" << endl << endl;

        Menu foyer_menu;
        foyer_menu.set_menu_header("What will you do?");
        foyer_menu.add_menu_option("Search through the rubble around the stairs");
        foyer_menu.add_menu_option("Check Fountain");
        foyer_menu.add_menu_option("Move to a different room");
        foyer_menu.add_menu_option("Pause Menu");
        foyer_menu.display_menu();
        menu_choice = foyer_menu.get_choice();

        switch (menu_choice)
        {
            case 1: // user wants to check rubble
            {
                rubble_event();
                player.decrease_health(10);
                return FOYER;
            }
            case 2: // user checked the fountain
            {
                fountain_event();
                player.increase_mana(8);
                return FOYER;
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