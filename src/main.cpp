#include <iostream>
#include <fstream>
#include "menu.h"
#include "UserManager.h"
#include "EmergencyManager.h"
#include "VehicleManager.h"
#include "CityMap.h"
#include "Colors.h"
using namespace std;

// Displays the welcome screen
void showWelcomeScreen() {
    cout << BLUE << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║       ISLAMABAD SMART CITY EMERGENCY DISPATCH        ║\n";
    cout << "║                   MANAGEMENT SYSTEM                   ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n" << RESET;
}

// Saves a daily operations report
void saveDailyReport() {
    ofstream report("data/daily_report.txt", ios::app);
    if(report.is_open()) {
        report << "\n=== DAILY OPERATIONS REPORT ===\n";
        report << "Date: [System Date]\n";
        report << "Time: [System Time]\n";
        report << "System: Islamabad Emergency Dispatch\n";
        report << "===================================\n\n";
        report.close();
        cout << GREEN << "✓ Daily report saved\n" << RESET;
    }
}

int main() {
    UserManager userManager;             //Manages citizens
    EmergencyManager emergencyManager;   //Manages emergencies
    VehicleManager vehicleManager;       //Manages emergency vehicles
    
    showWelcomeScreen();
    
    int userRole;
    do {
        showRoleMenu();
        cout << "\nEnter choice: ";
        cin >> userRole;
        
        if(userRole == 1) {
            int citizenChoice;

            do {
                showCitizenMenu();
                cout << "\nEnter your choice: ";
                cin >> citizenChoice;
                
                if(citizenChoice == 1) {
                    userManager.addUser();
                }
                else if(citizenChoice == 2) {
                    emergencyManager.reportEmergency();
                }
                else if(citizenChoice == 3) {
                    emergencyManager.trackEmergency();
                }
                else if(citizenChoice == 4) {
                    emergencyManager.findNearestService();
                }
                else if(citizenChoice == 5) {
                    emergencyManager.findRouteBetweenLocations();
                }
                else if(citizenChoice == 6) {
                    cout << CYAN << "\n=== EMERGENCY CONTACTS ===\n" << RESET;
                    cout << "📞 Police: 15\n";
                    cout << "📞 Fire: 16\n";
                    cout << "📞 Ambulance: 112\n";
                    cout << "📞 Rescue: 112\n";
                    cout << "📞 Emergency Helpline: 112 (24/7)\n";
                }
                
            } while(citizenChoice != 0);
        }
        
        else if(userRole == 2) {
            int adminPin;
            cout << "\nEnter 4-digit Admin PIN: ";
            cin >> adminPin;
            
            if(adminPin != 1234) {
                cout << RED << "✗ Access Denied! Invalid PIN.\n" << RESET;
                continue;
            }
            
            cout << GREEN << "✓ Admin Access Granted!\n" << RESET;
            
            int adminChoice;
            do {
                showAdminMenu();
                cout << "\nSelect command (0-13): ";
                cin >> adminChoice;
                
                if(adminChoice == 1) {
                    userManager.showUsers();
                }
                else if(adminChoice == 2) {
                    vehicleManager.addVehicle();
                }
                else if(adminChoice == 3) {
                    vehicleManager.showVehicles();
                }
                else if(adminChoice == 4) {
                    emergencyManager.showAllEmergencies();
                }
                else if(adminChoice == 5) {
                    emergencyManager.updateStatus();
                }
                else if(adminChoice == 6) {
                    vehicleManager.assignVehicle();
                }
                else if(adminChoice == 7) {
                    emergencyManager.findRouteBetweenLocations();
                }
                else if(adminChoice == 8) {
                    emergencyManager.showEmergencyLocations();
                }
                else if(adminChoice == 9) {
                    emergencyManager.findNearestService();
                }
                else if(adminChoice == 10) {
                    emergencyManager.saveMapToFile();
                }
                else if(adminChoice == 11) {
                    emergencyManager.showResponseHistory();
                }
                else if(adminChoice == 12) {
                    userManager.generateUserReport();
                    vehicleManager.generateReport();
                    saveDailyReport();
                }
                
            } while(adminChoice != 0);
        }
        
    } while(userRole != 0);
    
    cout << GREEN << "\n✓ System shutdown complete.\n";
    cout << "✓ All data has been saved.\n";
    cout << "✓ Thank you for using Islamabad Emergency Dispatch System!\n" << RESET;
    
    return 0;
}