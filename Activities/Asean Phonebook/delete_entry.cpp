#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "StringUtils.h"

using namespace std;

void deletePhonebookEntry(const string& filename) {
    string studentNumber;
    cout << "Enter student number: ";
    getline(cin, studentNumber); // Get full line input from user

    // Trim the input
    studentNumber = trim(studentNumber);

    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<string> entries;
    string line;
    bool entryFound = false;

    // Read all lines from the file
    while (getline(inFile, line)) {
        stringstream ss(line);
        string currentStudentNumber;
        getline(ss, currentStudentNumber, ','); // Extract student number

        // Trim the student number from the file for comparison
        currentStudentNumber = trim(currentStudentNumber);

        // Check if this is the student number to delete
        if (currentStudentNumber == studentNumber) {
            entryFound = true;

            // Confirm deletion
            char confirmation;
            cout << "Are you sure you want to delete it [Y/N]? ";
            cin >> confirmation;

            if (toupper(confirmation) == 'Y') {
                cout << "Deletion successful" << endl;
                continue; // Skip adding this line to the updated list
            } else {
                cout << "Deletion did not proceed" << endl;
            }
        }

        // If it's not the entry to delete, add it back to the list
        entries.push_back(line);
    }

    inFile.close();

    // If the student number was not found
    if (!entryFound) {
        cout << "Student number not found in the phonebook." << endl;
        return;
    }

    // Write updated entries back to the file
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (const auto& entry : entries) {
        outFile << entry << endl;
    }

    outFile.close();
}