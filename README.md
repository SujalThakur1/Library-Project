Library Management System
This C++ project implements a Library Management System using the hash node data structure. The system allows the management of various types of items, such as books, DVDs, and CDs, and includes user management for borrowing and returning items.

Overview
The project includes basic functionality for managing books, library users, and handling borrowing and returning. Additionally, it extends the functionality to support different types of items beyond books, creating a generic library management system.

Getting Started
Clone the repository:

```bash
git clone https://github.com/your-username/library-management.git
cd library-management
```
Compile the program:

```bash
g++ main.cpp -o library_system
```
Run the program:
```bash
./library_system
```
Advanced Features
Generic Library Management System: The system can handle various types of items (e.g., books, DVDs, CDs).

Item Hierarchy: A generic Item class serves as the base class for different item types, with specific derived classes (e.g., Book, DVD, CD) extending the Item class.

Flexible User Class: The User class is generic, allowing it to handle different types of items when users borrow them.

Late Fee Calculation: Implements a system for storing borrowed book due dates and calculating late fees for overdue items. Allows customization of late fee rates based on the type of item.

Advanced Search Capabilities: Users can search for items based on multiple criteria, such as item type, title, author, genre, and availability. Wildcard searches (using '*' or '?') and fuzzy search algorithms are incorporated to broaden search capabilities.

Item Reservation System: Users can reserve items that are currently checked out. The system provides alerts when reserved books become available.
