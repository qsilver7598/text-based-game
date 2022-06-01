/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the menu class. There are 2 constructors, 4 functions 
                that will build a menu, and 2 functions used in getting the menu selections from the user.
***********************************************************************************************************/

#include "Menu.hpp"
#include "InputVal.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::vector;
using std::stoi;

/***********************************************************************************************************
** Description: Default constructor
***********************************************************************************************************/
Menu::Menu()
{
    this->menu_title = "Menu";
}

/***********************************************************************************************************
** Description: Constructor created by the user that sets the title of the menu
***********************************************************************************************************/
Menu::Menu(string menu_title)
{
    this->menu_title = menu_title;
}

/***********************************************************************************************************
** Description: sets the header for the menu
***********************************************************************************************************/
void Menu::set_menu_header(string menu_header)
{
    this->menu_header = menu_header;
}

/***********************************************************************************************************
** Description: adds the options for the menu into the options vector
***********************************************************************************************************/
void Menu::add_menu_option(string menu_option)
{
    menu_options.push_back(menu_option);
}

/***********************************************************************************************************
** Description: Prints the menu title when the function is called.
***********************************************************************************************************/
void Menu::display_menu_title()
{
    cout << endl << "-----" << menu_title << "-----"<< endl;
}

/***********************************************************************************************************
** Description: Prints the menu when the function is called. The function prints menu header. Finally the
                array of options is iterated over and prints out each menu option.
***********************************************************************************************************/
void Menu::display_menu()
{
    cout << endl << menu_header << endl;
    for (int j = 0; j < get_number_of_options(); j++)
    {
        cout << j + 1 << ". " << menu_options.at(j) << endl;
    }
}

/***********************************************************************************************************
** Description: This function gets the choice from the user. The entered text is checked for errors
                and is returned to the program.
***********************************************************************************************************/
int Menu::get_choice()
{
    string choice;
    cout << "Selection: ";
    getline(cin, choice);
    return integer_range_check(choice, 1, get_number_of_options());
}

/***********************************************************************************************************
** Description: getter for the amount of options there are in a given menu
***********************************************************************************************************/
int Menu::get_number_of_options()
{
    return menu_options.size();
}