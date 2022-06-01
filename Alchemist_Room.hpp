/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the alchemist room class. It is derived from the space class. The 
                member variables are the flags for the various events inside the room. The functions defined
                are used within the room for displaying events and modifying the player's stats.
***********************************************************************************************************/

#ifndef ALCHEMIST_ROOM_HPP
#define ALCHEMIST_ROOM_HPP

#include "Space.hpp"
#include "Person.hpp"

class Alchemist_Room : public Space
{
    private:
        bool fancy_robes_obt;
        bool skull_head_obt;
        bool health_potion_obt;
        bool mana_potion_obt;
        bool cabinet_checked;

        void red_potion_event();
        void blue_potion_event();
        void wardrobe_event(Person &player);
        void cabinet_event(Person &player);
        Room_Name move_menu();

    public:
        Alchemist_Room();
        void display_room();
        Room_Name display_room_events(Person &player);
};

#endif