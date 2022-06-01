/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the header file for the input checking functions. The functions included are
                one that returns an int within a certain range, one that returns an int with no range 
                restriction, one function that checks to make sure a blank string is not entered, and
                a function that checks if the user just pushed enter.
***********************************************************************************************************/

#ifndef INPUTVAL_HPP
#define INPUTVAL_HPP

#include <string>

using std::string;

int integer_range_check(string input, int min_val, int max_val);
int integer_check(string input);
string check_string(string input);
bool check_string_blank(string input);

#endif