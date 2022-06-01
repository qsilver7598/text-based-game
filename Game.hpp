/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the game class. Defined in this file are two enums used in
                controlling different aspects of the game. There are 3 bool variables used in exiting
                loops. There are 4 functions. One to display the map, one to run the main portion of
                game, one to clear the console, and one to display the pause menu.
***********************************************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

enum Room_Name {TREASURE, PUZZLE, ALCHEMIST, LIBRARY, FOYER, ATRIUM, PAUSE};
enum Game_Items {MAP, FIRE_GAUNTLET, LIGHTNING_GAUNTLET, MAGNETIC_GAUNTLET, WIND_GAUNTLET, PASSCODE, BOOKS, 
                 SWORD_SHIELD, FANCY_ROBES, SKULL_HEAD, HEALTH_POTION, MANA_POTION};

#include "Person.hpp"

#include <string>

class Person; // forward declaration

class Game
{
    private:
        bool game_won;  // flag for winning
        bool exit_game; // flag for quitting the game
        bool death; // flag for death

    public:
        Game();
        void display_map(Person &player_in);
        void start_game();
        void clear_console();
        void display_pause_menu(Person &player_in);
};

#endif