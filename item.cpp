// item.cpp
#include "item.h"
item::item() {
    // Default constructor
    title = "";
    Code = "";
    creator = "";
    status = 0;
}

item::item(string title,string creator,string code, int status) {
    this->title = title;
    this->Code = code;
    this->creator = creator;
    this->status = status;
}

item::item(string title,string creator,string code, int status, list<int> reservedByUser) {
    // Parameterized constructor
    this->title = title;
    this->Code = code;
    this->creator = creator;
    this->status = status;
    this->reservedByUser = reservedByUser;
}

string item::getTitle(){
    return title;
}

string item::getCreator(){
    return creator;
}

string item::getCode() {
    return Code;
}

int item::getStatus(){
    return status;
}

void item::setStatus(int s) {
    status = s;
}

list<int> item::getReservedByUser(){
    return reservedByUser;
}

void item::setReservedByUser(int UserID){
    reservedByUser.push_back(UserID);
}

bool item::operator==(const item& other) const {
        // Implement the comparison logic based on your class attributes
        return (Code == other.Code && title == other.title && creator == other.creator /* add more as needed */);
    }

book::book(string title, string author, string ISBN, int status) : item(title,author,ISBN,status)
{
    // Initialize book-specific attributes
    this->author = author;
    this->ISBN = ISBN;
}

string book::getISBN() {
    return ISBN;
}

string book::getAuthor() {
    return author;
}

cd::cd(string title, string artist, string ISRC, int status): item(title,artist,ISRC,status)
     {
    // Initialize cd-specific attributes
    this->artist = artist;
    this->ISRC = ISRC;
}

string cd::getArtist() {
    return artist;
}

string cd::getISRC() {
    return ISRC;
}

dvd::dvd(string title, string director, string ISAN, int status): item(title,director,ISAN,status)
     {
    this->Director = director;
    this->ISAN = ISAN;
}

string dvd::getDirector() {
    return Director;
}

string dvd::getISAN() {
    return ISAN;
}
