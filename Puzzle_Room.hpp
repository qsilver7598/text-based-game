/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the puzzle room class. It is derived from the space class. The 
                member variables are the flags for the various events inside the room. The functions defined
                are used within the room for displaying events and modifying the player's stats.
***********************************************************************************************************/

#ifndef PUZZLE_ROOM_HPP
#define PUZZLE_ROOM_HPP

#include "Space.hpp"
#include "Person.hpp"

class Puzzle_Room : public Space
{
    private:
        bool passcode_obt;
        bool fire_gaunt_obt;
        bool ball_solved;

        void statue_event(Person &player);
        void metallic_ball_event(Person &player);
        void gauntlet_event(Person &player);
        Room_Name move_menu();

    public:
        Puzzle_Room();
        void display_room();
        Room_Name display_room_events(Person &player);
};

#endif