/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the game class. There are 4 functions. One to display
                the map, one to run the main portion of game, one to clear the console, and one
                to display the pause menu.
***********************************************************************************************************/

#include "Game.hpp"
#include "Menu.hpp"
#include "InputVal.hpp"
#include "Person.hpp"
#include "Space.hpp"
#include "Foyer.hpp"
#include "Puzzle_Room.hpp"
#include "Library.hpp"
#include "Treasure_Room.hpp"
#include "Alchemist_Room.hpp"
#include "Atrium.hpp"

#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Game::Game()
{
    game_won = false;
    exit_game = false;
    death = false;
}

/***********************************************************************************************************
** Description: This function will display the map to the user. The parameter is a reference to the person
                object which carries the inventory items. The function opens and reads from a txt file
                which has the map printed within.
***********************************************************************************************************/
void Game::display_map(Person &player_in)
{
    if (player_in.item_check(MAP))
    {
        string line;
        std::ifstream infile("map.txt");

        if (!infile.is_open())
        {
            cout << "There was an error opening the file." << endl;
        }
        else
        {
            // reads line by line the text file
            while (getline(infile, line))
            {
                cout << line << endl;
            }
        }

        infile.close();
    }
    else
    {
        cout << "You do not currently have a map of the place." << endl;
    }
}

/***********************************************************************************************************
** Description: This function is the bulk of the game control. Each room is created and the player is also
                created. All pointers are assigned the proper locations according to the map. See inline
                comments throughout the function to see what specific parts do.
***********************************************************************************************************/
void Game::start_game()
{
    int menu_choice;

    // resets flag variables
    game_won = false;
    exit_game = false;
    death = false;

    // creation of the room objects
    Space *foyer1 = new Foyer;
    Space *library1 = new Library;
    Space *alchemist1 = new Alchemist_Room;
    Space *puzzle1 = new Puzzle_Room;
    Space *treasure1 = new Treasure_Room;
    Space *atrium1 = new Atrium;

    // person object
    Person player;

    // sets pointers for the foyer
    foyer1->set_top(atrium1);
    foyer1->set_left(puzzle1);
    foyer1->set_right(library1);

    // sets pointers for the library
    library1->set_top(alchemist1);
    library1->set_left(foyer1);

    // sets pointers for the alchemist room
    alchemist1->set_bottom(library1);

    // sets pointers for the puzzle room
    puzzle1->set_top(treasure1);
    puzzle1->set_right(foyer1);

    // sets pointers for the treasure room
    treasure1->set_bottom(puzzle1);

    // sets pointers for the atrium
    atrium1->set_bottom(foyer1);

    // sets the player pointer to the first location
    player.set_position(foyer1);

    clear_console();

    // game start
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "                       Capstone Wizard Course                              " << endl;
    cout << "---------------------------------------------------------------------------" << endl << endl;
    cout << "Welcome... uh, wait what's your name? ";

    // getting players name
    string input;
    getline(cin, input);
    string name = check_string(input);
    player.set_name(name);

    // introduces the objective
    cout << endl;
    cout << "Ah yes, thank you. Welcome to your final test " << player.get_name() 
         << ". Should you pass this final" << endl;
    cout << "challenge you will be recognized as a master wizard and accepted into the prestigious" << endl;
    cout << "Council of Wizardry." << endl << endl;
    cout << "For this challenge you will be tasked with finding a way out of the Magic Mansion. Upon" << endl;
    cout << "entering, the mansion will be sealed off and you will have to find your way out. This" << endl;
    cout << "will not be an easy task. But you should be ready for this challenge." << endl << endl;

    // continue menu object
    Menu continue_menu;
    continue_menu.set_menu_header("Are you ready to take on the challenge and become a master wizard?");
    continue_menu.add_menu_option("Let's do it!");
    continue_menu.add_menu_option("On second thought, I need more training.");
    continue_menu.display_menu();
    menu_choice = continue_menu.get_choice();

    switch (menu_choice)
    {
        case 1: // user is ready
        {
            cout << endl << "Awesome! Continue into the mansion. Good Luck " << player.get_name()
                 << "!" << endl;
            cout << "\n\n\n";
            cout << "-------------------------------------------------------------------------------" << endl;
            cout << "You make your way into the mansion and are immediately struck with a dizzying" << endl;
            cout << "sensation. You begin to realize that your mana is steadily draining. You recall" << endl;
            cout << "from your training that your mana is your lifeforce. The mana is what gives you" << endl;
            cout << "contol of magic and also keeps your health full. If fully depleted you will" << endl;
            cout << "not be able to use magic and will begin to take health damage. It is important" << endl;
            cout << "to recover mana as much as possible." << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
            break;
        }
        case 2: // user has chosen to quit
        {
            cout << endl << "Continue your training and you will be ready in no time" << endl;
            exit_game = true;
            break;
        }
    }

    // snippet of code to halt the screen for reading and waits for an enter to continue
    do
    {
        cout << endl << "Press enter to continue..." << endl;
        getline(cin, input);
    } while (!check_string_blank(input));

    // loop that runs while in the mansion and you have not won and still alive
    while (!exit_game && !game_won && !death)
    {
        // variable that will hold the room name that is received from each call to the events
        // in the rooms (controls the flow of the character within the mansion)
        Room_Name game_flow;

        clear_console();

        // if statements depending upon the players current location. Each if statement is nearly identical
        // the differences depend on which room the player is in
        if (player.get_position() == "Treasure Room")
        {
            // displays the map of the room
            treasure1->display_room();
            // prints out player's life points
            cout << "\t" << player.get_name() << "'s current status" << endl;
            cout << "\tHealth: " << player.get_health() << "\tMana: " << player.get_mana() << endl << endl;
            // makes a call to room events that controls what happens within the room
            game_flow = treasure1->display_room_events(player);
            // will display the pause menu if selected by the user
            if (game_flow == PAUSE)
            {
                display_pause_menu(player);
            }
            // section that will control the player location
            else if (game_flow == PUZZLE)
            {
                player.move_bottom(treasure1);
            }
        }
        else if (player.get_position() == "Puzzle Room")
        {
            puzzle1->display_room();
            cout << "\t" << player.get_name() << "'s current status" << endl;
            cout << "\tHealth: " << player.get_health() << "\tMana: " << player.get_mana() << endl << endl;
            game_flow = puzzle1->display_room_events(player);
            if (game_flow == PAUSE)
            {
                display_pause_menu(player);
            }
            else if (game_flow == TREASURE)
            {
                player.move_top(puzzle1);
            }
            else if (game_flow == FOYER)
            {
                player.move_right(puzzle1);
            }
        }
        else if (player.get_position() == "Alchemist Room")
        {
            alchemist1->display_room();
            cout << "\t" << player.get_name() << "'s current status" << endl;
            cout << "\tHealth: " << player.get_health() << "\tMana: " << player.get_mana() << endl << endl;
            game_flow = alchemist1->display_room_events(player);
            if (game_flow == PAUSE)
            {
                display_pause_menu(player);
            }
            else if (game_flow == LIBRARY)
            {
                player.move_bottom(alchemist1);
            }
        }
        else if (player.get_position() == "Library")
        {
            library1->display_room();
            cout << "\t" << player.get_name() << "'s current status" << endl;
            cout << "\tHealth: " << player.get_health() << "\tMana: " << player.get_mana() << endl << endl;
            game_flow = library1->display_room_events(player);
            if (game_flow == PAUSE)
            {
                display_pause_menu(player);
            }
            else if (game_flow == ALCHEMIST)
            {
                player.move_top(library1);
            }
            else if (game_flow == FOYER)
            {
                player.move_left(library1);
            }
        }
        else if (player.get_position() == "Foyer")
        {
            foyer1->display_room();
            cout << "\t" << player.get_name() << "'s current status" << endl;
            cout << "\tHealth: " << player.get_health() << "\tMana: " << player.get_mana() << endl << endl;
            game_flow = foyer1->display_room_events(player);
            if (game_flow == PAUSE)
            {
                display_pause_menu(player);
            }
            else if (game_flow == PUZZLE)
            {
                player.move_left(foyer1);
            }
            else if (game_flow == LIBRARY)
            {
                player.move_right(foyer1);
            }
            else if (game_flow == ATRIUM)
            {
                player.move_top(foyer1);
            }
        }
        else
        {
            atrium1->display_room();
            cout << "\t" << player.get_name() << "'s current status" << endl;
            cout << "\tHealth: " << player.get_health() << "\tMana: " << player.get_mana() << endl << endl;
            game_flow = atrium1->display_room_events(player);
            if (game_flow == PAUSE)
            {
                display_pause_menu(player);
            }
            else if (game_flow == FOYER)
            {
                player.move_bottom(atrium1);
            }
        }

        // snippet of code to halt the screen for reading and waits for an enter to continue
        do
        {
            cout << endl << "Press enter to continue..." << endl;
            getline(cin, input);
        } while (!check_string_blank(input));

        // controls the life stats of the player after each action within the room
        player.decrease_mana(4);
        // will begin to decrease health if the player does not have mana
        if (player.get_mana() == 0)
        {
            player.decrease_health(10);
        }
        // regenerates player health if the player has mana
        else
        {
            player.increase_health(2);
        }

        // section that will display if the player dies
        if (player.get_health() == 0)
        {
            clear_console();

            cout << "-----------------------------------------------------------------------------" << endl;
            cout << "               Unfortunately your health has reached 0 points.               " << endl;
            cout << "               " << player.get_name() << " has died.                         " << endl;
            cout << "-----------------------------------------------------------------------------" << endl;
            death = true;

            do
            {
                cout << endl << "Press enter to continue..." << endl;
                getline(cin, input);
            } while (!check_string_blank(input));
        }

        // does a constant check to the portal to see if the user has won the game
        if (atrium1->get_portal())
        {
            clear_console();

            cout << "-----------------------------------------------------------------------------" << endl;
            cout << "            Congratulations! You have cleared the Magic Mansion              " << endl;
            cout << "            " << player.get_name() << " has become a Master Wizard           " << endl;
            cout << "-----------------------------------------------------------------------------" << endl;
            game_won = true;

            do
            {
                cout << endl << "Press enter to continue..." << endl;
                getline(cin, input);
            } while (!check_string_blank(input));
        }
    }

    // deletes the dynamically allocated memory
    delete foyer1;
    delete library1;
    delete alchemist1;
    delete puzzle1;
    delete treasure1;
    delete atrium1;
}

/***********************************************************************************************************
** Description: Function to clear the console
***********************************************************************************************************/
void Game::clear_console()
{
    cout << "\033[2J\033[1;1H";
}

/***********************************************************************************************************
** Description: This function will display the pause menu when envoked by the user. The parameter is the
                reference to the player to access the player options.
***********************************************************************************************************/
void Game::display_pause_menu(Person &player_in)
{
    int option;
    bool back_to_game = false;  // flag for returning back to the game
    string input;

    // loop runs while the user does not exit
    while (!back_to_game)
    {
        clear_console();

        // pause menu object
        Menu pause_menu;
        pause_menu.set_menu_header("Game paused. What would you like to do?");
        pause_menu.add_menu_option("Display Map");
        pause_menu.add_menu_option("Check Health and Mana");
        pause_menu.add_menu_option("Display items");
        pause_menu.add_menu_option("Current Location");
        pause_menu.add_menu_option("Use health potion");
        pause_menu.add_menu_option("Use mana potion");
        pause_menu.add_menu_option("Objective");
        pause_menu.add_menu_option("Hint");
        pause_menu.add_menu_option("Exit Menu");
        pause_menu.add_menu_option("Quit");
        pause_menu.display_menu();
        option = pause_menu.get_choice();

        cout << endl << "--------------------------------------------------------------------------"
             << "---------------" << endl;
        switch (option)
        {
            case 1: // user selected map
            {
                display_map(player_in);
                break;
            }
            case 2: // user selected health and mana check
            {
                cout << "\t" << player_in.get_name() << "'s current status" << endl;
                cout << "\tHealth: " << player_in.get_health() << "\tMana: " << player_in.get_mana() << endl;
                break;
            }
            case 3: // user selected inventory
            {
                cout << "\t" << player_in.get_name() << "'s current inventory" << endl;
                player_in.display_inventory();
                break;
            }
            case 4: // user selected location
            {
                cout << "\t" << player_in.get_name() << "'s current position" << endl;
                cout << "\t" << player_in.get_position() << endl;
                break;
            }
            case 5: // user selected health potion
            {
                if (player_in.item_check(HEALTH_POTION))
                {
                    cout << "\tYou take a drink of the health potion and feel the magical energies" << endl;
                    cout << "\trevitalize your body." << endl;
                    cout << "\t\t--You have recovered 50 health points--" << endl;
                    player_in.increase_health(50);
                }
                else
                {
                    cout << "\tYou do not have a health potion to use." << endl;
                }
                break;
            }
            case 6: // user selected mana potion
            {
                if (player_in.item_check(MANA_POTION))
                {
                    cout << "\tYou take a drink of the mana potion and feel the magical energies" << endl;
                    cout << "\trevitalize your mind." << endl;
                    cout << "\t\t--You have recovered 50 mana points--" << endl;
                    player_in.increase_mana(50);
                }
                else
                {
                    cout << "\tYou do not have a mana potion to use." << endl;
                }
                break;
            }
            case 7: // user selected objective
            {
                cout << "\tThe objective to clear the Magic Mansion is to find the four magical" << endl;
                cout << "\tgauntlets and the passcode to unlock the portal to escape. This has" << endl;
                cout << "\tto be done before you run out of health. While you still have mana" << endl;
                cout << "\tyou will slowly recover health. However, should your mana run out" << endl;
                cout << "\tyour health will decrease." << endl;
                break;
            }
            case 8: // user selected hint
            {
                // displays your next suggested location and item pickup
                if (!player_in.item_check(WIND_GAUNTLET))
                {
                    cout << "\tWind Gauntlet..." << endl;
                    cout << "\tCan be picked up in the Foyer." << endl;
                }
                else if (!player_in.item_check(PASSCODE))
                {
                    cout << "\tPasscode..." << endl;
                    cout << "\tExamine the statue in the Puzzle Room." << endl;
                }
                else if (!player_in.item_check(MAGNETIC_GAUNTLET))
                {
                    cout << "\tMagnetic Gauntlet..." << endl;
                    cout << "\tCan be found in the Treasure Room." << endl;
                }
                else if (!player_in.item_check(FIRE_GAUNTLET))
                {
                    cout << "\tFire Gauntlet..." << endl;
                    cout << "\tSolve the metallic ball puzzle in the Puzzle Room." << endl;
                }
                else if (!player_in.item_check(LIGHTNING_GAUNTLET))
                {
                    cout << "\tLightning Gauntlet..." << endl;
                    cout << "\tCan be found in the Library." << endl;
                }
                else
                {
                    cout << "\tOutdoor Atrium..." << endl;
                    cout << "\tYou will find the portal there." << endl;
                }

                if (player_in.get_health() <= 30 || player_in.get_mana() <= 30)
                {
                    cout << endl;
                    cout << "\tPotions..." << endl;
                    cout << "\tCan be found in the Alchemist Room." << endl;
                }
                break;
            }
            case 9: // user selected exit
            {
                cout << "\tExiting back to the game..." << endl;
                back_to_game = true;
                break;
            }
            case 10: // user selected quit game
            {
                cout << "\tQuiting game..." << endl;
                back_to_game = true;
                exit_game = true;
                break;
            }
        }
        cout << "--------------------------------------------------------------------------"
             << "---------------" << endl;

        if (!back_to_game)
        {
            do
            {
                cout << endl << "Press enter to continue..." << endl;
                getline(cin, input);
            } while (!check_string_blank(input));
        }

    }
}