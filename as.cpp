#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

bool isPhoneNumberValid(const string& phoneNumber) {
    return phoneNumber.size() == 10 && phoneNumber.find_first_not_of("0123456789") == string::npos;
}

bool isValidName(const string& name) {
    return name.find_first_of("0123456789") == string::npos;
}

int findTouristIndex(const vector<string>& phoneNumbers, const string& phoneNumber) {
    auto iter = find(phoneNumbers.begin(), phoneNumbers.end(), phoneNumber);
    if (iter != phoneNumbers.end()) {
        return distance(phoneNumbers.begin(), iter);
    }
    return -1;  
}

void addTourist(vector<string>& names, vector<int>& ages, vector<string>& genders,
                vector<string>& travelDescriptions, vector<string>& modesOfTravel,
                vector<string>& phoneNumbers) {
    string name;
    int age;
    string gender;
    string travelDescription;
    string modeOfTravel;
    string phoneNumber;

    cout << "Enter phone number (10 digits): ";
    do {
        getline(cin >> ws, phoneNumber);
        if (!isPhoneNumberValid(phoneNumber)) {
            cout << "Invalid phone number. Please enter exactly 10 digits: ";
        } else {
            int existingIndex = findTouristIndex(phoneNumbers, phoneNumber);
            if (existingIndex != -1) {
                cout << "Phone number already exists. Do you want to enter a new one? (Y/N): ";
                char choice;
                cin >> choice;
                cin.ignore();
                if (choice == 'Y' || choice == 'y') {
    
                    cout << "Enter new phone number (10 digits): ";
                    getline(cin >> ws, phoneNumber);
                    if (!isPhoneNumberValid(phoneNumber)) {
                        cout << "!!!!Invalid phone number!!!!! Please enter exactly 10 digits: ";
                        continue;  
                    } else {
                        existingIndex = findTouristIndex(phoneNumbers, phoneNumber);
                        if (existingIndex != -1) {
                            cout << "New phone number already exists. Please enter a unique phone number." << endl;
                            continue;  
                        }
                    }
                } else {
                    return;  
                }
            }
        }
    } while (!isPhoneNumberValid(phoneNumber));
    cout << "Enter name: ";
    getline(cin >> ws, name);

    while (!isValidName(name)) {
        cout << "Invalid name. Please enter a name without numbers: ";
        getline(cin >> ws, name);
    }
    names.push_back(name);

    cout << "Enter age: ";
    while (true) {
        if (!(cin >> age) || age < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a non-negative valid age: ";
        } else {
            break;
        }
    }
    ages.push_back(age);

    cout << "Select gender (enter 'M' for Male, 'F' for Female): ";
    char genderChoice;
    while (true) {
        cin >> genderChoice;
        if (genderChoice == 'M' || genderChoice == 'm') {
            gender = "Male";
            break;
        } else if (genderChoice == 'F' || genderChoice == 'f') {
            gender = "Female";
            break;
        } else {
            cout << "Invalid choice. Please enter 'M' for Male or 'F' for Female: ";
        }
    }
    genders.push_back(gender);

    cout << "Enter travel description: ";
    getline(cin >> ws, travelDescription);
    travelDescriptions.push_back(travelDescription);

    cout << "Select mode of travel (enter 'A' for Airplane, 'T' for Train, 'C' for Car): ";
    char travelChoice;
    while (true) {
        cin >> travelChoice;
        if (travelChoice == 'A' || travelChoice == 'a') {
            modeOfTravel = "Airplane";
            break;
        } else if (travelChoice == 'T' || travelChoice == 't') {
            modeOfTravel = "Train";
            break;
        } else if (travelChoice == 'C' || travelChoice == 'c') {
            modeOfTravel = "Car";
            break;
        } else {
            cout << "Invalid choice. Please enter 'A' for Airplane, 'T' for Train, or 'C' for Car: ";
        }
    }
    modesOfTravel.push_back(modeOfTravel);

    // Add the new phone number
    phoneNumbers.push_back(phoneNumber);

    cout << "Tourist information added successfully!" << endl;
}

void deleteTourist(vector<string>& names, vector<string>& phoneNumbers) {
    string name;
    cout << "Enter name of tourist to delete: ";
    getline(cin >> ws, name);

    bool found = false;
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            names.erase(names.begin() + i);
            phoneNumbers.erase(phoneNumbers.begin() + i);
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Tourist information deleted successfully!" << endl;
    } else {
        cout << "Tourist not found!" << endl;
    }
}

void viewTourist(const vector<string>& names, const vector<int>& ages, const vector<string>& genders,
                 const vector<string>& travelDescriptions, const vector<string>& modesOfTravel,
                 const vector<string>& phoneNumbers) {
    string name;
    cout << "Enter name of tourist to view: ";
    getline(cin >> ws, name);

    bool found = false;
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            cout << "Name: " << names[i] << endl;
            cout << "Age: " << ages[i] << endl;
            cout << "Gender: " << genders[i] << endl;
            cout << "Travel Description: " << travelDescriptions[i] << endl;
            cout << "Mode of Travel: " << modesOfTravel[i] << endl;
            cout << "Phone Number: " << phoneNumbers[i] << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Tourist not found!" << endl;
    }
}

int main() {
    vector<string> names;
    vector<int> ages;
    vector<string> genders;
    vector<string> travelDescriptions;
    vector<string> modesOfTravel;
    vector<string> phoneNumbers;

    int choice;
    do {
        cout << "Tourist Information System" << endl;
        cout << "1. Add Tourist" << endl;
        cout << "2. Remove Tourist" << endl;
        cout << "3. View Tourist" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }

        switch (choice) {
            case 1:
                addTourist(names, ages, genders, travelDescriptions, modesOfTravel, phoneNumbers);
                break;
            case 2:
                deleteTourist(names, phoneNumbers);
                break;
            case 3:
                viewTourist(names, ages, genders, travelDescriptions, modesOfTravel, phoneNumbers);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 4);

    return 0;
}