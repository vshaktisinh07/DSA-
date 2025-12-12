#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <sstream>
#include <map>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string category;
    bool isIssued;
    int issuedToMemberId;
};

struct Member {
    int id;
    string name;
};

vector<Book> books;
vector<Member> members;
vector<string> actionLog;
map<int, vector<int>> waitingLists;
map<string, vector<string>> categoryConnections;

void logAction(const string& action) {
    actionLog.push_back(action);
}

void initializeCategoryMap() {
    categoryConnections["Fiction"] = {"Mystery", "Fantasy"};
    categoryConnections["Science"] = {"Technology", "Mathematics"};
    categoryConnections["History"] = {"Biography", "Geography"};
    categoryConnections["Mystery"] = {"Fiction"};
    categoryConnections["Fantasy"] = {"Fiction"};
    categoryConnections["Technology"] = {"Science"};
    categoryConnections["Mathematics"] = {"Science"};
    categoryConnections["Biography"] = {"History"};
    categoryConnections["Geography"] = {"History"};
}

void displayCategoryMap() {
    cout << "\nBOOK CATEGORY CONNECTIONS MAP\n";
    for (const auto& pair : categoryConnections) {
        cout << pair.first << " is related to: ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            cout << pair.second[i] << (i < pair.second.size() - 1 ? ", " : "");
        }
        cout << "\n";
    }
}

void viewAllBooks() {
    cout << "\nCURRENT BOOK INVENTORY\n";
    if (books.empty()) {
        cout << "No books in inventory.\n";
        return;
    }
    for (const auto& b : books) {
        cout << "ID: " << b.id
             << ", Title: " << b.title
             << ", Author: " << b.author
             << ", Category: " << b.category
             << ", Status: " << (b.isIssued ? "Issued to Member " + to_string(b.issuedToMemberId) : "Available") << "\n";
    }
}

void addBook() {
    Book newBook;
    cout << "\nADD NEW BOOK\n";
    cout << "Enter Book ID (integer): ";
    if (!(cin >> newBook.id)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Title: ";
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter Category: ";
    getline(cin, newBook.category);

    newBook.isIssued = false;
    newBook.issuedToMemberId = 0;

    books.push_back(newBook);
    cout << "Book added successfully.\n";
    logAction("Added book: " + newBook.title + " (ID: " + to_string(newBook.id) + ")");
}

void updateBook() {
    int id;
    cout << "\nUPDATE BOOK INFORMATION\n";
    cout << "Enter Book ID to update: ";
    if (!(cin >> id)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = find_if(books.begin(), books.end(), [id](const Book& b){
        return b.id == id;
    });

    if (it != books.end()) {
        cout << "Found: " << it->title << ". Enter new Category: ";
        string newCat;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newCat);
        it->category = newCat;
        cout << "Book updated successfully.\n";
        logAction("Updated category for book: " + it->title + " (ID: " + to_string(it->id) + ")");
    } else {
        cout << "Book with ID " << id << " not found.\n";
    }
}

void removeBook() {
    int id;
    cout << "\nREMOVE BOOK\n";
    cout << "Enter Book ID to remove: ";
    if (!(cin >> id)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = find_if(books.begin(), books.end(), [id](const Book& b){
        return b.id == id;
    });

    if (it != books.end()) {
        string removedTitle = it->title;
        books.erase(it);
        waitingLists.erase(id);
        cout << "Book '" << removedTitle << "' removed successfully.\n";
        logAction("Removed book: " + removedTitle + " (ID: " + to_string(id) + ")");
    } else {
        cout << "Book with ID " << id << " not found.\n";
    }
}

void addMember() {
    Member newMember;
    cout << "\nADD NEW MEMBER\n";
    cout << "Enter Member ID (integer): ";
    if (!(cin >> newMember.id)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Member Name: ";
    getline(cin, newMember.name);

    members.push_back(newMember);
    cout << "Member added successfully.\n";
    logAction("Added member: " + newMember.name + " (ID: " + to_string(newMember.id) + ")");
}

void issueBook() {
    int bookId, memberId;
    cout << "\nISSUE BOOK\n";
    cout << "Enter Book ID: ";
    if (!(cin >> bookId)) {
        cout << "Invalid book ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cout << "Enter Member ID: ";
    if (!(cin >> memberId)) {
        cout << "Invalid member ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto bookIt = find_if(books.begin(), books.end(), [bookId](const Book& b){
        return b.id == bookId;
    });
    auto memberIt = find_if(members.begin(), members.end(), [memberId](const Member& m){
        return m.id == memberId;
    });

    if (bookIt == books.end()) {
        cout << "Error: Book ID not found.\n";
        return;
    }
    if (memberIt == members.end()) {
        cout << "Error: Member ID not found. Please add the member first.\n";
        return;
    }

    if (!bookIt->isIssued) {
        bookIt->isIssued = true;
        bookIt->issuedToMemberId = memberId;
        cout << "Book '" << bookIt->title << "' issued to " << memberIt->name << ".\n";
        logAction("Issued book " + bookIt->title + " to Member " + to_string(memberId));
    } else {
        cout << "Book is already issued to Member " << bookIt->issuedToMemberId << ".\n";
    }
}

void returnBook() {
    int bookId;
    cout << "\nRETURN BOOK\n";
    cout << "Enter Book ID to return: ";
    if (!(cin >> bookId)) {
        cout << "Invalid book ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto bookIt = find_if(books.begin(), books.end(), [bookId](const Book& b){
        return b.id == bookId;
    });

    if (bookIt == books.end()) {
        cout << "Error: Book ID not found.\n";
        return;
    }

    if (bookIt->isIssued) {
        int oldMemberId = bookIt->issuedToMemberId;
        bookIt->isIssued = false;
        bookIt->issuedToMemberId = 0;
        cout << "Book '" << bookIt->title << "' returned successfully.\n";
        logAction("Returned book " + bookIt->title + " from Member " + to_string(oldMemberId));

        if (!waitingLists[bookId].empty()) {
            int nextMemberId = waitingLists[bookId].front();
            waitingLists[bookId].erase(waitingLists[bookId].begin());
            cout << "Notification: Book is reserved. Next in line (Member ID " << nextMemberId << ") has been notified.\n";
            logAction("Notified Member " + to_string(nextMemberId) + " for reservation of " + bookIt->title);
        }
    } else {
        cout << "Book is not currently issued.\n";
    }
}

void requestBook() {
    int bookId, memberId;
    cout << "\nREQUEST BOOK (WAITING LIST)\n";
    cout << "Enter Book ID to request: ";
    if (!(cin >> bookId)) {
        cout << "Invalid book ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cout << "Enter your Member ID: ";
    if (!(cin >> memberId)) {
        cout << "Invalid member ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto memberIt = find_if(members.begin(), members.end(), [memberId](const Member& m){
        return m.id == memberId;
    });

    if (memberIt == members.end()) {
        cout << "Error: Member ID not found. Cannot place request.\n";
        return;
    }

    auto bookIt = find_if(books.begin(), books.end(), [bookId](const Book& b){
        return b.id == bookId;
    });

    if (bookIt == books.end()) {
        cout << "Error: Book ID not found.\n";
        return;
    }

    if (bookIt->isIssued) {
        auto& list = waitingLists[bookId];
        if (find(list.begin(), list.end(), memberId) == list.end()) {
            list.push_back(memberId);
            cout << "Book '" << bookIt->title << "' is currently issued. You have been added to the waiting list.\n";
            logAction("Member " + to_string(memberId) + " requested book " + bookIt->title);
        } else {
            cout << "You are already on the waiting list for this book.\n";
        }
    } else {
        cout << "Book '" << bookIt->title << "' is available! Please proceed to issue it.\n";
    }
}

void quickSearchBook() {
    int id;
    cout << "\nQUICK SEARCH BY BOOK ID\n";
    cout << "Enter Book ID to search: ";
    if (!(cin >> id)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = find_if(books.begin(), books.end(), [id](const Book& b){
        return b.id == id;
    });

    if (it != books.end()) {
        cout << "\n--- Book Found ---\n";
        cout << "Title: " << it->title << "\n";
        cout << "Author: " << it->author << "\n";
        cout << "Category: " << it->category << "\n";
        cout << "Status: " << (it->isIssued ? "Issued to Member " + to_string(it->issuedToMemberId) : "Available") << "\n";
    } else {
        cout << "Book with ID " << id << " not found.\n";
    }
}

void sortBooks() {
    cout << "\nARRANGE/SORT BOOKS\n";
    cout << "Sort by:\n";
    cout << "1. Title (A-Z)\n";
    cout << "2. Author (A-Z)\n";
    cout << "3. Book ID (Ascending)\n";
    cout << "Enter choice: ";

    int choice;
    if (!(cin >> choice)) {
        cout << "Invalid choice.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    switch (choice) {
        case 1:
            sort(books.begin(), books.end(), [](const Book& a, const Book& b){
                return a.title < b.title;
            });
            cout << "Books arranged by Title.\n";
            break;
        case 2:
            sort(books.begin(), books.end(), [](const Book& a, const Book& b){
                return a.author < b.author;
            });
            cout << "Books arranged by Author.\n";
            break;
        case 3:
            sort(books.begin(), books.end(), [](const Book& a, const Book& b){
                return a.id < b.id;
            });
            cout << "Books arranged by ID.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }
    viewAllBooks();
}

void seeRecentActions() {
    cout << "\nRECENT ACTIONS LOG\n";
    if (actionLog.empty()) {
        cout << "Action log is empty.\n";
        return;
    }
    for (int i = actionLog.size() - 1; i >= 0 && i >= (int)actionLog.size() - 5; --i) {
        cout << actionLog[i] << "\n";
    }
    if (actionLog.size() > 5) {
        cout << "... (Showing last 5 actions)\n";
    }
}

void viewAllDetails() {
    cout << "\n=========================================\n";
    cout << "       FULL LIBRARY MANAGEMENT REPORT      \n";
    cout << "=========================================\n";
    viewAllBooks();
    cout << "\n--- LIBRARY MEMBERS ---\n";
    for (const auto& m : members) {
        cout << "ID: " << m.id << ", Name: " << m.name << "\n";
    }
    cout << "\n--- BOOK WAITING LISTS ---\n";
    bool hasWaiting = false;
    for (const auto& pair : waitingLists) {
        if (!pair.second.empty()) {
            auto bookIt = find_if(books.begin(), books.end(), [id = pair.first](const Book& b){
                return b.id == id;
            });
            string title = (bookIt != books.end()) ? bookIt->title : "Unknown Book";
            cout << title << " (ID " << pair.first << "): ";
            for (int memberId : pair.second) {
                cout << "M" << memberId << " ";
            }
            cout << "\n";
            hasWaiting = true;
        }
    }
    if (!hasWaiting) {
        cout << "No current waiting lists.\n";
    }
    cout << "\n--- RECENT ACTIVITY ---\n";
    seeRecentActions();
    cout << "\n=========================================\n";
}

void bookMenu() {
    int choice;
    do {
        cout << "\n--- BOOK MANAGEMENT ---\n";
        cout << "1. Add New Book\n";
        cout << "2. Update Book Info\n";
        cout << "3. Remove Book\n";
        cout << "4. View All Books\n";
        cout << "5. Quick Search Book (by ID)\n";
        cout << "6. Arrange/Sort Books\n";
        cout << "7. Back to Dashboard\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: updateBook(); break;
            case 3: removeBook(); break;
            case 4: viewAllBooks(); break;
            case 5: quickSearchBook(); break;
            case 6: sortBooks(); break;
            case 7: return;
            default: cout << "\nInvalid choice. Please try again.\n"; break;
        }
    } while (choice != 7);
}

void memberMenu() {
    int choice;
    do {
        cout << "\n--- MEMBERS & TRANSACTIONS ---\n";
        cout << "1. Add New Member\n";
        cout << "2. Issue Book\n";
        cout << "3. Return Book\n";
        cout << "4. Request Book (Waiting List)\n";
        cout << "5. Back to Dashboard\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addMember(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: requestBook(); break;
            case 5: return;
            default: cout << "\nInvalid choice. Please try again.\n"; break;
        }
    } while (choice != 5);
}

void displayDashboard() {
    cout << "\n--- LIBRARY MANAGEMENT SYSTEM DASHBOARD ---\n";
    cout << "1. Book Management Menu\n";
    cout << "2. Members & Transactions Menu\n";
    cout << "3. View Category Map\n";
    cout << "4. See Recent Actions\n";
    cout << "5. Generate Full Library Report\n";
    cout << "6. Exit System\n";
    cout << "Enter your choice: ";
}

void runSystem() {
    initializeCategoryMap();
    int choice;
    do {
        displayDashboard();
        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: bookMenu(); break;
            case 2: memberMenu(); break;
            case 3: displayCategoryMap(); break;
            case 4: seeRecentActions(); break;
            case 5: viewAllDetails(); break;
            case 6: cout << "\nExiting Library Management System. Goodbye!\n"; break;
            default: cout << "\nInvalid choice. Please try again.\n"; break;
        }
    } while (choice != 6);
}

int main() {
    runSystem();
    return 0;
}