#ifndef USER
#define USER

#include <list>
using namespace std;

// Class representing a reservation
class Reservation
{
private:
    string reservedItem;
    bool isAvailable;

public:
    Reservation();
    Reservation(string item, bool available);
    string getReservedItem();
    bool getAvailability();
    void setAvailability(bool available);
    bool operator==(const Reservation& other) const;
};

// Class representing a borrowed item
class BorrowedItem
{
private:
    string borrowItem;
    string dueDate;

public:
    BorrowedItem();
    BorrowedItem(string borrowItem, string dueDate);
    string getBorrowedItem();
    string getDueDate();
    void setDueDate(string dueDate);
    bool operator==(const BorrowedItem& other) const;
};

// Class representing a user with borrowed items and reservations
class user
{
private:
    string userName;
    int userID;
    list<BorrowedItem> borrow;
    list<Reservation> reserved;

public:
    // Constructors
    user();
    user(string name, int Id, list<BorrowedItem> borrow, list<Reservation> reserved);
    user(string name, int ID);

    // Getter methods
    string getName();
    int getId();
    list<BorrowedItem> getBorrowedItem();
    list<Reservation> getReservedItem();
    list<Reservation>* getReservedItemWithPointer();

    // Methods for adding borrowed and reserved items
    void AddBorrowedItem(string Code, string dueDate);
    void AddreservedItem(string Code, bool boo);

    // Method for removing a reserved item
    void RemoveReservedItem(Reservation deleteReservation);

    // Method for returning an item
    bool returnItem(string Code, string date, int type);
};

#endif
