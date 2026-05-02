#ifndef EMERGENCYMANAGER_H
#define EMERGENCYMANAGER_H

#include "Queue.h"
#include "CityMap.h"
#include "Colors.h"
#include "ResponseStack.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class EmergencyManager {
    Queue emergencyQueue;               //Queue for managing emergency
    vector<int> emergencyStatus;
    vector<int> userLocations;          //Caller's location IDs
    vector<int> emergencyLocations;     //Emergency location IDs
    vector<string> emergencyTypes;      //Types of emergencies(Medical, Fire, Police etc)
    CityMap cityMap;
    ResponseStack responseStack;
    
public:
    EmergencyManager() : emergencyTypes({"Medical", "Fire", "Police", "Accident", "Rescue"}) {
        loadEmergencies();
    }

    //For reporting a new emergency
    void reportEmergency() {
        int emergencyType;
        int userLocationId;
        int emergencyLocationId;
        string sameLocation;
        
        cout << CYAN << "\n=== REPORT EMERGENCY ===\n" << RESET;
        
        cout << "\n🔴 Emergency Types:\n";
        for(int i = 0; i < emergencyTypes.size(); i++) {
            cout << i+1 << ". " << emergencyTypes[i] << endl;
        }
        cout << "Select emergency type (1-5): ";
        cin >> emergencyType;
        
        if(emergencyType < 1 || emergencyType > 5) {
            cout << RED << "Invalid emergency type!\n" << RESET;
            return;
        }
        
        cityMap.showAllLocations();
        
        cout << "\n📍 YOUR CURRENT LOCATION\n";
        cout << "Where are you calling from? (0-19): ";
        cin >> userLocationId;
        
        if(userLocationId < 0 || userLocationId > 19) {
            cout << RED << "Invalid location!\n" << RESET;
            return;
        }
        
        cout << "\n❓ Is the emergency at your current location? (yes/no): ";
        cin >> sameLocation;
        
        if(sameLocation == "yes" || sameLocation == "y") {
            emergencyLocationId = userLocationId;
            cout << "✓ Emergency location set to your current location.\n";
        }
        else {
            cout << "\n📍 EMERGENCY LOCATION\n";
            cout << "Where is the emergency happening? (0-19): ";
            cin >> emergencyLocationId;
            
            if(emergencyLocationId < 0 || emergencyLocationId > 19) {
                cout << RED << "Invalid location!\n" << RESET;
                return;
            }
        }
        
        //Generates emergency ID and to queue
        int emergencyId = emergencyQueue.getNextId();
        emergencyQueue.enqueue(emergencyId, emergencyType);
        emergencyStatus.push_back(0);
        userLocations.push_back(userLocationId);
        emergencyLocations.push_back(emergencyLocationId);
        
        cout << GREEN << "\n✓✓✓ EMERGENCY REPORTED SUCCESSFULLY! ✓✓✓\n" << RESET;
        cout << "==========================================\n";
        cout << "Emergency ID: " << RED << "E" << emergencyId << RESET << endl;
        cout << "Emergency Type: " << emergencyTypes[emergencyType-1] << endl;
        cout << "📞 Caller Location: " << cityMap.getLocationName(userLocationId) << endl;
        cout << "📍 Emergency Location: " << cityMap.getLocationName(emergencyLocationId) << endl;
        cout << "==========================================\n";
        cout << "⚠️  Save this ID for tracking: E" << emergencyId << "\n";
        
        string neededService;
        switch(emergencyType) {
            case 1: neededService = "Hospital"; break;
            case 2: neededService = "Fire"; break;
            case 3: neededService = "Police"; break;
            case 4: neededService = "Rescue"; break;
        }
        
        cout << "\n" << YELLOW << "🚨 DISPATCH INFORMATION 🚨\n" << RESET;
        cout << "==========================================\n";
        cout << "Emergency Location: " << cityMap.getLocationName(emergencyLocationId) << "\n";
        cout << "Required Service: " << neededService << "\n";
        
        // Use the existing method from CityMap
        cityMap.findNearestEmergencyService(emergencyLocationId, neededService);
        
        responseStack.push(emergencyId, "Emergency reported - Type: " + emergencyTypes[emergencyType-1]);
        saveToFile();
    }
    
    //Tracks an existing emergency
    void trackEmergency() {
        int searchId;
        cout << "\nEnter your Emergency ID (without E): ";
        cin >> searchId;
        
        int index = searchId - 1000;
        if(index >= 0 && index < emergencyStatus.size()) {
            cout << CYAN << "\n=== EMERGENCY STATUS ===\n" << RESET;
            cout << "Emergency ID: E" << searchId << endl;
            
            if(index < userLocations.size()) {
                cout << "📞 Caller Location: " << cityMap.getLocationName(userLocations[index]) << endl;
            }
            
            if(index < emergencyLocations.size()) {
                cout << "📍 Emergency Location: " << cityMap.getLocationName(emergencyLocations[index]) << endl;
            }
            
            cout << "Status: ";
            if(emergencyStatus[index] == 0) {
                cout << YELLOW << "⏳ PENDING - Waiting for emergency services\n" << RESET;
            }
            else if(emergencyStatus[index] == 1) {
                cout << BLUE << "🚗 ASSIGNED - Help is on the way!\n" << RESET;
            }
            else if(emergencyStatus[index] == 2) {
                cout << GREEN << "✅ RESOLVED - Emergency handled successfully\n" << RESET;
            }
        }
        else {
            cout << RED << "❌ Emergency ID not found!\n" << RESET;
        }
    }
    
    //Displays all active emergencies
    void showAllEmergencies() {
        cout << CYAN << "\n=== ACTIVE EMERGENCIES ===\n" << RESET;
        
        if(emergencyQueue.isEmpty()) {
            cout << "No active emergencies at the moment.\n";
            return;
        }
        
        emergencyQueue.traverse();
    }
    
    //Updates status of an emergency
    void updateStatus() {
        int id, newStatus;
        cout << "\nEnter Emergency ID to update: E";
        cin >> id;
        cout << "Enter new status (0=Pending, 1=Assigned, 2=Resolved): ";
        cin >> newStatus;
        
        int index = id - 1000;
        if(index >= 0 && index < emergencyStatus.size()) {
            emergencyStatus[index] = newStatus;
            
            string action;
            if(newStatus == 1) action = "Vehicle assigned to emergency";
            else if(newStatus == 2) action = "Emergency resolved";
            else action = "Status updated to pending";
            
            responseStack.push(id, action);
            
            cout << GREEN << "✓ Status updated successfully!\n" << RESET;
            saveToFile();
        }
        else {
            cout << RED << "❌ Invalid Emergency ID!\n" << RESET;
        }
    }
    
    //Finds route between two locations
    void findRouteBetweenLocations() {
        int startId, endId;
        
        cityMap.showAllLocations();
        
        cout << "\n🚗 ROUTE CALCULATION\n";
        cout << "Enter START location ID (where from): ";
        cin >> startId;
        cout << "Enter DESTINATION location ID (where to): ";
        cin >> endId;
        
        cout << "\n" << CYAN << "=== ROUTE CALCULATION ===\n" << RESET;
        cout << "From: " << cityMap.getLocationName(startId) << "\n";
        cout << "To: " << cityMap.getLocationName(endId) << "\n";
        cout << "----------------------------\n";
        
        cityMap.findShortestPath(startId, endId);
    }
    
    //Finds nearest emergency service from a location
    void findNearestService() {
        int locationId;
        string serviceType;
        
        cityMap.showAllLocations();
        
        cout << "\n📍 Enter your current location ID: ";
        cin >> locationId;
        
        cout << "\n🔧 Service needed:\n";
        cout << "1. Hospital\n";
        cout << "2. Police Station\n";
        cout << "3. Fire Station\n";
        cout << "4. Rescue Center\n";
        cout << "Select service (1-4): ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1: serviceType = "Hospital"; break;
            case 2: serviceType = "Police"; break;
            case 3: serviceType = "Fire"; break;
            case 4: serviceType = "Rescue"; break;
            default: serviceType = "Hospital";
        }
        
        cout << "\n" << YELLOW << "=== FINDING NEAREST " << serviceType << " ===\n" << RESET;
        cout << "Your location: " << cityMap.getLocationName(locationId) << "\n";
        cout << "----------------------------\n";
        
        cityMap.findNearestEmergencyService(locationId, serviceType);
    }
   
    //Displays emergency service locations
    void showEmergencyLocations() {
        cityMap.showEmergencyLocations();
    }
    
    //Saves city map to file
    void saveMapToFile() {
        cityMap.saveMapToFile();
    }
    
    //Displays response history
    void showResponseHistory() {
        cout << CYAN << "\n=== EMERGENCY RESPONSE HISTORY ===\n" << RESET;
        responseStack.displayRecent(10);
    }
    
private:
    //Saves emergencies to file
    void saveToFile() {
        ofstream file("data/emergencies.txt");
        if(file.is_open()) {
            for(int i = 0; i < emergencyStatus.size(); i++) {
                file << 1000 + i << " " 
                     << emergencyStatus[i] << " "
                     << userLocations[i] << " "
                     << emergencyLocations[i] << endl;
            }
            file.close();
        }
    }
    
    //Loads emergencies from file
    void loadEmergencies() {
        ifstream file("data/emergencies.txt");
        if(file.is_open()) {
            int id, status, userLoc, emergLoc;
            while(file >> id >> status >> userLoc >> emergLoc) {
                emergencyQueue.enqueue(id, 1);
                emergencyStatus.push_back(status);
                userLocations.push_back(userLoc);
                emergencyLocations.push_back(emergLoc);
            }
            file.close();
        }
    }
};

#endif