/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the atrium class. It is derived from the space class. The 
                member variables are the flags for the various events inside the room. The functions defined
                are used within the room for displaying events and modifying the player's stats.
***********************************************************************************************************/

#ifndef ATRIUM_HPP
#define ATRIUM_HPP

#include "Space.hpp"
#include "Person.hpp"

class Atrium : public Space
{
    private:
        bool vines_cleared;
        bool generator_on;
        
        void generator_event(Person &player);
        void vine_event(Person &player);
        void portal_event();
        Room_Name move_menu();

    public:
        Atrium();
        void display_room();
        Room_Name display_room_events(Person &player);
};

#endif