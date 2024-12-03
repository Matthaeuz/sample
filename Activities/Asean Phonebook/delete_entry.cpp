#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Helper function to trim leading and trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}


void deletePhonebookEntry(const string& filename) {
    string studentNumber;
    cout << "Enter student number: ";
    getline(cin, studentNumber); // Get full line input from user

    // Debugging: Raw input
    cout << "Raw student number entered: '" << studentNumber << "'" << endl;

    // Trim the input
    studentNumber = trim(studentNumber);

    // Debugging: Trimmed input
    cout << "Trimmed student number to search: '" << studentNumber << "'" << endl;

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

        // Debugging: Extracted student number
        cout << "Extracted student number: '" << currentStudentNumber << "'" << endl;

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
        } else {
            // Debugging: Explain why the values don't match
            cout << "No match: '" << currentStudentNumber << "' != '" << studentNumber << "'" << endl;
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
