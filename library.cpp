#include "library.h"

Library::Library()
{
    HashMap Map;
    booleanCheck = true;
}

int Library::addDataToHashMap()
{
    ifstream inputFile("inventory.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    // Read data from inventory.txt and populate HashMap
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string code, title, creator;
        int status;
        string userWHoReserved;
        list<int> userWhoReserved;
        ss >> code >> quoted(title) >> quoted(creator) >> status;
        if (ss >> userWHoReserved)
        {
            stringstream userStream(userWHoReserved);
            string user;
            while (getline(userStream, user, ','))
            {
                userWhoReserved.push_back(stoi(user));
            }
        }
        item item(title, creator, code, status, userWhoReserved);
        Map.addItem(item);
    }

    inputFile.close();

    ifstream inputFile2("users.txt");

    if (!inputFile2.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Read data from users.txt and populate HashMap with users
    while (getline(inputFile2, line))
    {
        stringstream ss(line);
        string userName, borrow, reserve;
        int userID;
        list<int> reservationAvailable;
        ss >> userID >> userName >> quoted(borrow) >> quoted(reserve);
        list<BorrowedItem> BORROW;
        list<Reservation> RESERVATION;

        istringstream sss(borrow);
        string item;
        while (getline(sss, item, ','))
        {
            size_t pos = item.find(':');
            string borrowItem = item.substr(0, pos);
            string dueDate = item.substr(pos + 1);
            BORROW.push_back(BorrowedItem(borrowItem, dueDate));
        }

        istringstream ssss(reserve);

        while (getline(ssss, item, ','))
        {
            size_t pos = item.find(':');
            string reserveItem = item.substr(0, pos);
            string available = item.substr(pos + 1);
            bool availabley = false;
            if (available == "1")
            {
                availabley = true;
            }
            RESERVATION.push_back(Reservation(reserveItem, availabley));
        }

        user user(userName, userID, BORROW, RESERVATION);
        Map.addUser(user);
    }

    inputFile2.close();

    return 0;
}

void Library::addToFile()
{
    ofstream outputFile("users.txt");

    if (!outputFile.is_open())
    {
        // Handle error if the file cannot be opened
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    list<user> allUser = Map.getAllUser();
    // Iterate through users and write to the file
    for (auto it = allUser.rbegin(); it != allUser.rend(); ++it)
    {
        user currentUser = *it;
        int userID = currentUser.getId();
        outputFile << userID << " " << currentUser.getName() << " ";
        list<BorrowedItem> Borrow = currentUser.getBorrowedItem();
        int count = 0;
        for (BorrowedItem borrowItem : Borrow)
        {
            if (count != 0)
            {
                outputFile << ",";
            }
            outputFile << borrowItem.getBorrowedItem() << ":" << borrowItem.getDueDate();
            count++;
        }
        outputFile << " ";
        list<Reservation> reservation = currentUser.getReservedItem();
        count = 0;
        for (Reservation reserve : reservation)
        {
            if (count != 0)
            {
                outputFile << ",";
            }
            outputFile << reserve.getReservedItem() << ":" << reserve.getAvailability();
            count++;
        }
        outputFile << endl;
    }

    outputFile.close();

    ofstream outputFile2("inventory.txt");

    if (!outputFile2.is_open())
    {
        // Handle error if the file cannot be opened
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    // Iterate through items and write to the file
    list<item> allItem = Map.allItem();
    for (item currentItem : allItem)
    {
        outputFile2 << currentItem.getCode() << " "
                    << "\""
                    << currentItem.getTitle() << "\""
                    << " "
                    << "\""
                    << currentItem.getCreator() << "\""
                    << " "
                    << currentItem.getStatus() << " ";
        int count = 0;
        for (int ID : currentItem.getReservedByUser())
        {
            if (count != 0)
            {
                outputFile2 << ",";
            }
            outputFile2 << ID;
            count++;
        }
        outputFile2 << endl;
    }

    outputFile2.close();
}

// Generating random code for DVD
string Library::getCodeForDVD()
{
    string code;
    string a1 = to_string(rand() % 10);
    string b2 = to_string(rand() % 10);
    string c3 = to_string(rand() % 10);
    string d4 = to_string(rand() % 10);
    string e5 = to_string(rand() % 10);
    char randomAlphabet = 'A' + rand() % 26;
    code = a1 + a1 + a1 + a1 + "-" + b2 + b2 + b2 + b2 + "-" + c3 + c3 + c3 + c3 + "-" + d4 + d4 + d4 + d4 + "-" + e5 + "-" + b2 + b2 + b2 + b2 + "-" + a1 + a1 + a1 + a1 + "-" + randomAlphabet;
    return code;
}

// Generating random code for Book
string Library::getCodeForBOOK()
{
    string code;
    int lastDigit = rand() % 10;
    int firstMiddleDigit = rand() % 8800 + 1101;
    int secondMiddleDigit = rand() % 8800 + 1101;

    code = "978-" + to_string(lastDigit) + "-" + to_string(firstMiddleDigit) + "-" +
           to_string(secondMiddleDigit) + "-" + to_string(lastDigit);
    return code;
}

void Library::addNewItem()
{
    int choice;
    string title;
    string creator;
    string code;

    // Seed for generating random codes
    srand(static_cast<unsigned int>(time(0)));

    do
    {
        // Display menu
        cout << "Choose an item to add:" << endl;
        cout << "1. CD" << endl;
        cout << "2. DVD" << endl;
        cout << "3. Book" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";

        // Validate user input
        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        // Process user's choice
        switch (choice)
        {
        case 1:
            cout << "Adding CD..." << endl;
            cout << "Enter CD title: ";
            cin.ignore();
            getline(cin, title);

            cout << "Enter CD artist: ";
            getline(cin, creator);

            // Generate a random code for CD
            code = "CDART" + to_string(rand() % 8651977 + 1234567);

            // Set choice to 0 to exit the loop
            choice = 0;
            break;
        case 2:
            cout << "Adding DVD..." << endl;
            cout << "Enter DVD title: ";
            cin.ignore();
            getline(cin, title);

            cout << "Enter DVD director: ";
            getline(cin, creator);

            // Generate a code for DVD
            code = getCodeForDVD();

            // Set choice to 0 to exit the loop
            choice = 0;
            break;
        case 3:
            cout << "Adding Book..." << endl;
            cout << "Enter Book title: ";
            cin.ignore();
            getline(cin, title);

            cout << "Enter Book author: ";
            getline(cin, creator);

            // Generate a code for Book
            code = getCodeForBOOK();

            // Set choice to 0 to exit the loop
            choice = 0;
            break;
        case 0:
            // User chose to go back
            cout << "Going back..." << endl;
            break;
        default:
            // Invalid choice
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    // Create an item with user input and add it to the Map
    item item(title, creator, code, 1);
    Map.addItem(item);

    cout << "Item has been added successfully." << endl;
}

void Library::removeItem()
{
    int choice;
    string code;

    do
    {
        // Display menu
        cout << "1. Remove CD\n";
        cout << "2. Remove DVD\n";
        cout << "3. Remove Book\n";
        cout << "0. Back\n";

        // Get user choice
        cout << "Enter your choice: ";

        // Validate user input
        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        // Process user choice
        switch (choice)
        {
        case 1:
        {
            // Remove CD
            string isrc;
            cout << "Enter CD ISRC: ";
            cin >> isrc;
            regex pattern("^CD[0-9A-Z]{10}$");

            // Validate ISRC format
            if (!regex_match(isrc, pattern))
            {
                cout << "Invalid ISRC format. Please enter a valid ISRC.\n";
                break;
            }

            cout << "Removing CD with ISRC " << isrc << "...\n";
            code = isrc;

            // Attempt to remove CD
            if (Map.removeItem(code))
            {
                cout << "CD has been successfully deleted" << endl;
            }
            else
            {
                cout << "Incorrect ISRC" << endl;
            }
            break;
        }
        case 2:
        {
            // Remove DVD
            string isan;
            cout << "Enter DVD ISAN: ";
            cin >> isan;
            regex pattern("^\\d{4}-\\d{4}-\\d{4}-\\d{4}-\\d-\\d{4}-\\d{4}-[A-Z]$");

            // Validate ISAN format
            if (!regex_match(isan, pattern))
            {
                cout << "Invalid ISAN format. Please enter a valid ISAN.\n";
                break;
            }

            cout << "Removing DVD with ISAN " << isan << "...\n";
            code = isan;

            // Attempt to remove DVD
            if (Map.removeItem(code))
            {
                cout << "DVD has been successfully deleted" << endl;
            }
            else
            {
                cout << "Incorrect ISAN" << endl;
            }
            break;
        }
        case 3:
        {
            // Remove Book
            string isbn;
            cout << "Enter Book ISBN: ";
            cin >> isbn;
            regex pattern("^978-[0-9]-[0-9]{4}-[0-9]{4}-[0-9]$");

            // Validate ISBN format
            if (!regex_match(isbn, pattern))
            {
                cout << "Invalid ISBN format. Please enter a valid ISBN.\n";
                break;
            }

            cout << "Removing Book with ISBN " << isbn << "...\n";
            code = isbn;

            // Attempt to remove Book
            if (Map.removeItem(code))
            {
                cout << "Book has been successfully deleted" << endl;
            }
            else
            {
                cout << "Incorrect ISBN" << endl;
            }
            break;
        }
        case 0:
            cout << "Going back...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

item Library::searchItemByIsbn(string ISBN)
{
    item item = Map.searchByISBN(ISBN);
    return item;
}
// Printing Item details
void Library::printItem(item item, bool boo)
{
    if (boo)
    {
        cout << "``````````````````````````````````````````````````````" << endl;
    }
    if (item.getCode().length() > 17)
    {
        cout << "Name of the DVD -> " << item.getTitle() << endl;
        if (boo)
        {
            cout << "Director Name -> " << item.getCreator() << endl;
            cout << "ISAN Code -> " << item.getCode() << endl;
        }
    }
    else if (item.getCode().length() == 17)
    {
        cout << "Name of the book is -> " << item.getTitle() << endl;
        if (boo)
        {
            cout << "Author Name -> " << item.getCreator() << endl;
            cout << "ISBN Code -> " << item.getCode() << endl;
        }
    }
    else
    {
        cout << "Name of the CD -> " << item.getTitle() << endl;
        if (boo)
        {
            cout << "Artist Name -> " << item.getCreator() << endl;
            cout << "ISRC Code -> " << item.getCode() << endl;
        }
    }
    if (boo)
    {
        if (item.getStatus() == 0)
        {
            cout << "Available -> No" << endl;
        }
        else
        {
            cout << "Available -> Yes" << endl;
        }
    }
}

void Library::displayAllItem()
{
    list<item> items = Map.allItem();
    for (item currentItem : items)
    {
        printItem(currentItem, true);
    }
}

int Library::addUser(bool isInteractive)
{
    bool isAlphabetic = true;
    string name;

    // Loop until a valid alphabetic name is entered
    while (isAlphabetic)
    {
        isAlphabetic = false;

        // Prompt the user based on the context
        if (isInteractive)
        {
            cout << "Please enter your name: ";
        }
        else
        {
            cout << "Enter User Name: ";
        }

        // Read user input
        getline(cin, name);

        // Check if the entered name contains only alphabets
        for (char c : name)
        {
            if (!isalpha(c))
            {
                isAlphabetic = true;
                cout << "Invalid name. Please enter only alphabets." << endl;
                break;
            }
        }
    }

    // Generate a unique user ID
    user topUser = Map.getTopUser();
    int ID = 1 + topUser.getId();

    // Create a new user with the entered name and generated ID
    user newUser(name, ID);

    // Add the new user to the library
    Map.addUser(newUser);

    // Display a success message if not in interactive mode
    if (!isInteractive)
    {
        cout << newUser.getName() << " with UserID " << newUser.getId() << " has been added" << endl;
    }

    // Return the generated user ID
    return ID;
}

void Library::removeUser()
{
    int userID;

    // Prompt the user to enter the ID of the user to be removed
    cout << "Enter the ID of the user you want to remove: ";

    // Validate and read the user ID
    while (!(cin >> userID))
    {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Check if the user is trying to remove themselves
    if (userID == CurrentUserID)
    {
        cout << "You can't remove yourself" << endl;
        return;
    }

    // Attempt to remove the user with the specified ID
    if (Map.removeUser(userID))
    {
        cout << "User with ID " << userID << " successfully removed." << endl;
    }
    else
    {
        cout << "User with ID " << userID << " not found." << endl;
    }
}
// Displaying user
void Library::displayAllUser()
{
    list<user> AllUsers = Map.getAllUser();
    for (user currentUser : AllUsers)
    {
        cout << "``````````````````````````````````````````````````````" << endl;
        cout << "User Name is -> " << currentUser.getName() << endl;
        cout << "User ID -> " << currentUser.getId() << endl;
        list<BorrowedItem> borrowedItems = currentUser.getBorrowedItem();
        if (!borrowedItems.empty())
        {
            cout << "Borrowed Items -> " << endl;
            for (BorrowedItem borrow : borrowedItems)
            {
                item item = searchItemByIsbn(borrow.getBorrowedItem());
                printItem(item, false);
                cout << "Due Date -> " << borrow.getDueDate() << endl;
            }
        }
        list<Reservation> reservedItem = currentUser.getReservedItem();
        if (!reservedItem.empty())
        {
            cout << "Reserved Items -> " << endl;
            for (Reservation reserve : reservedItem)
            {
                item item = searchItemByIsbn(reserve.getReservedItem());
                printItem(item, false);
            }
        }
        cout << "`````````````````````````````````````````````````````````" << endl;
    }
}

void Library::borrowItem(item item1)
{
    // Search for the item in the library using its ISBN/code
    item *newItem = Map.searchByISBN2(item1.getCode());

    // Prompt the user to borrow or reserve the item based on its status
    char response;
    if (newItem->getStatus() == 1)
    {
        cout << "Do you want to borrow this item? (y/n): ";
    }
    else
    {
        cout << "Do you want to reserve this item? (y/n): ";
    }

    cin >> response;

    // Process user's response
    if (response == 'y' || response == 'Y')
    {
        // Get the current user
        user *MainUser = Map.searchUser2(CurrentUserID);

        // If the item is available for borrowing
        if (newItem->getStatus() == 1)
        {
            // Calculate due date (5 days from the current date)
            time_t t = time(0);
            t += 5 * 24 * 60 * 60;
            tm *now = localtime(&t);
            string date = to_string(now->tm_year + 1900) + '-' +
                          (now->tm_mon + 1 < 10 ? "0" : "") + to_string(now->tm_mon + 1) + '-' +
                          (now->tm_mday < 10 ? "0" : "") + to_string(now->tm_mday);

            // Add the item to the user's borrowed items
            MainUser->AddBorrowedItem(item1.getCode(), date);

            // Remove the item from the user's reserved items (if present)
            list<Reservation> ItemsId = MainUser->getReservedItem();
            for (Reservation reserve : ItemsId)
            {
                if (reserve.getReservedItem() == item1.getCode())
                {
                    MainUser->RemoveReservedItem(reserve);
                }
            }

            cout << "You Borrow an Item" << endl;
        }
        // If the item is not available for borrowing, reserve it
        else
        {
            MainUser->AddreservedItem(item1.getCode(), 0);
            Map.setReservedByUser(newItem->getCode(), CurrentUserID);
            cout << "Item has been reserved for you" << endl;
            cout << "You will get a notification when the item is available" << endl;
        }

        // Update the status of the item to unavailable
        Map.setStatus(newItem->getCode(), false);
    }
    else
    {
        // User chose not to borrow or reserve the item
        return;
    }
}

void Library::returnItem()
{
    // Variables to store user input
    string itemCode;
    int type = 0;

    // Prompt user to enter the item code for return
    cout << "Enter the item code you want to return: ";
    cin >> itemCode;

    // Define regex patterns for different item types (CD, DVD, Book)
    regex pattern("^CD[0-9A-Z]{10}$");
    regex pattern2("^\\d{4}-\\d{4}-\\d{4}-\\d{4}-\\d-\\d{4}-\\d{4}-[A-Z]$");
    regex pattern3("^978-[0-9]-[0-9]{4}-[0-9]{4}-[0-9]$");

    // Determine the type of the item based on the regex patterns
    if (regex_match(itemCode, pattern))
    {
        type = 1; // CD
    }
    else if (regex_match(itemCode, pattern2))
    {
        type = 2; // DVD
    }
    else if (regex_match(itemCode, pattern3))
    {
        type = 3; // Book
    }

    // Check if the item code is valid
    if (type != 0)
    {
        // Get the current user
        user *MainUser = Map.searchUser2(CurrentUserID);

        // Get the current date for return
        time_t t = time(0);
        tm *now = localtime(&t);
        string date = to_string(now->tm_year + 1900) + '-' +
                      (now->tm_mon + 1 < 10 ? "0" : "") + to_string(now->tm_mon + 1) + '-' +
                      (now->tm_mday < 10 ? "0" : "") + to_string(now->tm_mday);

        // Check if the user has the returning item
        if (MainUser->returnItem(itemCode, date, type))
        {
            // Get the item from the library
            item *item = Map.searchByISBN2(itemCode);

            // Get the list of users who have reserved the item
            list<int> usersWhoReserve = item->getReservedByUser();

            // Notify users that the item is available
            cout << "Item Has Been Returned Successfully" << endl;
            cout << "The item is now available in the library." << endl;

            // Notify users who have reserved the item to come and collect it
            for (int userID : usersWhoReserve)
            {
                cout << "User with ID " << userID << ", please come and collect it!" << endl;

                // Update the availability status of the reserved item
                user *curUser = Map.searchUser2(userID);
                list<Reservation> *reservedItems = curUser->getReservedItemWithPointer();
                for (Reservation &reserve : *reservedItems)
                {
                    if (reserve.getReservedItem() == itemCode)
                    {
                        reserve.setAvailability(true);
                    }
                }
            }

            // Update the status of the item in the library to available
            Map.setStatus(itemCode, true);
        }
        else
        {
            // Inform the user that they don't have the returning item
            cout << "You don't have the returning item." << endl;
        }
    }
    else
    {
        // Inform the user about the invalid item code format
        cout << "Invalid Code format. Please enter a valid Item Code.\n";
        return;
    }
}

void Library::search()
{
    int choice;
    bool isAlphabetic;

    // Menu for search options
    while (true)
    {
        cout << "What would you like to search for?\n";
        cout << "1. Search by name (WildCard Search and Fuzzy Search available)\n";
        cout << "2. Search by code\n";
        cout << "3. Search by creator (WildCard Search and Fuzzy Search available)\n";
        cout << "4. Search by status\n";
        cout << "5. Search by type\n";
        cout << "0. Exit\n";
        cout << "Enter your choice (1-6): ";

        // Validate user input
        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }
        cin.ignore(); // Clear the newline character from the buffer

        // Process user's choice
        switch (choice)
        {
        case 1:
            // Search by name
            {
                string itemName;
                isAlphabetic = true;

                // Prompt user for the name of the item
                cout << "Enter the name of the item: ";
                getline(cin, itemName);

                // Perform wildcard search if * or ? are present in the name
                if (itemName.find("*") != string::npos || itemName.find("?") != string::npos)
                {
                    list<item> items = Map.searchByWildCard(itemName, true);
                    if (!items.empty())
                    {
                        for (item item : items)
                        {
                            printItem(item, true);
                        }
                    }
                    else
                    {
                        cout << "No item found" << endl;
                    }
                }
                else
                {
                    // Perform exact search by title
                    item item = Map.searchByTitle(itemName);
                    if (!item.getTitle().empty())
                    {
                        printItem(item, true);
                        bool doUserNeedToBorrow = false;
                        user *mainUser = Map.searchUser2(CurrentUserID);
                        for (BorrowedItem borrow : mainUser->getBorrowedItem())
                        {
                            if (borrow.getBorrowedItem() == item.getCode())
                            {
                                doUserNeedToBorrow = true;
                                break;
                            }
                        }
                        if (!doUserNeedToBorrow)
                        {
                            borrowItem(item);
                        }
                    }
                }
            }
            break;
        case 2:
            // Search by code
            {
                string itemCode;
                // Prompt user for the code of the item
                cout << "Enter the code of the item: ";
                getline(cin, itemCode);
                item item = Map.searchByISBN(itemCode);
                if (!item.getTitle().empty())
                {
                    printItem(item, true);
                    bool doUserNeedToBorrow = false;
                        user *mainUser = Map.searchUser2(CurrentUserID);
                        for (BorrowedItem borrow : mainUser->getBorrowedItem())
                        {
                            if (borrow.getBorrowedItem() == item.getCode())
                            {
                                doUserNeedToBorrow = true;
                                break;
                            }
                        }

                        if (!doUserNeedToBorrow)
                        {
                            borrowItem(item);
                        }
                }
            }
            break;
        case 3:
            // Search by creator
            {
                string creatorName;
                // Prompt user for the name of the creator
                cout << "Enter the name of the creator: ";
                getline(cin, creatorName);
                if (creatorName.find("*") != string::npos || creatorName.find("?") != string::npos)
                {
                    // Perform wildcard search if * or ? are present in the creator name
                    list<item> items = Map.searchByWildCard(creatorName, false);
                    if (!items.empty())
                    {
                        for (item item : items)
                        {
                            printItem(item, true);
                        }
                    }
                    else
                    {
                        cout << "No item found" << endl;
                    }
                }
                else
                {
                    // Perform exact search by author
                    item item = Map.searchByAuthor(creatorName);
                    if (!item.getTitle().empty())
                    {
                        printItem(item, true);
                        bool doUserNeedToBorrow = false;
                        user *mainUser = Map.searchUser2(CurrentUserID);
                        for (BorrowedItem borrow : mainUser->getBorrowedItem())
                        {
                            if (borrow.getBorrowedItem() == item.getCode())
                            {
                                doUserNeedToBorrow = true;
                                break;
                            }
                        }

                        if (!doUserNeedToBorrow)
                        {
                            borrowItem(item);
                        }
                    }
                }
            }
            break;
        case 4:
            // Search by status
            {
                int status;
                isAlphabetic = true;
                while (isAlphabetic)
                {
                    isAlphabetic = false;
                    // Prompt user for the status of the item
                    cout << "Enter the status of the item: (eg. 1 for available and 0 for unavailable)" << endl;
                    if (!(cin >> status))
                    {
                        cout << "Invalid input. Please enter 0 or 1." << endl;
                        choice = -1;
                        isAlphabetic = true;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else
                    {
                        if (status != 0 && status != 1)
                        {
                            isAlphabetic = true;
                        }
                    }
                }
                // Perform search by status
                list<item> items = Map.searchByStatus(status);
                for (item item : items)
                {
                    printItem(item, true);
                }
            }
            break;
        case 5:
            // Search by type
            {
                string itemType;
                isAlphabetic = true;
                while (isAlphabetic)
                {
                    isAlphabetic = false;
                    // Prompt user for the type of the item
                    cout << "Enter the type of the item: (eg. Book, DVD, CD)" << endl;
                    cin >> itemType;
                    if (itemType != "Book" && itemType != "DVD" && itemType != "CD")
                    {
                        cout << "Invalid Item Type. Please enter a valid Type" << endl;
                        isAlphabetic = true;
                    }
                }
                // Perform search by type
                list<item> items = Map.searchByType(itemType);
                for (item item : items)
                {
                    printItem(item, true);
                }
            }
            break;
        case 0:
            // Exit the search menu
            cout << "Exiting the search menu.\n";
            return;
        default:
            // Invalid choice
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }
}

// Displaying All the library options
void Library::displayLibraryOptions()
{
    int choice;

    do
    {
        cout << "Library Menu Options:" << endl;
        cout << "1. Display all users in the library" << endl;
        cout << "2. Display all items in the library" << endl;
        cout << "3. Search for an item in the library and borrow" << endl;
        cout << "4. Remove user" << endl;
        cout << "5. Remove item" << endl;
        cout << "6. Add item" << endl;
        cout << "7. Add user" << endl;
        cout << "8. Return Item" << endl;
        cout << "0. Back" << endl;

        cout << "Enter your choice (1-8): ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            displayAllUser();
            break;
        case 2:
            displayAllItem();
            break;
        case 3:
            search();
            break;
        case 4:
            removeUser();
            break;
        case 5:
            removeItem();
            break;
        case 6:
            addNewItem();
            break;
        case 7:
            addUser(false);
            break;
        case 8:
            returnItem();
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }

    } while (choice != 0);
}

void Library::userChoice()
{
    while (true)
    {
        int user_id;

        // Prompt the user to enter their 3-digit ID number or 'r' if they don't have an ID
        cout << "Please enter your 3-digit ID number (or press 'r' if you don't have an ID): ";

        // Check if the input is an integer
        if (cin >> user_id)
        {
            // Check if the entered user ID exists in the library
            if (Map.searchUser(user_id))
            {
                CurrentUserID = user_id;
                user *MainUser = Map.searchUser2(CurrentUserID);

                // Check and notify the user about available reserved items
                list<Reservation> reserveItem = MainUser->getReservedItem();
                for (Reservation reserve : reserveItem)
                {
                    if (reserve.getAvailability())
                    {
                        item item = Map.searchByISBN(reserve.getReservedItem());
                        cout << "Hey " << MainUser->getName() << endl;
                        cout << "Item With Name " << item.getTitle() << " is now available in the library" << endl;
                    }
                }

                // Display library options for the user
                displayLibraryOptions();
                break;
            }
            else
            {
                cout << "Incorrect User ID" << endl;
            }
        }
        else
        {
            // Clear input buffer and welcome a new user
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Hello New User" << endl;

            // Add a new user and display their assigned ID
            CurrentUserID = addUser(true);
            cout << "Your ID is now: " << CurrentUserID << endl;

            // Display library options for the new user
            displayLibraryOptions();
            break;
        }
    }
}

void Library::run()
{
    cout << "Welcome to the Library!" << endl;

    while (true)
    {
        cout << "\nMenu:" << endl;
        cout << "1. Enter" << endl;
        cout << "2. Leave" << endl;

        int choice;
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Adding to hash map from file only 1 time
            if (booleanCheck)
            {
                addDataToHashMap();
                booleanCheck = false;
            }

            userChoice();
            break;
        case 2:
            // Adding HashMap data to file only if HashMap had add data from file first
            if (!booleanCheck)
            {
                addToFile();
            }
            cout << "Goodbye!" << endl;
            return;
        default:
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }
    }
}
