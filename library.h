#ifndef LIBRARY
#define LIBRARY
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "user.h"
#include "item.h"
#include "HashMap.h"
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <regex>
#include <ctime>
#include <algorithm>
using namespace std;

// Class representing a Library
class Library
{
private:
    HashMap Map;          // Instance of the HashMap class to store items
    int CurrentUserID;    // ID of the current user who is log in
    bool booleanCheck;    // Boolean flag for checking purposes

public:
    // Constructor for the Library class
    Library();

    // Function to add data to the HashMap for file
    int addDataToHashMap();

    // Function to add data to the file from HashMap
    void addToFile();

    // Function to generate a code for a DVD
    string getCodeForDVD();

    // Function to generate a code for a book
    string getCodeForBOOK();

    // Function to add a new item to the library
    void addNewItem();

    // Function to remove an item from the library
    void removeItem();

    // Function to search for an item by its ISBN
    item searchItemByIsbn(string ISBN);

    // Function to print information about an item
    void printItem(item item, bool boo);

    // Function to display information about all items in the library
    void displayAllItem();

    // Function to add a new user to the library
    int addUser(bool boo);

    // Function to remove a user from the library
    void removeUser();

    // Function to display information about all users in the library
    void displayAllUser();

    // Function to handle the process of borrowing an item
    void borrowItem(item item1);

    // Function to handle the process of returning an item
    void returnItem();

    // Function to perform all searches in the library
    void search();

    // Function to display the available library options
    void displayLibraryOptions();

    // Function is a log in page for users
    void userChoice();

    // Function to run the library management system
    void run();
};

#endif
