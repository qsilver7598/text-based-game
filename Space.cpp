/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the abstract space class. The functions are the setters
                and getters for the member variables.
***********************************************************************************************************/

#include "Space.hpp"
#include "Game.hpp"

#include <string>

/***********************************************************************************************************
** Description: setter for the top pointer
***********************************************************************************************************/
void Space::set_top(Space *room)
{
    top = room;
}

/***********************************************************************************************************
** Description: setter for the left pointer
***********************************************************************************************************/
void Space::set_left(Space *room)
{
    left = room;
}

/***********************************************************************************************************
** Description: setter for the right pointer
***********************************************************************************************************/
void Space::set_right(Space *room)
{
    right = room;
}

/***********************************************************************************************************
** Description: setter for the bottom pointer
***********************************************************************************************************/
void Space::set_bottom(Space *room)
{
    bottom = room;
}

/***********************************************************************************************************
** Description: getter for the top pointer
***********************************************************************************************************/
Space *Space::get_top()
{
    return top;
}

/***********************************************************************************************************
** Description: getter for the left pointer
***********************************************************************************************************/
Space *Space::get_left()
{
    return left;
}

/***********************************************************************************************************
** Description: getter for the right pointer
***********************************************************************************************************/
Space *Space::get_right()
{
    return right;
}

/***********************************************************************************************************
** Description: getter for the bottom pointer
***********************************************************************************************************/
Space *Space::get_bottom()
{
    return bottom;
}

/***********************************************************************************************************
** Description: getter for the name
***********************************************************************************************************/
std::string Space::get_name()
{
    return name;
}

/***********************************************************************************************************
** Description: getter for the condition of the portal flag
***********************************************************************************************************/
bool Space::get_portal()
{
    return entered_portal;
}