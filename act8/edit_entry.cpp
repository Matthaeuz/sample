#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent an entry in the phonebook
struct PhonebookEntry {
    string studentNumber;
    string surname;
    string firstName;
    string occupation;
    string gender;
    string countryCode;
    string areaCode;
    string number;
};

// Function to load all entries from the phonebook file
vector<PhonebookEntry> loadPhonebook(const string& filename) {
    vector<PhonebookEntry> entries;
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Unable to open the phonebook file!" << endl;
        return entries;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        PhonebookEntry entry;
        getline(ss, entry.studentNumber, ',');
        getline(ss, entry.surname, ',');
        getline(ss, entry.firstName, ',');
        getline(ss, entry.occupation, ',');
        getline(ss, entry.gender, ',');
        getline(ss, entry.countryCode, ',');
        getline(ss, entry.areaCode, ',');
        getline(ss, entry.number, ',');
        entries.push_back(entry);
    }

    file.close();
    return entries;
}

// Function to save all entries back to the phonebook file
void savePhonebook(const string& filename, const vector<PhonebookEntry>& entries) {
    ofstream file(filename, ios::trunc);

    if (!file) {
        cerr << "Error: Unable to open the phonebook file!" << endl;
        return;
    }

    for (const auto& entry : entries) {
        file << entry.studentNumber << "," << entry.surname << "," << entry.firstName << ","
             << entry.occupation << "," << entry.gender << "," << entry.countryCode << ","
             << entry.areaCode << "," << entry.number << endl;
    }

    file.close();
}

// Function to edit a specific entry
void editPhonebookEntry(const string& filename) {
    vector<PhonebookEntry> entries = loadPhonebook(filename);

    if (entries.empty()) {
        cout << "The phonebook is empty or could not be loaded." << endl;
        return;
    }

    // Prompt user for student number
    string studentNumber;
    cout << "Enter student number: ";
    cin >> studentNumber;

    // Search for the entry by student number
    auto it = find_if(entries.begin(), entries.end(), [&](const PhonebookEntry& entry) {
        return entry.studentNumber == studentNumber;
    });

    if (it == entries.end()) {
        cout << "No entry found for student number " << studentNumber << "." << endl;
        return;
    }

    // Display the existing information
    PhonebookEntry& entry = *it;
    cout << "Here is the existing information about " << studentNumber << ":" << endl;
    cout << entry.firstName << " " << entry.surname << " is a " << entry.occupation << ". ";
    cout << (entry.gender == "M" ? "His" : "Her") << " number is "
         << entry.countryCode << "-" << entry.areaCode << "-" << entry.number << endl;

    // Display options for editing
    cout << "Which of the following information do you wish to change?" << endl;
    cout << "[1] Student number" << endl;
    cout << "[2] Surname" << endl;
    cout << "[3] First name" << endl;
    cout << "[4] Occupation" << endl;
    cout << "[5] Gender" << endl;
    cout << "[6] Country code" << endl;
    cout << "[7] Area code" << endl;
    cout << "[8] Phone number" << endl;
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    cin.ignore(); // Clear input buffer

    // Edit the selected field
    string newValue;
    switch (choice) {
        case 1:
            cout << "Enter new student number: ";
            getline(cin, newValue);
            entry.studentNumber = newValue;
            break;
        case 2:
            cout << "Enter new surname: ";
            getline(cin, newValue);
            entry.surname = newValue;
            break;
        case 3:
            cout << "Enter new first name: ";
            getline(cin, newValue);
            entry.firstName = newValue;
            break;
        case 4:
            cout << "Enter new occupation: ";
            getline(cin, newValue);
            entry.occupation = newValue;
            break;
        case 5:
            cout << "Enter new gender (M/F): ";
            getline(cin, newValue);
            entry.gender = newValue;
            break;
        case 6:
            cout << "Enter new country code: ";
            getline(cin, newValue);
            entry.countryCode = newValue;
            break;
        case 7:
            cout << "Enter new area code: ";
            getline(cin, newValue);
            entry.areaCode = newValue;
            break;
        case 8:
            cout << "Enter new phone number: ";
            getline(cin, newValue);
            entry.number = newValue;
            break;
        default:
            cout << "Invalid choice. No changes were made." << endl;
            return;
    }

    // Save the updated phonebook back to the file
    savePhonebook(filename, entries);
    cout << "Entry updated successfully!" << endl;
}
