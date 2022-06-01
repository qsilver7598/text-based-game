/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the treasure room class. It is derived from the space 
                class. The functions defined are used within the room for displaying events and modifying the
                player's stats.
***********************************************************************************************************/

#include "Space.hpp"
#include "Treasure_Room.hpp"
#include "Menu.hpp"
#include "Person.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/***********************************************************************************************************
** Description: Function that is called when the user selects the lamp option
***********************************************************************************************************/
void Treasure_Room::lamp_event()
{
    cout << endl;
    if (lamp_checked)
    {
        cout << "You have already checked the lamp and believe the runes guarding the gauntlet have" << endl;
        cout << "dissipated." << endl;
    }
    else
    {
        cout << "You cautiously ascend the stair case expecting some kind of trap to be laid out" << endl;
        cout << "above you. To your surprise nothing happened. You take stock of the lamp before" << endl;
        cout << "picking it up. Nothing strange about it. You pick it up and instantly blue smoke" << endl;
        cout << "comes swirling out of it filling up the room, and almost as quick as it came," << endl;
        cout << "the smoke was gone. You hear the sound of runes dissipating around the gauntlet." << endl;
        lamp_checked = true;
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the gauntlet option
***********************************************************************************************************/
void Treasure_Room::gauntlet_event(Person &player)
{
    cout << endl;
    if (lamp_checked)
    {
        cout << "You slowly and carefully walk over to the gauntlet. You pick it up and sense" << endl;
        cout << "the runes of magnetic energy pulling at the very foundation of the room as you" << endl;
        cout << "slide the glove onto your hand." << endl;
        cout << "\t--You place the Magnetic Gauntlet into your satchel--" << endl;
        player.add_item(MAGNETIC_GAUNTLET);
        if (player.item_check(MAGNETIC_GAUNTLET))
        {
            magnetic_gaunt_obt = true;
        }
    }
    else
    {        
        cout << "You try to grab the gauntlet, but electricity surges through you and you" << endl;
        cout << "are thrown backwards onto a mountain of gold." << endl;
        cout << "\t--The defensive runes were activated as you tried to grab the gauntlet.--" << endl;
        cout << "\t--Perhaps you should find a way to deactivate the runes.--" << endl;
        player.decrease_health(20);
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the gold option
***********************************************************************************************************/
void Treasure_Room::gold_event(Person &player)
{
    int choice;

    cout << endl;
    cout << "You decide to rummage through the gold looking for something too good to pass up. You" << endl;
    cout << "stumble upon a magnificently crafted sword and shield set. You truly admire the" << endl;
    cout << "craftsmanship that went into it. It looks fit for a god." << endl;

    Menu sword_shield;
    sword_shield.set_menu_header("What will you do?");
    sword_shield.add_menu_option("Take the sword and shield");
    sword_shield.add_menu_option("Put it back on the pile");
    sword_shield.display_menu();
    choice = sword_shield.get_choice();

    cout << endl;
    switch (choice)
    {
        case 1: // user gets sword/shield
        {
            cout << "\t--You place the sword/shield into your satchel--" << endl;
            player.add_item(SWORD_SHIELD);
            if (player.item_check(SWORD_SHIELD))
            {
                sword_shield_obt = true;
            }
            break;
        }
        case 2: // user puts sword/shield back
        {
            cout << "You regretfully place the sword and shield back onto the pile of treasures." << endl;
            break;
        }
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the rug option
***********************************************************************************************************/
void Treasure_Room::rug_event()
{
    cout << endl;
    if (rug_checked)
    {
        cout << "You debate on trying to befriend the rug. (would be cool to go on a ride) but" << endl;
        cout << "decide not to mess with it again. He... or she... hmm... or it, heck I don't" << endl;
        cout << "know, probably wants to be left alone based on its previous action." << endl;
    }
    else
    {
        cout << "You are curious about that rug. It seems so out of place in here. As you walk over" << endl;
        cout << "to it, you notice it twitch. You shrug it off as your mind playing tricks on you." << endl;
        cout << "Just as you get within arms distance, the rug reaches out and slaps you across the" << endl;
        cout << "face. (yeah, a rug) You watch as it takes off flying (yeah, again a rug) and heads" << endl;
        cout << "over to another mountain of gold and retreats to its previous posture. You face" << endl;
        cout << "hurts a little but by golly if that isn't the cutest/strangest thing you ever" << endl;
        cout << "seen." << endl;
        cout << "\t--You take 10 points of damage to your health--" << endl;
        cout << "\t--but gain 5 points of mana for a good chuckle--" << endl;
        rug_checked = true;
    }
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the jewel option
***********************************************************************************************************/
void Treasure_Room::jewel_event()
{
    cout << endl;
    if (jewel_checked)
    {
        cout << "You remember the searing pain you had the first time you touched the jewel." << endl;
        cout << "\t**Perhaps I shouldn't try touching it again, you think to yourself." << endl;
    }
    else
    {
        cout << "You are captivated by the fiery jewel placed upon the hands of a statue. You tell" << endl;
        cout << "yourself this looks like a trap but the 'precious' is just to much to ignore. You" << endl;
        cout << "reach out and grab the jewel and are consumed with a burning sensation within your" << endl;
        cout << "body. You immediately drop the jewel and seeth in frustration as the jewel falls to" << endl;
        cout << "the ground and rolls under a golden table." << endl;
        cout << "\t--You take 20 points of damage to your health--" << endl;
        jewel_checked = true;
    }
}

/***********************************************************************************************************
** Description: Function that returns the room the user wants to move to
***********************************************************************************************************/
Room_Name Treasure_Room::move_menu()
{
    int choice;

    Menu move;
    move.set_menu_header("Which room would you like to move to?");
    move.add_menu_option("Puzzle Room");
    move.add_menu_option("Stay in Treasure Room");
    move.display_menu();
    choice = move.get_choice();

    switch (choice)
    {
        case 1: // user moved to puzzle room
        {
            cout << endl << "\tMoving to the Puzzle Room..." << endl;
            return PUZZLE;
        }
        case 2: // user stayed treasure room
        {
            return TREASURE;
        }
    }
}

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Treasure_Room::Treasure_Room()
{
    magnetic_gaunt_obt = false;
    sword_shield_obt = false;
    lamp_checked = false;
    jewel_checked = false;
    rug_checked = false;
    fog_cleared = false;
    entered_portal = false;
    name = "Treasure Room";

    this->top = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->bottom = nullptr;
}

/***********************************************************************************************************
** Description: Function used in displaying the foyer map. The map is read from a txt file that has the
                map printed within.
***********************************************************************************************************/
void Treasure_Room::display_room()
{
    string line;
    std::ifstream infile;

    if (fog_cleared)
    {
        infile.open("special_treasure.txt");
    }
    else
    {
        infile.open("treasure.txt");
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
Room_Name Treasure_Room::display_room_events(Person &player)
{
    int menu_choice;

    if (!fog_cleared)
    {
        cout << endl << "\t--You are in the Treasure Room--" << endl << endl;
        cout << "Your eyes are burning by the magical fog that is covering this place. If only you" << endl;
        cout << "had a way to clear out the room." << endl;

        cout << endl;
        if (player.item_check(WIND_GAUNTLET))
        {
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
                        cout << "out the fog from within the Treasure Room revealing mountains of" << endl;
                        cout << "gold and jewels scattered throughout the room. To the North of the" << endl;
                        cout << "room you see an elegant marble staircase with what appears to be" << endl;
                        cout << "a golden lamp at the top. You also notice another gauntlet sitting" << endl;
                        cout << "on another pedestal in the center of the room." << endl;
                        cout << "\t--Your mana is drained by 2 points by using the gauntlet--" << endl;
                        player.decrease_mana(2);
                        fog_cleared = true;
                    }
                    return TREASURE;
                }
                case 2: // user does not equip gauntlets
                {
                    cout << endl;
                    cout << "Unfortunately with the suffocating fog you are forced to retreat" << endl;
                    cout << "back into the Puzzle Room." << endl;
                    return PUZZLE;
                }
            }
        }
        else
        {
            cout << endl;
            cout << "\t**You think to yourself, there must be a magical item I can get to remove" << endl;
            cout << "\tall of this fog. You retreat back into the Puzzle Room." << endl;
            return PUZZLE;
        }
    }
    else
    {
        if (!magnetic_gaunt_obt && !sword_shield_obt)
        {
            cout << endl << "\t--You are in the Treasure Room--" << endl << endl;
            cout << "As you wander around the Treasure Room, you can't help but wonder if it would" << endl;
            cout << "be best to grab some of this treasure on your way out. You notice a peculiar" << endl;
            cout << "looking rug perched next to one of the mountains of gold. You also notice one" << endl;
            cout << "of the most blazing red jewels you have ever seen." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Examine the Lamp");
            library_menu.add_menu_option("Grab gauntlet");
            library_menu.add_menu_option("Rummage through the stacks of gold");
            library_menu.add_menu_option("Look under the peculiar looking rug");
            library_menu.add_menu_option("Grab the jewel");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user checks lamp
                {
                    lamp_event();
                    return TREASURE;
                }
                case 2: // user grabs gauntlet
                {
                    gauntlet_event(player);
                    return TREASURE;
                }
                case 3: // user checks gold
                {
                    gold_event(player);
                    return TREASURE;
                }
                case 4: // user checks rug
                {
                    rug_event();
                    player.decrease_health(10);
                    player.increase_mana(5);
                    return TREASURE;
                }
                case 5: // user checks jewel
                {
                    jewel_event();
                    player.decrease_health(20);
                    return TREASURE;
                }
                case 6: // user wants to move rooms
                {
                    return move_menu();
                }
                case 7: // user paused the game
                {
                    return PAUSE;
                }
            }
        }
        if (!magnetic_gaunt_obt && sword_shield_obt)
        {
            cout << endl << "\t--You are in the Treasure Room--" << endl << endl;
            cout << "You wander around the Treasure Room feeling like a king/queen after picking" << endl;
            cout << "up that sword and shield. You are ready to take on anything that stands" << endl;
            cout << "in your way. Now lets figure out how to get that gauntlet." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Examine the Lamp");
            library_menu.add_menu_option("Grab gauntlet");
            library_menu.add_menu_option("Look under the peculiar looking rug");
            library_menu.add_menu_option("Grab the jewel");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user checks lamp
                {
                    lamp_event();
                    return TREASURE;
                }
                case 2: // user grabs gauntlet
                {
                    gauntlet_event(player);
                    return TREASURE;
                }
                case 3: // user checks rug
                {
                    rug_event();
                    player.decrease_health(10);
                    player.increase_mana(5);
                    return TREASURE;
                }
                case 4: // user checks jewel
                {
                    jewel_event();
                    player.decrease_health(20);
                    return TREASURE;
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
        if (magnetic_gaunt_obt && !sword_shield_obt)
        {
            cout << endl << "\t--You are in the Treasure Room--" << endl << endl;
            cout << "Your main objective is accomplished. You nabbed the gauntlet. There doesn't" << endl;
            cout << "appear to be another gauntlet in this room. But maybe looking around couldn't" << endl;
            cout << "hurt." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Rummage through the stacks of gold");
            library_menu.add_menu_option("Look under the peculiar looking rug");
            library_menu.add_menu_option("Grab the jewel");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user checks gold
                {
                    gold_event(player);
                    return TREASURE;
                }
                case 2: // user checks rug
                {
                    rug_event();
                    player.decrease_health(10);
                    player.increase_mana(5);
                    return TREASURE;
                }
                case 3: // user checks jewel
                {
                    jewel_event();
                    player.decrease_health(20);
                    return TREASURE;
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
        if (magnetic_gaunt_obt && sword_shield_obt)
        {
            cout << endl << "\t--You are in the Treasure Room--" << endl << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Look under the peculiar looking rug");
            library_menu.add_menu_option("Grab the jewel");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user checks rug
                {
                    rug_event();
                    player.decrease_health(10);
                    player.increase_mana(5);
                    return TREASURE;
                }
                case 2: // user checks jewel
                {
                    jewel_event();
                    player.decrease_health(20);
                    return TREASURE;
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