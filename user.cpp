#include <iostream>
#include "user.h"

Reservation::Reservation()
{
    reservedItem = "";
    isAvailable = -1;
}

Reservation::Reservation(string item, bool available)
{
    reservedItem = item;
    isAvailable = available;
}

string Reservation::getReservedItem()
{
    return reservedItem;
}

bool Reservation::getAvailability()
{
    return isAvailable;
}

void Reservation::setAvailability(bool available)
{
    isAvailable = available;
}

bool Reservation::operator==(const Reservation &other) const
{
    return (reservedItem == other.reservedItem) && (isAvailable == other.isAvailable);
}

BorrowedItem::BorrowedItem()
{
    this->borrowItem = "";
    this->dueDate = "";
}

BorrowedItem::BorrowedItem(string borrowItem, string dueDate)
{
    this->borrowItem = borrowItem;
    this->dueDate = dueDate;
}

string BorrowedItem::getBorrowedItem()
{
    return borrowItem;
}

string BorrowedItem::getDueDate()
{
    return dueDate;
}

void BorrowedItem::setDueDate(string dueDate)
{
    this->dueDate = dueDate;
}

bool BorrowedItem::operator==(const BorrowedItem &other) const
{
    // Assuming that equality is based on both borrowItem and dueDate
    return (borrowItem == other.borrowItem) && (dueDate == other.dueDate);
}

user::user()
{
    this->userName = "";
    this->userID = 0;
}

user::user(string name, int Id, list<BorrowedItem> borrow, list<Reservation> reserved)
{
    this->userName = name;
    this->userID = Id;
    this->borrow = borrow;
    this->reserved = reserved;
}

user::user(string name, int Id)
{
    this->userName = name;
    this->userID = Id;
}

string user::getName()
{
    return userName;
}

int user::getId()
{
    return userID;
}

list<BorrowedItem> user::getBorrowedItem()
{
    return borrow;
}

list<Reservation> user::getReservedItem()
{
    return reserved;
}

list<Reservation>* user::getReservedItemWithPointer(){
    return &(reserved);
}

void user::AddBorrowedItem(string Code, string Date)
{
    BorrowedItem boo(Code, Date);
    borrow.push_back(boo);
}

void user::AddreservedItem(string Code, bool boo)
{
    Reservation res(Code, boo);
    reserved.push_back(res);
}

void user::RemoveReservedItem(Reservation deleteReserve)
{
    reserved.remove(deleteReserve);
}

bool user::returnItem(string Code, string currentDate, int type)
{
    // Iterate through the list of borrowed items
    for (BorrowedItem borrowItem : borrow)
    {
        // Check if the current borrowed item matches the specified code
        if (borrowItem.getBorrowedItem() == Code)
        {
            // Check if the item is overdue
            if (borrowItem.getDueDate() < currentDate)
            {
                // Penalty logic based on the item type
                if (type == 1)
                {
                    cout << "CD with ISRC " << Code << " is overdue. A penalty of 20 pounds is applied." << endl;
                }
                else if (type == 2)
                {
                    cout << "DVD with ISAN " << Code << " is overdue. A penalty of 30 pounds is applied." << endl;
                }
                else
                {
                    cout << "Book with ISBN " << Code << " is overdue. A penalty of 10 pounds is applied." << endl;
                }

                // Remove the overdue item from the borrow list
                borrow.remove(borrowItem);
                return true; // Item returned with a penalty
            }
            else
            {
                // Item is not overdue
                cout << "Item with code " << Code << " returned successfully." << endl;
                cout << "Item is not overdue so NO penalty :-)" << endl;
                // Remove the item from the borrow list
                borrow.remove(borrowItem);

                return true; // Item returned successfully
            }
        }
    }

    // The specified item code was not found in the list of borrowed items
    return false;
}