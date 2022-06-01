/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the foyer class. It is derived from the space class. The member
                variables are the flags for the various events inside the room. The functions defined
                are used within the room for displaying events and modifying the player's stats.
***********************************************************************************************************/

#ifndef FOYER_HPP
#define FOYER_HPP

#include "Space.hpp"
#include "Person.hpp"

class Foyer : public Space
{
    private:
        bool map_obt;
        bool wind_gaunt_obt;
        bool atrium_unlocked;
        bool rubble_checked;

        void map_event();
        void fountain_event();
        void gauntlet_event();
        void check_atrium(Person &player);
        void rubble_event();
        Room_Name move_menu();

    public:
        Foyer();
        void display_room();
        Room_Name display_room_events(Person &player);
};

#endif