/***********************************************************************************************************
** Program name: Final Project
** Author: Adam Silver
** Date: 9 Dec 2019
** Description: This is the implementation file for the input checking functions. The functions included are
                one that returns an int within a certain range, one that returns an int with no range 
                restriction, one function that checks to make sure a blank string is not entered, and
                a function that checks if the user just pushed enter.
***********************************************************************************************************/

#include "InputVal.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::stoi;

/***********************************************************************************************************
** Description: This function takes in a user entered string as parameter. It also takes in a min value and 
                a max value. It itereates through the string looking for non integers. If one is found it 
                will ask the user to reenter the input. If the user entered value is correct it will 
                return the integer back to the program.
***********************************************************************************************************/
int integer_range_check(string input, int min_val, int max_val)
{
    bool valid_integer;

    do
    {
        valid_integer = true;

        // user does not enter anything
        if (input.length() == 0)
        {
            valid_integer = false;
            cout << "You have not entered a value. Please try again." << endl;
            cout << "Selection: ";
            getline(cin, input);
        }
        else
        {
            // Ranged based for loop that iterates over each character in the string and looks for non numbers.
            for (char& c : input)
            {
                if (!isdigit(c))
                {
                    valid_integer = false;
                }
            }
        
            if (!valid_integer)
            {
                cout << "You have not entered a valid number. Please try again." << endl;
                cout << "Selection: ";
                getline(cin, input);
            }
            else
            {
                // converts string to an integer
                int x = stoi(input);
                if (x >= min_val && x <= max_val)
                {
                    valid_integer = true;
                    return x;
                }
                else if (x < min_val)
                {
                    valid_integer = false;
                    cout << "You have entered a number less than " << min_val << ". Please try again." << endl;
                    cout << "Selection: ";
                    getline(cin, input);
                }
                else
                {
                    valid_integer = false;
                    cout << "You have entered a number greater than " << max_val << ". Please try again." << endl;
                    cout << "Selection: ";
                    getline(cin, input);
                }
            }
        }
    } while (!valid_integer);
}

/***********************************************************************************************************
** Description: This function takes in a user entered string as parameter. It itereates through the string
                looking for non integers. If one is found it will ask the user to reenter the input. If 
                the user entered value is correct it will return the integer back to the program.
***********************************************************************************************************/
int integer_check(string input)
{
    bool valid_integer;

    do
    {
        valid_integer = true;

        // user does not enter anything
        if (input.length() == 0)
        {
            valid_integer = false;
            cout << "You have not entered a value. Please try again." << endl;
            cout << "Selection: ";
            getline(cin, input);
        }
        else
        {
            // Ranged based for loop that iterates over each character in the string and looks for non numbers.
            for (char& c : input)
            {
                if (!isdigit(c))
                {
                    valid_integer = false;
                }
            }
        
            if (!valid_integer)
            {
                cout << "You have not entered a valid number. Please try again." << endl;
                cout << "Selection: ";
                getline(cin, input);
            }
            else
            {
                // converts string to integer
                int x = stoi(input);
                valid_integer = true;
                return x;
            }
        }
    } while (!valid_integer);
}

/***********************************************************************************************************
** Description: This function checks the users inputted string. Makes sure the user has not entered a blank
                string.
***********************************************************************************************************/
string check_string(string input)
{
    bool good_string;

    do
    {
        good_string = true;

        if (input.length() == 0)
        {
            good_string = false;
            cout << "You have entered a blank string. Please try again." << endl;
            cout << "String: ";
            getline(cin, input);
        }
    } while (!good_string);

    return input;
}

/***********************************************************************************************************
** Description: This function checks the users inputted string. It will return a true if the string
                passed to it is blank. Otherwise it will continue in a loop until the string is blank
***********************************************************************************************************/
bool check_string_blank(string input)
{
    bool good_string;

    do
    {
        good_string = true;

        if (input.length() != 0)
        {
            good_string = false;
            cout << "You have not pushed enter. Please try again." << endl;
            getline(cin, input);
        }
    } while (!good_string);

    return true;
}