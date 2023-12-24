#include <iostream>
#include "HashMap.h"

list<item> HashMap::allItem()
{
    list<item> allItems;
    for (const auto &itemPair : isbnMap)
    {
        allItems.push_back(itemPair.second);
    }
    return allItems;
}

list<user> HashMap::getAllUser()
{
    list<user> allUsers;
    for (const auto &userPair : userMap)
    {
        allUsers.push_back(userPair.second);
    }
    return allUsers;
}

user HashMap::getTopUser()
{
    if (!userMap.empty())
    {
        auto it = userMap.begin();
        return it->second;
    }
    else
    {
        cerr << "UserMap is empty." << endl;
        return user();
    }
}

void HashMap::addItem(item newItem)
{
    string type;
    if (newItem.getCode().length() == 17)
    {
        type = "Book";
    }
    else if (newItem.getCode().length() > 17)
    {
        type = "DVD";
    }
    else
    {
        type = "CD";
    }
    isbnMap[newItem.getCode()] = newItem;
    titleMap[newItem.getTitle()] = newItem;
    authorMap[newItem.getCreator()] = newItem;
    statusMap[newItem.getStatus()].push_back(newItem);
    typeMap[type].push_back(newItem);
}

void HashMap::addUser(user user)
{
    int index = user.getId() - 100;
    userMap[index] = user;
}

item HashMap::searchByISBN(string isbn)
{
    auto it = isbnMap.find(isbn);

    if (it != isbnMap.end())
    {
        return it->second;
    }
    else
    {
        cerr << "Item with ISBN " << isbn << " not found." << endl;
        return item();
    }
}
// Method to search for an item by ISBN and return a pointer
item *HashMap::searchByISBN2(string isbn)
{
    auto it = isbnMap.find(isbn);

    if (it != isbnMap.end())
    {
        return &(it->second);
    }
    else
    {
        cerr << "Item with ISBN " << isbn << " not found." << endl;
        return nullptr;
    }
}

item HashMap::searchByTitle(string title)
{
    auto it = titleMap.find(title);

    if (it != titleMap.end())
    {

        return it->second;
    }
    else
    {
        cerr << "Item not found by exact title. Trying fuzzy search..." << endl;
        // Fuzzy search for similar titles
        for (const auto &itemPair : titleMap)
        {
            const string &itemTitle = itemPair.first;
            int distance = levenshteinDistance(title, itemTitle);

            // You can adjust the threshold based on your requirements
            if (distance <= 2)
            {
                cerr << "Fuzzy match found: " << itemTitle << endl;
                return itemPair.second;
            }
        }

        cerr << "Item with title " << title << " not found." << endl;
        return item();
    }
}

int HashMap::levenshteinDistance(const string &s1, const string &s2)
{
    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (i == 0)
            {
                dp[i][j] = j;
            }
            else if (j == 0)
            {
                dp[i][j] = i;
            }
            else if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    return dp[m][n];
}

item HashMap::searchByAuthor(string author)
{
    auto it = authorMap.find(author);
    if (it != authorMap.end())
    {
        return it->second;
    }
    else
    {
        cerr << "Item not found by exact Author name. Trying fuzzy search..." << endl;
        // Fuzzy search for similar authors
        for (const auto &itemPair : authorMap)
        {
            const string &itemAuthor = itemPair.first;
            int distance = levenshteinDistance(author, itemAuthor);

            // You can adjust the threshold based on your requirements
            if (distance <= 2)
            {
                cerr << "Fuzzy match found: " << itemAuthor << endl;
                return itemPair.second;
            }
        }
        cerr << "Item with author " << author << " not found." << endl;
        return item();
    }
}

// Method to search for items by status
list<item> HashMap::searchByStatus(int status)
{
    auto it = statusMap.find(status);
    if (it != statusMap.end())
    {
        return it->second;
    }
    else
    {
        cerr << "Item with status " << status << " not found." << endl;
        return list<item>();
    }
}

list<item> HashMap::searchByType(string type)
{
    auto it = typeMap.find(type);
    if (it != typeMap.end())
    {
        return it->second;
    }
    else
    {
        cerr << "Item with type " << type << " not found." << endl;
        return list<item>();
    }
}

list<item> HashMap::searchByWildCard(string wildCard, bool boo)
{
    list<item> wildcard;
    for (const auto &itemPair : isbnMap)
    {
        item item = itemPair.second;
        string name;
        if (boo)
        {
            name = item.getTitle();
        }
        else
        {
            name = item.getCreator();
        }
        // Check if the current item's title or creator matches the wildcard pattern
        if (wildCardValidation(wildCard, name))
        {
            wildcard.push_back(item);
        }
    }
    return wildcard;
}

// Method to validate wildcard pattern against a string
bool HashMap::wildCardValidation(string wildCard, string name)
{
    size_t i = 0;
    size_t j = 0;
    while (i < name.size() && j < wildCard.size())
    {
        if (wildCard[j] == '?' || name[i] == wildCard[j])
        {
            ++i;
            ++j;
        }
        else if (wildCard[j] == '*')
        {
            ++j;
            if (j == wildCard.size())
            {
                return true;
            }
            while (i < name.size() && name[i] != wildCard[j])
            {
                ++i;
            }
        }
        else
        {
            return false;
        }
    }
    return (i == name.size() && j == wildCard.size());
}
//method to remove item from all the maps
bool HashMap::removeItem(string code)
{
    item mainItem;
    auto it = isbnMap.find(code);
    if (it != isbnMap.end())
    {
        mainItem = it->second;
        isbnMap.erase(it);
    }
    else
    {
        // Item not found in isbnMap, return false
        return false;
    }

    auto it2 = titleMap.find(mainItem.getTitle());
    if (it2 != titleMap.end())
    {
        titleMap.erase(it2);
    }
    else
    {
        // Item not found in titleMap, return false
        return false;
    }

    auto it3 = authorMap.find(mainItem.getCreator());
    if (it3 != authorMap.end())
    {
        authorMap.erase(it3);
    }
    else
    {
        // Item not found in authorMap, return false
        return false;
    }

    auto it4 = statusMap.find(mainItem.getStatus());
    if (it4 != statusMap.end())
    {
        // Assuming statusMap value is a list
        it4->second.remove(mainItem);
    }
    else
    {
        // Item not found in statusMap, return false
        return false;
    }

    auto it5 = typeMap.find(mainItem.getCode().length() == 17 ? "Book" : (mainItem.getCode().length() > 17 ? "DVD" : "CD"));
    if (it5 != typeMap.end())
    {
        it5->second.remove(mainItem);
    }
    else
    {
        return false;
    }

    return true;
}
//Method to set status in all the maps
void HashMap::setStatus(string code, bool boo)
{
    item mainItem;
    auto it = isbnMap.find(code);
    if (it != isbnMap.end())
    {
        mainItem = it->second;
        it->second.setStatus(boo);
    }

    auto it2 = titleMap.find(mainItem.getTitle());
    if (it2 != titleMap.end())
    {
        it2->second.setStatus(boo);
    }
    auto it3 = authorMap.find(mainItem.getCreator());
    if (it3 != authorMap.end())
    {
        it3->second.setStatus(boo);
    }
    auto it4 = statusMap.find(mainItem.getStatus());
    if (it4 != statusMap.end())
    {
        for (auto &item : it4->second)
        {
            if (item.getCode() == mainItem.getCode())
            {
                item.setStatus(boo);
                break;
            }
        }
        it4->second.remove(mainItem);
        statusMap[boo].push_back(mainItem);
    }
    auto it5 = typeMap.find(mainItem.getCode().length() == 17 ? "Book" : (mainItem.getCode().length() > 17 ? "DVD" : "CD"));
    if (it5 != typeMap.end())
    {
        for (auto& item : it5->second)
        {
            if (item.getCode() == mainItem.getCode())
            {
                item.setStatus(boo);
                break;
            }
        }
    }
}
//Method to set reservation by user id in all the maps
void HashMap::setReservedByUser(string code, int userID){
    item mainItem;
    auto it = isbnMap.find(code);
    if (it != isbnMap.end())
    {
        mainItem = it->second;
        it->second.setReservedByUser(userID);
    }

    auto it2 = titleMap.find(mainItem.getTitle());
    if (it2 != titleMap.end())
    {
        it2->second.setReservedByUser(userID);
    }
    auto it3 = authorMap.find(mainItem.getCreator());
    if (it3 != authorMap.end())
    {
        it3->second.setReservedByUser(userID);
    }
    auto it4 = statusMap.find(mainItem.getStatus());
    if (it4 != statusMap.end())
    {
        for (auto &item : it4->second)
        {
            if (item.getCode() == mainItem.getCode())
            {
                item.setReservedByUser(userID);
                break;
            }
        }
    }
    auto it5 = typeMap.find(mainItem.getCode().length() == 17 ? "Book" : (mainItem.getCode().length() > 17 ? "DVD" : "CD"));
    if (it5 != typeMap.end())
    {
        for (auto& item : it5->second)
        {
            if (item.getCode() == mainItem.getCode())
            {
                item.setReservedByUser(userID);
                break;
            }
        }
    }
}

bool HashMap::removeUser(int ID)
{
    int index = ID - 100;
    auto it = userMap.find(index);
    if (it != userMap.end())
    {
        userMap.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}

bool HashMap::searchUser(int ID)
{
    int index = ID - 100;
    auto it = userMap.find(index);
    if (it != userMap.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

user *HashMap::searchUser2(int ID)
{
    int index = ID - 100;
    auto it = userMap.find(index);
    if (it != userMap.end())
    {
        return &(it->second);
    }
    else
    {
        return nullptr;
    }
}