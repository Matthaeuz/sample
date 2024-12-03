#include <iostream>
#include <string>
#include "edit_entry.cpp"
#include "add_entry.cpp"
#include "delete_entry.cpp"
#include "view_entry.cpp"

using namespace std;

int main() {
    const string phonebookFile = "asean_phonebook.txt"; // Define the shared file path
    int option;

    do {
        cout << "\nASEAN Phonebook Menu:" << endl;
        cout << "[1] Store to ASEAN phonebook" << endl;
        cout << "[2] Edit entry in ASEAN phonebook" << endl;
        cout << "[3] Delete entry from ASEAN phonebook" << endl;
        cout << "[4] View/search ASEAN phonebook" << endl;
        cout << "[5] Exit" << endl;
        cout << "Select an option: ";
        cin >> option;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (option) {
            case 1:
                storeToPhonebook();
                break;
            case 2:
                editPhonebookEntry(phonebookFile);
                break;
            case 3:
                deletePhonebookEntry(phonebookFile);
                break;
            // case 4:
            //     viewPhonebookEntry(phonebookFile);
            //     break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 5);

    return 0;
}
