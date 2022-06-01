/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the menu class. There are 3 variables, a vector for the 
                different options and 2 variables for the menu title and the header. There are 2 
                constructors, 4 functions that will build a menu, and 2 functions used in getting the menu
                selections from the user.
***********************************************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>

using std::vector;
using std::string;

class Menu
{
    private:
        vector<string> menu_options;
        string menu_title;
        string menu_header;

    public:
        Menu();
        Menu(string menu_title);
        void set_menu_header(string menu_header);
        void add_menu_option(string menu_option);
        void display_menu_title();
        void display_menu();
        int get_choice();
        int get_number_of_options();
};

#endif