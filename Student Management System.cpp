#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <sstream>

using namespace std;

struct Student
{
    string name;
    int rollNumber;
    double marks;
};

vector<Student> records;
vector<string> actionLog;

void logAction(const string &action)
{
    actionLog.push_back(action);
}

void viewRecords()
{
    cout << "\nSTUDENT RECORDS\n";
    if (records.empty())
    {
        cout << "No records found.\n";
        return;
    }
    for (const auto &s : records)
    {
        cout << "Roll No: " << s.rollNumber
             << ", Name: " << s.name
             << ", Marks: " << s.marks << "\n";
    }
}

void addRecord()
{
    Student newStudent;
    cout << "\nADD NEW STUDENT RECORD\n";
    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStudent.name);
    cout << "Enter Roll Number: ";
    while (!(cin >> newStudent.rollNumber))
    {
        cout << "Invalid input. Enter Roll Number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter Marks: ";
    while (!(cin >> newStudent.marks))
    {
        cout << "Invalid input. Enter Marks: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    records.push_back(newStudent);
    cout << "Record added successfully.\n";
    logAction("Added student " + newStudent.name + " (Roll No: " + to_string(newStudent.rollNumber) + ")");
}

void updateRecord()
{
    int roll;
    cout << "\nUPDATE STUDENT RECORD\n";
    cout << "Enter Roll Number of student to update: ";
    if (!(cin >> roll))
    {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = find_if(records.begin(), records.end(), [roll](const Student &s)
                      { return s.rollNumber == roll; });

    if (it != records.end())
    {
        cout << "Found: " << it->name << ". Enter new Marks: ";
        double newMarks;
        if (!(cin >> newMarks))
        {
            cout << "Invalid marks input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        it->marks = newMarks;
        cout << "Record updated successfully.\n";
        logAction("Updated marks for " + it->name + " (Roll No: " + to_string(it->rollNumber) + ")");
    }
    else
    {
        cout << "Student with Roll Number " << roll << " not found.\n";
    }
}

void deleteRecord()
{
    int roll;
    cout << "\nDELETE STUDENT RECORD\n";
    cout << "Enter Roll Number of student to delete: ";
    if (!(cin >> roll))
    {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = find_if(records.begin(), records.end(), [roll](const Student &s)
                      { return s.rollNumber == roll; });

    if (it != records.end())
    {
        string deletedName = it->name;
        records.erase(it);
        cout << "Record for " << deletedName << " deleted successfully.\n";
        logAction("Deleted student " + deletedName + " (Roll No: " + to_string(roll) + ")");
    }
    else
    {
        cout << "Student with Roll Number " << roll << " not found.\n";
    }
}

void searchRecord()
{
    int roll;
    cout << "\nSEARCH STUDENT BY ROLL NUMBER\n";
    cout << "Enter Roll Number to search: ";
    if (!(cin >> roll))
    {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = find_if(records.begin(), records.end(), [roll](const Student &s)
                      { return s.rollNumber == roll; });

    if (it != records.end())
    {
        cout << "\n--- Student Found ---\n";
        cout << "Name: " << it->name << "\n";
        cout << "Roll No: " << it->rollNumber << "\n";
        cout << "Marks: " << it->marks << "\n";
    }
    else
    {
        cout << "Student with Roll Number " << roll << " not found.\n";
    }
}

void quickFind()
{
    searchRecord();
}

void arrangeStudents()
{
    cout << "\nARRANGE STUDENTS\n";
    cout << "Arrange by:\n";
    cout << "1. Name (A-Z)\n";
    cout << "2. Roll Number (Ascending)\n";
    cout << "3. Marks (Descending)\n";
    cout << "Enter choice: ";

    int choice;
    if (!(cin >> choice))
    {
        cout << "Invalid choice.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    switch (choice)
    {
    case 1:
        sort(records.begin(), records.end(), [](const Student &a, const Student &b)
             { return a.name < b.name; });
        cout << "Records arranged by Name.\n";
        break;
    case 2:
        sort(records.begin(), records.end(), [](const Student &a, const Student &b)
             { return a.rollNumber < b.rollNumber; });
        cout << "Records arranged by Roll Number.\n";
        break;
    case 3:
        sort(records.begin(), records.end(), [](const Student &a, const Student &b)
             { return a.marks > b.marks; });
        cout << "Records arranged by Marks (Highest first).\n";
        break;
    default:
        cout << "Invalid choice.\n";
        return;
    }
    viewRecords();
}

void seeRecentActions()
{
    cout << "\nRECENT ACTIONS LOG\n";
    if (actionLog.empty())
    {
        cout << "Action log is empty.\n";
        return;
    }
    for (int i = actionLog.size() - 1; i >= 0 && i >= (int)actionLog.size() - 5; --i)
    {
        cout << actionLog[i] << "\n";
    }
    if (actionLog.size() > 5)
    {
        cout << "... (Showing last 5 actions)\n";
    }
}

void handleStudentRequests()
{
    string request;
    cout << "\nSTUDENT REQUESTS SYSTEM\n";
    cout << "Enter your request (e.g., 'Need transcript', 'Change course'):\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, request);
    cout << "Request submitted: '" << request << "'.\n";
    cout << "The system will process this request shortly.\n";
    logAction("Submitted student request: " + (request.length() > 20 ? request.substr(0, 20) + "..." : request));
}

void displayMenu()
{
    cout << "\n--- STUDENT RECORD MANAGEMENT SYSTEM ---\n";
    cout << "1. Add New Student Record\n";
    cout << "2. Update Student Record (by Roll No)\n";
    cout << "3. Delete Student Record (by Roll No)\n";
    cout << "4. View All Student Records\n";
    cout << "5. Search Student by Roll Number (Quick Find)\n";
    cout << "6. Arrange/Sort Student Records\n";
    cout << "7. See Recent Actions\n";
    cout << "8. Handle Student Requests\n";
    cout << "9. Exit System\n";
    cout << "Enter your choice: ";
}

void runSystem()
{
    int choice;
    do
    {
        displayMenu();
        if (!(cin >> choice))
        {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            updateRecord();
            break;
        case 3:
            deleteRecord();
            break;
        case 4:
            viewRecords();
            break;
        case 5:
            quickFind();
            break;
        case 6:
            arrangeStudents();
            break;
        case 7:
            seeRecentActions();
            break;
        case 8:
            handleStudentRequests();
            break;
        case 9:
            cout << "\nExiting Student Management System. Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    } while (choice != 9);
}

int main()
{
    runSystem();
    return 0;
}