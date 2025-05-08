#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<cstdlib>


using namespace std;

// Structure to hold patient information
struct Patient {
    int id;
    string fullName;
    int age;
    string gender;
    string address;
    string contactNumber;
    string emergencyContact;
    string status; // "In Treatment" or "Completed"
    string date; // history
    string room_number;
    string treatment_type;
};

// Service charges for departments (General Medicine, Surgery, Orthopedics, Pediatrics)
int serviceCharges[] = {200, 500, 400, 150};

// Global filename variable for selected department
string filename;

// Function prototypes
void clearScreen();
void selectDepartment();
void registerPatient();
void viewAllPatients();
void searchPatientByID();
void editPatientInfo();
void migratePatient();
void billingMenu();
int getNextID();
string assign_room();
void displayMenu();
string appointmentDate(); // Gets the date for appointment

// for clearing screen
void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
// Function to get the preferred date
string appointmentDate() {
    int day, month, year;
    string date;
    bool validDate = false;
    while (!validDate) {
        cout << "Enter preferred date (day month year): ";
        cin >> day >> month >> year;
        // Simple date validation (no leap year check)
        if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1000) {
            cout << "Invalid date. Please try again.\n";
        } else {
            validDate = true;
            date = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
        }
    }
    return date;
}

// Select department inside each function
void selectDepartment() {
    int departmentChoice = 0;
    bool validChoice = false;

    while (!validChoice) {
        cout << "Select Department:\n";
        cout << "1. General Medicine\n";
        cout << "2. Surgery\n";
        cout << "3. Orthopedics\n";
        cout << "4. Pediatrics\n";
        cout << "Enter your choice (1-4): ";
        cin >> departmentChoice;
        clearScreen();

        switch (departmentChoice) {
            case 1:
                filename = "general_medicine.csv";
                validChoice = true;
                break;
            case 2:
                filename = "surgery.csv";
                validChoice = true;
                break;
            case 3:
                filename = "orthopedics.csv";
                validChoice = true;
                break;
            case 4:
                filename = "pediatrics.csv";
                validChoice = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n\n";
        }
    }
}


// Registers a new patient
void registerPatient() {
    selectDepartment();  // Ask for department before registration
    clearScreen();
    Patient p;
    p.id = getNextID();
    int room;

    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, p.fullName);
    cout << "Enter age: ";
    cin >> p.age;
    cin.ignore();
    cout << "Enter gender: ";
    getline(cin, p.gender);
    cout << "Enter address: ";
    getline(cin, p.address);
    cout << "Enter contact number: ";
    getline(cin, p.contactNumber);
    cout << "Enter emergency contact: ";
    getline(cin, p.emergencyContact);
    cout<<"ENTER TREATMENT TYPE:"<<endl;
    getline(cin, p.treatment_type);
    cout <<"IF ROOM IS NEEDED ENTER 1:"<<endl;
    cin>>room;
    if(room==1){
         p.room_number= assign_room();}
         else {p.room_number=" NO ROOM RESERVED";}
    p.status = "In Treatment"; // Default status
    p.date = appointmentDate();


    ofstream file(filename, ios::app); // Append to file
    if (file.is_open()) {
        file << p.id << "," << p.fullName << "," << p.age << "," << p.gender << ","
             << p.address << "," << p.contactNumber << "," << p.emergencyContact << ","
             << p.status << "," << p.date <<"," << p.treatment_type <<"," <<p.room_number<< "\n";

        file.close();
        clearScreen();
        cout << "Patient registered successfully with ID: " << p.id << endl;
    } else {
        cout << "Error opening file.\n";
    }
}
string assign_room(){
    int count;
    if (filename=="general_medicine.csv")
    count = 0;
    else if ( filename == "surgery.csv")
         count = 99;
    else if (filename == "orthopedics.csv")
        count = 199;
    else if(filename=="pediatrics.csv")
        count=299;
ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string field, lastField;

        while (getline(ss, field, ',')) {
            lastField = field;
        }
        if (lastField == " NO ROOM RESERVED")
            continue;

        count++;

         if (filename == "general_medicine.csv" && count == 100) {
            cout << "all rooms are reserved" << endl;
                      return " NO ROOM RESERVED";
        }
        if (filename == "surgery.csv" && count == 200) {
            cout << "all rooms are reserved" << endl;
            return " NO ROOM RESERVED";
        }
        if (filename == "orthopedics.csv" && count == 300) {
            cout << "all rooms are reserved" << endl;
                        return " NO ROOM RESERVED";
        }
        if (filename == "pediatrics.csv" && count == 400) {
            cout << "all rooms are reserved" << endl;
                       return " NO ROOM RESERVED";
        }

    }
    file.close();
      return to_string(count + 1);

}

// Generates the next patient ID by counting existing entries
int getNextID() {
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line)) {
        count++;
    }
    file.close();
    return count + 1;
}

// Displays all patients in the department
void viewAllPatients() {
    selectDepartment();  // Ask for department before viewing patients

    ifstream file(filename);
    string line;
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    cout << "\n--- List of Patients ---\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            cout << item << " | ";
        }
        cout << endl;
    }
    file.close();
}

// Searches for a patient by their ID
void searchPatientByID() {
    selectDepartment();  // Ask for department before searching

    string id;
    cout << "Enter patient ID to search: ";
    cin.ignore();
    getline(cin, id);

    ifstream file(filename);
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        if (field == id) {
            found = true;
            cout << "\n--- Patient Found ---\n";
            cout << "ID: " << field << endl;

            string labels[] = {"Full Name", "Age", "GENDER", "Address", "Contact Number",
                "EMERGENCY CONTACT", "Status", "Appointment DATE","treatment_type","ROOM_NUMBER"};
                for (int i = 0; i < 10; i++) {
                    getline(ss, field, ',');
                    if (field.empty()) {
                        field = "N/A";

                    }
                    cout << labels[i] << ": " << field << endl;
                }
                if (filename == "general_medicine.csv") {
            cout << "department:GENERAL_MEDICINE" << endl;

        }
        if (filename == "surgery.csv" ) {
            cout << "department:SURGERY" << endl;

        }
        if (filename == "orthopedics.csv" ) {
            cout << "department:ORTHOPEDICS" << endl;

        }
        if (filename == "pediatrics.csv") {
            cout << "department:PEDIATRICS" << endl;

        }
            break;
        }
    }
    if (found == false) {
        cout << "Patient with ID " << id << " not found.\n";
    }
    file.close();
}

// Edits patient information by ID
void editPatientInfo() {
    selectDepartment();
    string id, output, line, newValue;
    int choice;
    bool found = false;

    cin.ignore();
    cout << "Enter patient ID to edit: ";
    getline (cin, id);

    cout << "Enter choice of attribute to edit:\n";
    cout << "1. Full Name\n" << "2. Age\n" << "3. Birthdate\n" << "4. Address\n" << "5. Contact Number\n";
    cout << "6. Department\n" << "7. Treatment Type\n" << "8. Status\n" << "9. Appointment date\n";

    cout << "Enter your choice: ";
    cin >> choice;
    clearScreen();

    cin.ignore();
    cout << "Enter new value: ";
    getline(cin, newValue);

    ifstream file(filename);
    ofstream temp("temp.csv");

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        string currentID = field;
        output = currentID;

        if (currentID == id) {
            found = true;
            int fieldCount = 0;
            while (getline(ss, field, ',')) {
                fieldCount++;
                output += ",";
                if (fieldCount == choice) {
                    output += newValue;
                } else {
                    output += field;
                }
            }
            temp << output << "\n";
        }
        else {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());   
    clearScreen();

    if (found) {
        cout << "Patient information updated successfully.\n";
    } else {
        cout << "Patient with ID " << id << " not found.\n";
    }
    cout << endl;

}

void billingMenu() {
    selectDepartment();  // Ask for department before billing

    int id, days = 0;
    cout << "Enter patient ID for billing: ";
    cin >> id;

    // Check if the patient exists in the file
    ifstream file(filename);
    string line;
    bool found = false;
    ofstream temp("temp.csv");

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        int currentID = stoi(field);

        if (currentID == id) {
            found = true;
            // If department requires room (Surgery or Orthopedics), ask for days stayed
            if (filename == "surgery.csv" || filename == "orthopedics.csv") {
                cout << "Enter number of days stayed: ";
                cin >> days;
            }

            // Calculate the bill (service charge + room charge based on days)
            int departmentIndex = filename == "general_medicine.csv" ? 0 :
                                  filename == "surgery.csv" ? 1 :
                                  filename == "orthopedics.csv" ? 2 : 3;
            int totalBill = serviceCharges[departmentIndex] + (days * 100);  // Assuming 100/day for room

            cout << "Total Bill: $" << totalBill << endl;

            // Update status to "Completed" and write patient info to temp
            temp << currentID << ",";
            for (int i = 1; getline(ss, field, ','); i++) {
                if (i == 7) {
                    temp << "Completed,"; // Update status to "Completed"
                } else {
                    temp << field << ",";
                }
            }
            temp << "\n";
        } else {
            temp << line << "\n"; // Copy other patient records
        }
    }

    file.close();
    temp.close();
    clearScreen();

    if (found) {
        remove(filename.c_str());
        rename("temp.csv", filename.c_str());
        cout << "Patient status updated to 'Completed' and billing finalized.\n";
    } else {
        cout << "Patient with ID " << id << " not found.\n";
    }
}


// Main function - Display the menu
int main() {
    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Register new patient\n";
        cout << "2. Search for a patient by ID\n";
        cout << "3. Edit patient information\n";
        cout << "4. View all patients\n";
        cout << "5. Billing\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        clearScreen();

        switch (choice) {
            case 1: registerPatient(); break;
            case 2: searchPatientByID(); break;
            case 3: editPatientInfo(); break;
            case 4: viewAllPatients(); break;
            case 5: billingMenu(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

