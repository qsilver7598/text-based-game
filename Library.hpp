/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the library class. It is derived from the space class. The 
                member variables are the flags for the various events inside the room. The functions defined
                are used within the room for displaying events and modifying the player's stats.
***********************************************************************************************************/

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "Space.hpp"
#include "Person.hpp"

class Library : public Space
{
    private:
        bool lightning_gaunt_obt;
        bool books_obt;

        void books_event();
        void gauntlet_event();
        void read_event();
        Room_Name move_menu();

    public:
        Library();
        void display_room();
        Room_Name display_room_events(Person &player);
};

#endif