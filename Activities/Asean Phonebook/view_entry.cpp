#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "StringUtils.h"

using namespace std;

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != string::npos) {
        string token = str.substr(start, end - start);
        tokens.push_back(trim(token));
        start = end + 1;
    }
    // Add the last token
    tokens.push_back(trim(str.substr(start)));

    return tokens;
}

// Formatter function for output
string formatEntry(const vector<string>& entryFields) {
    return entryFields[1] + ", " + entryFields[2] + ", with student number " +
           entryFields[0] + ", a " + entryFields[3] +
           ". His/her phone number is " + entryFields[7] + ".";
}

// View function
void viewPhonebookEntry(const string& phonebookFile) {
    ifstream file(phonebookFile);
    if (!file.is_open()) {
        cerr << "Error: Unable to open the phonebook file." << endl;
        return;
    }

    int option;
    string searchValue;
    vector<string> matchingEntries;

    cout << "\nSearch Options:" << endl;
    cout << "[1] Search by Surname" << endl;
    cout << "[2] Search by Country Code" << endl;
    cout << "Select an option: ";
    cin >> option;
    cin.ignore(); // Clear the input buffer

    if (option == 1) {
        cout << "Enter Surname: ";
    } else if (option == 2) {
        cout << "Enter Country Code: ";
    } else {
        cout << "Invalid option." << endl;
        return;
    }

    getline(cin, searchValue);

    string line;
    while (getline(file, line)) {
    vector<string> fields = split(line, ',');
    if (fields.size() < 8) continue; // Ensure there are enough fields

    // // Debug: Print the fields to inspect
    // for (const auto& field : fields) {
    //     cout << "[" << field << "] ";
    // }
    // cout << endl;

    string matchField = (option == 1) ? fields[1] : fields[5]; // Surname or Country Code
    if (trim(matchField) == trim(searchValue)) {
        matchingEntries.push_back(line);
    }
}


    file.close();

    if (matchingEntries.empty()) {
        cout << "No matching entries found for \"" << searchValue << "\"." << endl;
    } else {
        cout << "\nMatching Entries:\n" << endl;
        for (const auto& entry : matchingEntries) {
            vector<string> fields = split(entry, ',');
            cout << formatEntry(fields) << endl;
        }
    }
}
