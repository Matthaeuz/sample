#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "StringUtils.h"

using namespace std;

// ASEAN country codes for validation
unordered_map<string, string> ASEAN_COUNTRIES = {
    {"60", "Federation of Malaysia"},
    {"62", "Republic of Indonesia"},
    {"63", "Republic of Philippines"},
    {"65", "Republic of Singapore"},
    {"66", "Kingdom of Thailand"}
};

// Function to store an entry in the ASEAN Phonebook
void storeToPhonebook() {
    ofstream file("asean_phonebook.txt", ios::app); // Open file in append mode
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string studentNumber, surname, firstName, occupation, gender, countryCode, areaCode, number;
    char anotherEntry;

    do {
        // Get user input
        cout << "Enter student number: ";
        getline(cin, studentNumber);
        cout << "Enter surname: ";
        getline(cin, surname);
        cout << "Enter first name: ";
        getline(cin, firstName);
        cout << "Enter occupation: ";
        getline(cin, occupation);
        cout << "Enter gender (M for male, F for female): ";
        getline(cin, gender);
        cout << "Enter country code: ";
        getline(cin, countryCode);

        // Trim inputs
        studentNumber = trim(studentNumber);
        surname = trim(surname);
        firstName = trim(firstName);
        occupation = trim(occupation);
        gender = trim(gender);
        countryCode = trim(countryCode);

        // Validate country code in a separate loop
        while (true) {
            cout << "Enter country code: ";
            getline(cin, countryCode);
            countryCode = trim(countryCode);

            if (ASEAN_COUNTRIES.find(countryCode) != ASEAN_COUNTRIES.end()) {
                break; // Valid country code, exit the loop
            }

            cout << "Invalid country code! Must be one of: ";
            for (const auto& country : ASEAN_COUNTRIES) {
                cout << country.first << " ";
            }
            cout << endl;
        }

        cout << "Enter area code: ";
        getline(cin, areaCode);
        cout << "Enter number: ";
        getline(cin, number);

        // Trim remaining inputs
        areaCode = trim(areaCode);
        number = trim(number);

        // Write data to file
        file << studentNumber << "," << surname << "," << firstName << ","
             << occupation << "," << gender << "," << countryCode << ","
             << areaCode << "," << number << endl;

        cout << "Entry added successfully." << endl;

        // Ask if the user wants to add another entry
        cout << "Do you want to enter another entry [Y/N]? ";
        cin >> anotherEntry;
        cin.ignore(); // Clear the newline character from the input buffer

    } while (toupper(anotherEntry) == 'Y');

    file.close();
    cout << "All entries have been saved to ASEAN Phonebook." << endl;
}
