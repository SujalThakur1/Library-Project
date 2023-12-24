#ifndef HASHMAP
#define HASHMAP

#include <vector>
#include <algorithm>
#include <unordered_map>
#include "item.h"
#include "user.h"
#include <string>
#include "list"
using namespace std;

class HashMap {
private:
    // Maps for efficient data storage and retrieval
    unordered_map<string, item> isbnMap;        // Map for ISBN-based item lookup
    unordered_map<string, item> titleMap;       // Map for title-based item lookup
    unordered_map<string, item> authorMap;      // Map for author-based item lookup
    unordered_map<int, list<item>> statusMap;   // Map for status-based item lookup
    unordered_map<string, list<item>> typeMap;  // Map for type-based item lookup
    unordered_map<int, user> userMap;           // Map for user data storage

public:
    // Method to retrieve a list of all items
    list<item> allItem();

    // Method to retrieve a list of all users
    list<user> getAllUser();

    // Method to get the user with highest ID
    user getTopUser();

    // Method to add an item to the HashMap
    void addItem(item item);

    // Method to add a user to the HashMap
    void addUser(user user);

    // Methods for searching items by different criteria
    item searchByISBN(string isbn);
    item* searchByISBN2(string isbn);
    item searchByTitle(string title);
    int levenshteinDistance(const string& s1, const string& s2);
    item searchByAuthor(string author);
    list<item> searchByWildCard(string wildCard, bool boo);
    bool wildCardValidation(string wildCard, string name);
    list<item> searchByStatus(int status);
    list<item> searchByType(string type);

    // Method to remove an item
    bool removeItem(string code);

    // Method to set the status of an item
    void setStatus(string code, bool boo);

    // Method to set the reserved status of an item for a user
    void setReservedByUser(string code, int userID);

    // Method to remove a user by their ID
    bool removeUser(int ID);

    // Method to check if a user with a given ID exists
    bool searchUser(int ID);

    // Method to search for a user by their ID
    user* searchUser2(int ID);
};

#endif
