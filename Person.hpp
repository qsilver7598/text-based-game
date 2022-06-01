/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the person class. Member variables are the players stats and
                the players inventory. There are many functions used in getting and setting these variables.
                See the cpp file for function descriptions.
***********************************************************************************************************/

#ifndef PERSON_HPP
#define PERSON_HPP

#include "Space.hpp"
#include "Game.hpp"

#include <string>
#include <vector>

class Space; // forward declaration

class Person
{
    private:
        std::string name;   // player's name
        int health; // health stat
        int mana; // mana stat
        Space *position;    // players location within the mansion
        std::vector<Game_Items> inventory;  // vector that holds the items the user has
        int max_inventory;  // maximum inventory
        bool exit_inventory_menu = false;   // flag used when discarding an item
    public:
        Person();
        void set_health(int h);
        void increase_health(int h_up);
        void decrease_health(int h_down);
        void set_mana(int m);
        void increase_mana(int m_up);
        void decrease_mana(int m_down);
        void set_name(std::string name_in);
        void set_position(Space *new_location);
        void move_top(Space *room);
        void move_left(Space *room);
        void move_right(Space *room);
        void move_bottom(Space *room);
        void display_inventory();
        void add_item(Game_Items item_in);
        void remove_item(Game_Items item_out);
        bool check_inventory_limit();
        bool item_check(Game_Items item_check);
        int get_health();
        int get_mana();
        std::string get_name();
        std::string get_position();
        std::string print_enum(Game_Items item);
};

#endif