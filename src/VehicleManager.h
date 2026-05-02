#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include "LinkedList.h"
#include "Colors.h"
#include "ResponseStack.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class VehicleManager {
    LinkedList vehicleList;          //Linked list of vehicles
    vector<string> vehicleTypes;     //Available vehicle types
    
public:
    VehicleManager() {
        vehicleTypes = {"Ambulance", "Fire Truck", "Police Car", "Rescue Van", "Patrol Bike"};
        loadVehicles();
    }
    
    //Adds a new vehicle
    void addVehicle() {
        int id;
        int typeChoice;
        
        cout << CYAN << "\n=== ADD EMERGENCY VEHICLE ===\n" << RESET;
        cout << "Enter Vehicle ID (e.g., 101, 202): ";
        cin >> id;
        
        cout << "\nSelect Vehicle Type:\n";
        for(int i = 0; i < vehicleTypes.size(); i++) {
            cout << i+1 << ". " << vehicleTypes[i] << endl;
        }
        cout << "Enter choice (1-" << vehicleTypes.size() << "): ";
        cin >> typeChoice;
        
        if(typeChoice >= 1 && typeChoice <= vehicleTypes.size()) {
            vehicleList.insert(id, vehicleTypes[typeChoice-1].c_str());
            cout << GREEN << "\n✓ " << vehicleTypes[typeChoice-1] << " (ID: " << id << ") added successfully!\n" << RESET;
            
            saveVehicleToFile(id, vehicleTypes[typeChoice-1]);
        }
        else {
            cout << RED << "Invalid choice!\n" << RESET;
        }
    }
    
    //Displays all vehicles
    void showVehicles() {
        cout << CYAN << "\n=== CITY EMERGENCY VEHICLES ===\n" << RESET;
        vehicleList.traverse();
        cout << "Total vehicles in service: " << vehicleList.getCount() << endl;
    }
    
    //Assigns a vehicle to an emergency
    void assignVehicle() {
        int emergencyId, vehicleId;
        cout << "\n=== ASSIGN VEHICLE TO EMERGENCY ===\n";
        cout << "Enter Emergency ID: E";
        cin >> emergencyId;
        cout << "Enter Vehicle ID to assign: ";
        cin >> vehicleId;
        
        cout << GREEN << "\n✓ Vehicle " << vehicleId << " assigned to Emergency E" << emergencyId << RESET << endl;
        
        ofstream log("assignments_log.txt", ios::app);
        if(log.is_open()) {
            log << "Emergency: E" << emergencyId << " | Assigned Vehicle: " << vehicleId << endl;
            log.close();
        }
    }
    
    //Generates fleet report
    void generateReport() {
        ofstream report("fleet_report.txt");
        if(report.is_open()) {
            report << "=== EMERGENCY VEHICLE FLEET REPORT ===\n";
            report << "Total Vehicles: " << vehicleList.getCount() << "\n";
            report << "-------------------------------------\n";
            report << "Vehicle Types Available:\n";

            for(int i = 0; i < vehicleTypes.size(); i++) {
                report << "  " << i+1 << ". " << vehicleTypes[i] << "\n";
            }
            report << "=====================================\n";
            report.close();

            cout << GREEN << "✓ Fleet report saved: fleet_report.txt\n" << RESET;
        }
    }
    
private:
    //Saves vehicle to file
    void saveVehicleToFile(int id, string type) {
        ofstream file("data/vehicles.txt", ios::app);
        if(file.is_open()) {
            file << id << " " << type << endl;
            file.close();
        }
    }
    
    //Loads vehicles from file
    void loadVehicles() {
        ifstream file("data/vehicles.txt");
        if(file.is_open()) {
            int id;
            string type;
            while(file >> id >> type) {
                vehicleList.insert(id, type.c_str());
            }
            file.close();
        }
    }
};

#endif