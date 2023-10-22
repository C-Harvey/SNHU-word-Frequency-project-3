#include <iostream>
#include <fstream>
#include <map>
using namespace std;

// Check the file to see how often a item is listed.
void getSpecificItemFrequency(const map<string, int>& itemFrequency) {
    string item;
    cout << "Enter the name of the item: ";
    cin >> item;
    if (itemFrequency.count(item) > 0) {
        cout << "The frequency of " << item << ": " << itemFrequency.at(item) << endl;
    }
    else {
        cout << "This item is not listed, ensure that you are using the correct case-sensitive word." << endl;
    }
}

// Main menu display and logic
int displayMenu() {
    int choice;
    cout << "\nChoices:" << endl;
    cout << "1. Check how many times an item is bought." << endl;
    cout << "2. List all items and how frequently they are bought." << endl;
    cout << "3. List an item histogram." << endl;
    cout << "4. Quit" << endl;
    cout << "Please enter the numer representing your choice: ";
    cin >> choice;
    return choice;
}


// List all items followed by a "*" for each time they appear in the list.
void displayHistogram(const map<string, int>& itemFrequency) {
    cout << "Frequency histogram:" << endl;
    for (const auto& entry : itemFrequency) {
        cout << entry.first << " ";
        for (int i = 0; i < entry.second; i++) {
            cout << "*";
        }
        cout << endl;
    }
}

// List all items followed by a number of times they are in the list.
void listAllItems(const map<string, int>& itemFrequency) {
    cout << "List all items and how frequently they are bought:" << endl;
    for (const auto& entry : itemFrequency) {
        cout << entry.first << " " << entry.second << endl;
    }
}

// Read through the file and update the frequency of the name on each line.
void readInputFile(map<string, int>& itemFrequency) {
    ifstream inputFile("CS210_Project_Three_Input_File.txt");
    if (inputFile.is_open()) {
        string item;
        while (inputFile >> item) {
            itemFrequency[item]++;
        }
        inputFile.close();
    }
    else {
        cout << "Error: The file is missing or the name is incorrect." << endl;
    }
}

int main() {
    map<string, int> itemFrequency;

    // Read the input file and populate the item frequency map
    readInputFile(itemFrequency);

    int choice;
    do {
        choice = displayMenu();
        switch (choice) {
        case 1:
            getSpecificItemFrequency(itemFrequency);
            break;
        case 2:
            listAllItems(itemFrequency);
            break;
        case 3:
            displayHistogram(itemFrequency);
            break;
        case 4:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option (1-4)." << endl;
        }
    } while (choice != 4);

    // Write the frequency to a file.
    ofstream backupFile("frequency.dat");
    for (const auto& entry : itemFrequency) {
        backupFile << entry.first << " " << entry.second << endl;
    }
    backupFile.close();

    return 0;
}
