/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This program implements a text based fantasy game. Your goal is to complete the challenge
                by solving puzzles, picking up items, and trying to stay alive. The control is a menu
                system that asks the user how they would like to interact with the game. The theme is
                fantasy. You are a wizard taking your final challenge in your wizard training. Should
                you complete it. You will become a master wizard.
***********************************************************************************************************/

#include "Menu.hpp"
#include "Game.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;

int main()
{
    int menu_choice;
    bool quit = false;  // flag to quit the game
    bool first_run = true;  // flag to display the play again menu

    // Main menu object
    Menu main_menu("Main Menu");
    main_menu.set_menu_header("Welcome to Wizard Training!");
    main_menu.add_menu_option("Play");
    main_menu.add_menu_option("Exit");

    // Play again menu object
    Menu play_again("Play Again");
    play_again.set_menu_header("Would you like to play again?");
    play_again.add_menu_option("Yes");
    play_again.add_menu_option("No");

    // game object
    Game game1;

    // this do loop is for the play or quit option
    do
    {
        // clears the console
        cout << "\033[2J\033[1;1H";

        // if first time playing display the main menu
        if (first_run)
        {
            main_menu.display_menu_title();
            main_menu.display_menu();
            menu_choice = main_menu.get_choice();
        }
        // if playing again, display the play again menu
        else
        {
            play_again.display_menu();
            menu_choice = play_again.get_choice();
        }
        switch (menu_choice)
        {
            case 1: // user selected to start game
            {
                game1.start_game();
                first_run = false;
                break;
            }
            // user has selected to quit
            case 2:
            {
                quit = true;
                break;
            }
        }

    } while (!quit);

    return 0;
}
