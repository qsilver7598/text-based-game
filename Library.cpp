/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the library class. It is derived from the space class.
                The functions defined are used within the room for displaying events and modifying the
                player's stats.
***********************************************************************************************************/

#include "Space.hpp"
#include "Library.hpp"
#include "Menu.hpp"
#include "Person.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/***********************************************************************************************************
** Description: Function that is called when the user selects the book option
***********************************************************************************************************/
void Library::books_event()
{
    cout << endl;
    cout << "You walk over to the table that has the shadow magic for dummies book. You pick them" << endl;
    cout << "up in hopes you will get a chance to rest and take a quick look." << endl;
    cout << "\t--You place the books in your satchel--" << endl;
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the gauntlet option
***********************************************************************************************************/
void Library::gauntlet_event()
{
    cout << endl;
    cout << "You grab a nearby ladder and hesitantly climb up to remove the gauntlets from it's" << endl;
    cout << "holder. You're hesitation will not prove your worth in the council's eyes, so you brush" << endl;
    cout << "off the thoughts and grab the gauntlets. The runes engraved into these gloves symbolize" << endl;
    cout << "electricity. As you put them on your hair stands on end and you feel the crackling" << endl;
    cout << "of electricity wrap around you." << endl;
    cout << "\t--You place the Lightning Gauntlet in your satchel--" << endl;
}

/***********************************************************************************************************
** Description: Function that is called when the user selects the read option
***********************************************************************************************************/
void Library::read_event()
{
    cout << endl;
    cout << "You sit down at one of the tables with a book in hand. You flick on the light and" << endl;
    cout << "Start reading. Your mind is energized imagining what you are reading." << endl;
    cout << "\t--You have gained 5 mana points--" << endl;
}

/***********************************************************************************************************
** Description: Function that returns the room the user wants to move to
***********************************************************************************************************/
Room_Name Library::move_menu()
{
    int choice;

    Menu move;
    move.set_menu_header("Which room would you like to move to?");
    move.add_menu_option("Alchemist Room");
    move.add_menu_option("Foyer");
    move.add_menu_option("Stay in Library");
    move.display_menu();
    choice = move.get_choice();

    switch (choice)
    {
        case 1: // user moved to alchemist room
        {
            cout << endl << "\tMoving to the Alchemist Room..." << endl;
            return ALCHEMIST;
        }
        case 2: // user moved to Foyer
        {
            cout << endl << "\tMoving to the Foyer..." << endl;
            return FOYER;
        }
        case 3: // user stayed library
        {
            return LIBRARY;
        }
    }
}

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Library::Library()
{
    lightning_gaunt_obt = false;
    books_obt = false;
    fog_cleared = false;
    entered_portal = false;
    name = "Library";

    this->top = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->bottom = nullptr;
}

/***********************************************************************************************************
** Description: Function used in displaying the foyer map. The map is read from a txt file that has the
                map printed within.
***********************************************************************************************************/
void Library::display_room()
{
    string line;
    std::ifstream infile;

    if (fog_cleared)
    {
        infile.open("special_library.txt");
    }
    else
    {
        infile.open("library.txt");
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
Room_Name Library::display_room_events(Person &player)
{
    int menu_choice;

    if (!fog_cleared)
    {
        cout << endl << "\t--You are in the Library--" << endl << endl;
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
                        cout << "out the fog from within the Library revealing a ridiculously large" << endl;
                        cout << "room with rows upon rows of books. You feel a little overwhelmed" << endl;
                        cout << "standing here gazing upon this room. You shake off that feeling" << endl;
                        cout << "and set out to explore the Library." << endl;
                        cout << "\t--Your mana is drained by 2 points by using the gauntlet--" << endl;
                        player.decrease_mana(2);
                        fog_cleared = true;
                    }
                    return LIBRARY;
                }
                case 2: // user does not equip gauntlets
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
        if (!lightning_gaunt_obt && !books_obt)
        {
            cout << endl << "\t--You are in the Library--" << endl << endl;
            cout << "After a quick rundown of the Library you have discovered two things of" << endl;
            cout << "interest. The first is one of gauntlets you are trying to find and it's" << endl;
            cout << "just sitting there on a plaque on the East wall." << endl;
            cout << "\t**It definitely gives me caution with it just sitting there but I haven't" << endl;
            cout << "\tdiscovered any other traps or puzzles, you think to yourself." << endl;
            cout << "The other is a few books that explains the attack strategies and weaknesses" << endl;
            cout << "of shadow magic. Which might be a good read later." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Grab the books");
            library_menu.add_menu_option("Grab the gauntlet");
            library_menu.add_menu_option("Sit down and read a book.");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: 
                {
                    books_event();
                    player.add_item(BOOKS);
                    if (player.item_check(BOOKS))
                    {
                        books_obt = true;
                    }
                    return LIBRARY;
                }
                case 2: 
                {
                    gauntlet_event();
                    player.add_item(LIGHTNING_GAUNTLET);
                    if (player.item_check(LIGHTNING_GAUNTLET))
                    {
                        lightning_gaunt_obt = true;
                    }
                    return LIBRARY;
                }
                case 3: 
                {
                    read_event();
                    player.increase_mana(7);
                    return LIBRARY;
                }
                case 4: 
                {
                    return move_menu();
                }
                case 5: 
                {
                    return PAUSE;
                }
            }
        }

        if (lightning_gaunt_obt && !books_obt)
        {
            cout << endl << "\t--You are in the Library--" << endl << endl;
            cout << "After grabbing the gauntlet you begin looking through the books hoping to find" << endl;
            cout << "the next great book to read. After perusing you decide the shadow books are" << endl;
            cout << "worth a borrow." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Grab the books");
            library_menu.add_menu_option("Sit down and read a book.");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: 
                {
                    books_event();
                    player.add_item(BOOKS);
                    if (player.item_check(BOOKS))
                    {
                        books_obt = true;
                    }
                    return LIBRARY;
                }
                case 2: 
                {
                    read_event();
                    player.increase_mana(7);
                    return LIBRARY;
                }
                case 3: 
                {
                    return move_menu();
                }
                case 4: 
                {
                    return PAUSE;
                }
            }
        }

        if (!lightning_gaunt_obt && books_obt)
        {
            cout << endl << "\t--You are in the Library--" << endl << endl;
            cout << "You wander around the library looking at the books. You are a book nerd" << endl;
            cout << "(what wizard isn't) and are easily distracted by the centuries of human" << endl;
            cout << "knowledge within this room." << endl;
            cout << "\t**Perhaps I should get back to getting out of here." << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Grab the gauntlet");
            library_menu.add_menu_option("Sit down and read a book.");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: 
                {
                    gauntlet_event();
                    player.add_item(LIGHTNING_GAUNTLET);
                    if (player.item_check(LIGHTNING_GAUNTLET))
                    {
                        lightning_gaunt_obt = true;
                    }
                    return LIBRARY;
                }
                case 2: 
                {
                    read_event();
                    player.increase_mana(7);
                    return LIBRARY;
                }
                case 3: 
                {
                    return move_menu();
                }
                case 4: 
                {
                    return PAUSE;
                }
            }
        }

        if (lightning_gaunt_obt && books_obt)
        {
            cout << endl << "\t--You are in the Library--" << endl << endl;

            Menu library_menu;
            library_menu.set_menu_header("What will you do?");
            library_menu.add_menu_option("Sit down and read a book.");
            library_menu.add_menu_option("Move to a different room");
            library_menu.add_menu_option("Pause Menu");
            library_menu.display_menu();
            menu_choice = library_menu.get_choice();

            switch (menu_choice)
            {
                case 1: // user wants to move rooms
                {
                    read_event();
                    player.increase_mana(7);
                    return LIBRARY;
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
}