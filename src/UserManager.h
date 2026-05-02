#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "HashTable.h"
#include "Colors.h"
#include <fstream>
#include <iostream>
using namespace std;

class UserManager {
    HashTable userTable;
    
public:
    //Adds a new user
    void addUser() {
        int id;
        char name[30];
        
        cout << CYAN << "\n=== USER REGISTRATION ===\n" << RESET;
        cout << "Enter User ID (4-digit number): ";
        cin >> id;
        
        // Check if ID already exists
        if(userTable.search(id)) {
            cout << RED << "User ID already exists! Try another.\n" << RESET;
            return;
        }
        
        cout << "Enter Full Name: ";
        cin.ignore(); // Clear input buffer
        cin.getline(name, 30);
        
        userTable.insert(id, name);
        cout << GREEN << "\n✓ Registration Successful!\n" << RESET;
        cout << "User ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        
        // Also save to separate citizen list file
        saveToCitizenFile(id, name);
    }
    
    //Displays all registered users
    void showUsers() {
        cout << CYAN << "\n=== REGISTERED CITIZENS ===\n" << RESET;
        userTable.traverse();
    }
    
    //Checks if a user exists by ID
    bool checkUser(int id) {
        return userTable.search(id);
    }
    
    //Generates a citizen report
    void generateUserReport() {
        ofstream report("citizen_report.txt");
        if(report.is_open()) {
            report << "=== SMART CITY CITIZEN REPORT ===\n";
            report << "Total Registered Citizens: " << userTable.getCount() << "\n";
            report << "Generated on: [System Date]\n";
            report << "===============================\n\n";
            report.close();
            cout << GREEN << "Citizen report generated: citizen_report.txt\n" << RESET;
        }
    }
    
private:
    //Saves citizen details to a citizen list file
    void saveToCitizenFile(int id, const char* name) {
        ofstream file("data/citizen_list.txt", ios::app);
        if(file.is_open()) {
            file << "ID: " << id << " | Name: " << name << endl;
            file.close();
        }
    }
};

#endif