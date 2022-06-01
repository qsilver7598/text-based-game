/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the puzzle room class. It is derived from the space class.
                The functions defined are used within the room for displaying events and modifying the
                player's stats.
***********************************************************************************************************/

#include "Space.hpp"
#include "Puzzle_Room.hpp"
#include "Menu.hpp"
#include "Person.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/***********************************************************************************************************
** Description: Function that is called when the user selects the statue option
***********************************************************************************************************/
void Puzzle_Room::statue_event(Person &player)
{
    int choice;

    cout << endl;
    cout << "Upon touching the statue you are very aware of someone or something within your" << endl;
    cout << "mind. A voice beckons from somewhere but you aren't hearing it." << endl << endl;
    cout << "\tRIDDLE ME THIS MORTAL: I WILL ALLOW YOU TO PASS AND RELEASE MY SECRETS IF YOU" << endl;
    cout << "\tANSWER ME ONE RIDDLE..." << endl << endl;
    cout << "\tI FOLLOW YOU BY DAY, BY NIGHT I BLEND RIGHT IN BUT NO ONE SEES ME EXCEPT WHEN" << endl;
    cout << "\tI'M IN THE LIGHT." << endl << endl;
    while (!passcode_obt)
    {
        Menu puzzle;
        puzzle.set_menu_header("WHAT AM I?");
        puzzle.add_menu_option("Sun");
        puzzle.add_menu_option("Moon");
        puzzle.add_menu_option("Shadow");
        puzzle.add_menu_option("Cloud");
        puzzle.add_menu_option("Repeat riddle");
        puzzle.display_menu();
        choice = puzzle.get_choice();

        switch (choice)
        {
            case 1: // user selects sun
            {
                cout << endl;
                cout << "\tTHAT IS NOT CORRECT." << endl;
                cout << "\tYou feel a twisting pain from within your mind." << endl;
                cout << "\t--You have lost 10 mana points--" << endl;
                player.decrease_mana(10);
                break;
            }
            case 2: // user selects moon
            {
                cout << endl;
                cout << "\tTHAT IS NOT CORRECT." << endl;
                cout << "\tYou feel a twisting pain from within your mind." << endl;
                cout << "\t--You have lost 10 mana points--" << endl;
                player.decrease_mana(10);
                break;
            }
            case 3: // user selects shadow
            {
                cout << endl;
                cout << "\tCONGRATULATIONS. SHADOW IS THE CORRECT ANSWER. I WILL NOW BESTOW" << endl;
                cout << "\tUPON YOU A SCROLL WITH A SERIES OF NUMBERS ETCHED UPON THE SURFACE" << endl;
                cout << "\t--You place the scroll inside your satchel--" << endl << endl;
                cout << "You hear some movement from the North wall." << endl;
                cout << "\t--A door has suddenly appeared--" << endl;
                player.add_item(PASSCODE);
                if (player.item_check(PASSCODE))
                {
                    passcode_obt = true;
                }
                break;
            }
            case 4: // user selects cloud
            {
                cout << endl;
                cout << "\tTHAT IS NOT CORRECT." << endl;
                cout << "\tYou feel a twisting pain from within your mind." << endl;
                cout << "\t--You have lost 10 mana points--" << endl;
                player.decrease_mana(10);
                break;
            }
            case 5: // user selects to hear riddle again
            {
                cout << endl;
                cout << "\tI FOLLOW YOU BY DAY, BY NIGHT I BLEND RIGHT IN BUT NO ONE SEES ME" << endl;
                cout << "\tEXCEPT WHEN I'M IN THE LIGHT." << endl << endl;
            }
        }
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the ball option
***********************************************************************************************************/
void Puzzle_Room::metallic_ball_event(Person &player)
{
    int menu_choice;

    cout << endl;
    if (ball_solved)
    {
        cout << "The ball has already been placed into it's correct spot. You believe the runes" << endl;
        cout << "guarding the gauntlet have dissipated." << endl;
    }
    else
    {
        if (player.item_check(MAGNETIC_GAUNTLET))
        {
            cout << "Would you like to equip your Magnetic Gauntlet and use the stored energy in the" << endl;
            cout << "runes to move the ball." << endl;

            Menu yes_no;
            yes_no.set_menu_header("What is your decision.");
            yes_no.add_menu_option("Yes");
            yes_no.add_menu_option("No");
            yes_no.display_menu();
            menu_choice = yes_no.get_choice();

            switch (menu_choice)
            {
                case 1: // user equips gauntlet
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
                        cout << "With the power of magnetism surging through you, you are able to lift" << endl;
                        cout << "the ball and move it into the giant hole in the South wall. You" << endl;
                        cout << "witness lightning shoot across the room shattering the defensive runes," << endl;
                        cout << "intertwined around the gauntlet." << endl;
                        cout << "\t--Your mana is drained by 2 points by using the gauntlet--" << endl;
                        player.decrease_mana(2);
                        ball_solved = true;
                    }
                    break;
                }
                case 2: // user does not equip gauntlet
                {
                    cout << endl;
                    cout << "Unfortunately you lack the strength to move the giant hunk of metal" << endl;
                    cout << "without aid from some magical forces." << endl;
                    break;
                }
            }
        }
        else
        {
            cout << endl;
            cout << "\t**You wonder if you would be able to move that metal ball with a different" << endl;
            cout << "\ttype of gauntlet. Hmmm..." << endl;
        }
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the gauntlet option
***********************************************************************************************************/
void Puzzle_Room::gauntlet_event(Person &player)
{
    cout << endl;
    if (ball_solved)
    {
        cout << "You walk over to the newly freed gauntlet and upon inspection you see the markings" << endl;
        cout << "of the fire runes etched upon the gloves. You pick them up and immediatly feel" << endl;
        cout << "the burning heat surround you as you place the gloves on your hand." << endl;
        cout << "\t--You place the Fire Gauntlet into your satchel--" << endl;
        player.add_item(FIRE_GAUNTLET);
        if (player.item_check(FIRE_GAUNTLET))
        {
            fire_gaunt_obt = true;
        }
    }
    else
    {
        cout << "You try to grab the gauntlet, but fire bellows out and rushes up your arm and you" << endl;
        cout << "are thrown back into the wall." << endl;
        cout << "\t--The defensive runes were activated as you tried to grab the gauntlet.--" << endl;
        cout << "\t--Perhaps you should find a way to deactivate the runes.--" << endl;
        player.decrease_health(20);
    }
}

/***********************************************************************************************************
** Description: Function that returns the room the user wants to move to
***********************************************************************************************************/
Room_Name Puzzle_Room::move_menu()
{
    int choice;

    Menu move;
    move.set_menu_header("Which room would you like to move to?");
    move.add_menu_option("Treasure Room");
    move.add_menu_option("Foyer");
    move.add_menu_option("Stay in Puzzle Room");
    move.display_menu();
    choice = move.get_choice();

    cout << endl;
    switch (choice)
    {
        case 1: // user moved to treasure room
        {
            if (passcode_obt)
            {
                cout << endl << "\tMoving to the Treasure Room..." << endl;
                return TREASURE;
            }
            else
            {
                cout << "You are unable to locate the entrance to the Treasure Room. The map says" << endl;
                cout << "it is located in this room somewhere." << endl;
                cout << "\t**Maybe I should try solving a puzzle." << endl;
                return PUZZLE;
            }
        }
        case 2: // user moved to Foyer
        {
            cout << endl << "\tMoving to the Foyer..." << endl;
            return FOYER;
        }
        case 3: // user stayed in puzzle room
        {
            return PUZZLE;
        }
    }
}

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Puzzle_Room::Puzzle_Room()
{
    passcode_obt = false;
    fire_gaunt_obt = false;
    ball_solved = false;
    fog_cleared = false;
    entered_portal = false;
    name = "Puzzle Room";

    this->top = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->bottom = nullptr;
}

/***********************************************************************************************************
** Description: Function used in displaying the foyer map. The map is read from a txt file that has the
                map printed within.
***********************************************************************************************************/
void Puzzle_Room::display_room()
{
    string line;
    std::ifstream infile;

    if (fog_cleared)
    {
        infile.open("special_puzzle.txt");
    }
    else
    {
        infile.open("puzzle.txt");
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
Room_Name Puzzle_Room::display_room_events(Person &player)
{
    int menu_choice;

    // checks to see if fog is cleared or no
    if (!fog_cleared)
    {
        cout << endl << "\t--You are in the Puzzle Room--" << endl << endl;
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
                case 1: // user equips gauntlet
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
                        cout << "out the fog from within the Puzzle Room revealing a peculiar looking" << endl;
                        cout << "statue and giant ball sitting on the floor. In the corner you see" << endl;
                        cout << "another gauntlet sitting magnificently upon another pedestal." << endl;
                        cout << "Unfortunatly this magical glove appears to be protected by some kind" << endl;
                        cout << "of defense rune." << endl;
                        cout << "\t--Your mana is drained by 2 points by using the gauntlet--" << endl;
                        player.decrease_mana(2);
                        fog_cleared = true;
                    }
                    return PUZZLE;
                }
                case 2: // user does not equip gauntlet
                {
                    cout << endl;
                    cout << "Unfortunately with the suffocating fog you are forced to retreat" << endl;
                    cout << "back into the foyer." << endl;
                    return FOYER;
                }
            }
        }
        else
        {
            cout << endl;
            cout << "\t**You think to yourself, there must be a magical item I can get to remove" << endl;
            cout << "\tall of this fog. You retreat back into the foyer." << endl;
            return FOYER;
        }
    }
    else
    {
        if (!passcode_obt && !fire_gaunt_obt)
        {
            cout << endl << "\t--You are in the Puzzle Room--" << endl << endl;
            cout << "Your observations of the Puzzle Room lead you to conclude that to release" << endl;
            cout << "the gauntlet, this requires the movement of the large metallic ball in the" << endl;
            cout << "back of the room. It looks like the giant shiney boulder can be slotted into" << endl;
            cout << "the similar shaped hole along the South wall." << endl;

            Menu puzzle_room_menu;
            puzzle_room_menu.set_menu_header("What will you do?");
            puzzle_room_menu.add_menu_option("Examine the Statue");
            puzzle_room_menu.add_menu_option("Examine the metallic ball");
            puzzle_room_menu.add_menu_option("Pick up gauntlet");
            puzzle_room_menu.add_menu_option("Move to a different room");
            puzzle_room_menu.add_menu_option("Pause Menu");
            puzzle_room_menu.display_menu();
            menu_choice = puzzle_room_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user examined the statue
                {
                    statue_event(player);
                    return PUZZLE;
                }
                case 2: // user examined the metallic ball
                {
                    metallic_ball_event(player);
                    return PUZZLE;
                }
                case 3: // user tried to get the gauntlet
                {
                    gauntlet_event(player);
                    return PUZZLE;
                }
                case 4: // user moved to a different room
                {
                    return move_menu();
                }
                case 5: // user paused the game
                {
                    return PAUSE;
                }
            }
        }

        if (passcode_obt && !fire_gaunt_obt)
        {
            cout << endl << "\t--You are in the Puzzle Room--" << endl << endl;
            cout << "You have solved one of the puzzles within this room. You must figure out" << endl;
            cout << "a way to retrieve those gauntlet." << endl;

            Menu puzzle_room_menu;
            puzzle_room_menu.set_menu_header("What will you do?");
            puzzle_room_menu.add_menu_option("Examine the metallic ball");
            puzzle_room_menu.add_menu_option("Pick up gauntlet");
            puzzle_room_menu.add_menu_option("Move to a different room");
            puzzle_room_menu.add_menu_option("Pause Menu");
            puzzle_room_menu.display_menu();
            menu_choice = puzzle_room_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user examined the metallic ball
                {
                    metallic_ball_event(player);
                    return PUZZLE;
                }
                case 2: // user tried to get the gauntlet
                {
                    gauntlet_event(player);
                    return PUZZLE;
                }
                case 3: // user moved to a different room
                {
                    return move_menu();
                }
                case 4: // user paused the game
                {
                    return PAUSE;
                }
            }
        }

        if (passcode_obt && fire_gaunt_obt)
        {
            cout << endl << "\t--You are in the Puzzle Room--" << endl << endl;
            cout << "There doesn't appear to be any more puzzles within this room." << endl;

            Menu puzzle_room_menu;
            puzzle_room_menu.set_menu_header("What will you do?");
            puzzle_room_menu.add_menu_option("Move to a different room");
            puzzle_room_menu.add_menu_option("Pause Menu");
            puzzle_room_menu.display_menu();
            menu_choice = puzzle_room_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user wants to move rooms
                {
                    return move_menu();
                }
                case 2: // user paused the game
                {
                    return PAUSE;
                }
            }
        }
    }
}