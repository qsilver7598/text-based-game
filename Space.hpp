/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the abstract space class. Member variables are 4 pointers that
                point to different spaces, the name of the space, and 2 bools used in room events. The
                functions are the setters and getters for the member variables. There are also the virtual
                abstract functions that are used in the derived classes.
***********************************************************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Game.hpp"
#include "Person.hpp"

#include <string>

class Person; // forward declaration

class Space
{
    protected:
        Space *top;
        Space *left;
        Space *right;
        Space *bottom;
        std::string name;
        
        bool fog_cleared;
        bool entered_portal;

    public:
        virtual ~Space() {}
        virtual void display_room() = 0;
        virtual Room_Name display_room_events(Person &player) = 0;
        
        void set_top(Space *room);
        void set_left(Space *room);
        void set_right(Space *room);
        void set_bottom(Space *room);
        Space *get_top();
        Space *get_left();
        Space *get_right();
        Space *get_bottom();
        std::string get_name();
        bool get_portal();
};

#endif