/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the treasure room class. It is derived from the space class. The 
                member variables are the flags for the various events inside the room. The functions defined
                are used within the room for displaying events and modifying the player's stats.
***********************************************************************************************************/

#ifndef TREASURE_ROOM_HPP
#define TREASURE_ROOM_HPP

#include "Space.hpp"
#include "Person.hpp"

class Treasure_Room : public Space
{
    private:
        bool magnetic_gaunt_obt;
        bool sword_shield_obt;
        bool lamp_checked;
        bool jewel_checked;
        bool rug_checked;
        
        void lamp_event();
        void gauntlet_event(Person &player);
        void gold_event(Person &player);
        void rug_event();
        void jewel_event();
        Room_Name move_menu();
        
    public:
        Treasure_Room();
        void display_room();
        Room_Name display_room_events(Person &player);
};

#endif