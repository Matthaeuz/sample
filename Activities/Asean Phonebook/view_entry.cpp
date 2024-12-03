// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <unordered_map>
// #include <vector>
// #include <string>
// #include <set>

// using namespace std;

// // Helper function to trim leading and trailing spaces
// string trim(const string& str) {
//     size_t first = str.find_first_not_of(' ');
//     size_t last = str.find_last_not_of(' ');
//     return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
// }

// // ASEAN country mapping
// unordered_map<string, string> ASEAN_COUNTRIES = {
//     {"60", "Federation of Malaysia"},
//     {"62", "Republic of Indonesia"},
//     {"63", "Republic of Philippines"},
//     {"65", "Republic of Singapore"},
//     {"66", "Kingdom of Thailand"}
// };

// // Function to display and search ASEAN phonebook by country
// void viewPhonebookEntry(const string& filename) {
//     while (true) {
//         cout << "\nSearch by:\n[1] Search by country\n[2] Search by surname\n[3] Go back to main menu\n";
//         cout << "Enter choice: ";
//         int choice;
//         cin >> choice;

//         if (choice == 1) {
//             // Search by country
//             set<string> selectedCountryCodes;

//             cout << "\nFrom which country:\n";
//             int index = 1;
//             for (const auto& country : ASEAN_COUNTRIES) {
//                 cout << "[" << index++ << "] " << country.second << endl;
//             }
//             cout << "[0] No more\n";

//             // Read country selections
//             while (true) {
//                 cout << "Enter choice " << index << ": ";
//                 int countryChoice;
//                 cin >> countryChoice;

//                 if (countryChoice == 0) break; // No more choices

//                 // Validate choice
//                 if (countryChoice > 0 && countryChoice <= ASEAN_COUNTRIES.size()) {
//                     auto it = next(ASEAN_COUNTRIES.begin(), countryChoice - 1);
//                     selectedCountryCodes.insert(it->first);
//                 } else {
//                     cout << "Invalid choice. Try again.\n";
//                 }
//             }

//             // Display selected country codes
//             cout << "Selected country codes: ";
//             for (const auto& code : selectedCountryCodes) {
//                 cout << code << " ";
//             }
//             cout << "\n";

//             // Search phonebook for matching entries
//             ifstream inFile(filename);
//             if (!inFile) {
//                 cerr << "Error opening file!\n";
//                 return;
//             }

//             cout << "Entries matching the selected countries:\n";
//             string line;
//             bool found = false;
//             while (getline(inFile, line)) {
//                 stringstream ss(line);
//                 string studentNumber, surname, givenName, profession, gender, countryCode, otherFields;

//                 getline(ss, studentNumber, ',');
//                 getline(ss, surname, ',');
//                 getline(ss, givenName, ',');
//                 getline(ss, profession, ',');
//                 getline(ss, gender, ',');
//                 getline(ss, countryCode, ',');

//                 countryCode = trim(countryCode);

//                 // Check if the country code matches any selected
//                 if (selectedCountryCodes.find(countryCode) != selectedCountryCodes.end()) {
//                     cout << line << endl;
//                     found = true;
//                 }
//             }

//             if (!found) {
//                 cout << "No entries found for the selected countries.\n";
//             }
//             inFile.close();
//         } else if (choice == 2) {
//             // Placeholder for searching by surname (can be implemented similarly)
//             cout << "Search by surname not yet implemented.\n";
//         } else if (choice == 3) {
//             // Go back to main menu
//             break;
//         } else {
//             cout << "Invalid choice. Try again.\n";
//         }
//     }
// }
