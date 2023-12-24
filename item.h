#ifndef ITEM
#define ITEM

#include <string>
#include <list>

using namespace std;
class item {
private:
    string title;
    string Code;
    string creator;
    int status;
    list<int> reservedByUser;

public:
    // Constructors
    item();
    item(string title, string creator, string code, int status);
    item(string title, string creator, string Code, int status, list<int> reservedByUser);

    // Getter methods
    string getTitle();
    string getCreator();
    string getCode();
    int getStatus();
    list<int> getReservedByUser();

    // Setter methods
    void setReservedByUser(int reservedByUser);
    void setStatus(int s);

    // Overloaded equality operator
    bool operator==(const item& other) const;
};

#endif

#ifndef BOOK
#define BOOK

#include "item.h"

class book : public item {
private:
    string ISBN;
    string author;

public:
    // Constructor
    book(string title, string author, string ISBN, int status);

    // Getter methods for book-specific attributes
    string getISBN();
    string getAuthor();
};

#endif

#ifndef CD
#define CD

#include "item.h"

class cd : public item {
private:
    string artist;
    string ISRC;

public:
    // Constructor
    cd(string title, string artist, string ISRC, int status);

    // Getter methods for cd-specific attributes
    string getArtist();
    string getISRC();
};

#endif

#ifndef DVD
#define DVD

#include "item.h"

class dvd : public item {
private:
    string Director;
    string ISAN;

public:
    // Constructor
    dvd(string title, string director, string ISAN, int status);

    // Getter methods for dvd-specific attributes
    string getDirector();
    string getISAN();
};

#endif
