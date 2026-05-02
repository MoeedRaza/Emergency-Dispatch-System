#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Colors.h"

using namespace std;

//Displays the role selection menu
void showRoleMenu() {
    cout << CYAN << "\n╔══════════════════════════════════════╗\n";
    cout << "║         MAIN ACCESS MENU             ║\n";
    cout << "╚══════════════════════════════════════╝\n" << RESET;
    cout << "1. 👤 Citizen Access\n";
    cout << "2. 🔧 Admin Control Panel\n";
    cout << "0. 🚪 Exit System\n";
}

//Displays the citizen services menu
void showCitizenMenu() {
    cout << CYAN << "\n╔══════════════════════════════════════╗\n";
    cout << "║         CITIZEN SERVICES            ║\n";
    cout << "╚══════════════════════════════════════╝\n" << RESET;
    cout << "1. 📝 Register in System\n";
    cout << "2. 🚨 Report Emergency\n";
    cout << "3. 🔍 Track Emergency Status\n";
    cout << "4. 🏥 Find Nearest Service\n";
    cout << "5. 🛣️  Calculate Route\n";
    cout << "6. 📞 Emergency Contacts\n";
    cout << "0. ↩️  Back to Main Menu\n";
}

//Displays the admin control panel menu
void showAdminMenu() {
    cout << CYAN << "\n╔══════════════════════════════════════╗\n";
    cout << "║         ADMIN CONTROL PANEL        ║\n";
    cout << "╚══════════════════════════════════════╝\n" << RESET;
    cout << "1. 👥 View All Citizens\n";
    cout << "2. 🚗 Add Emergency Vehicle\n";
    cout << "3. 🚘 View All Vehicles\n";
    cout << "4. 📋 View Active Emergencies\n";
    cout << "5. ✏️  Update Emergency Status\n";
    cout << "6. 🔗 Assign Vehicle to Emergency\n";
    cout << "7. 🛣️  Calculate Route\n";
    cout << "8. 🏥 Show Emergency Locations\n";
    cout << "9. 🔍 Find Nearest Service\n";
    cout << "10. 💾 Save Map to File\n";
    cout << "11. 📊 View Response History\n";
    cout << "12. 📈 Generate Reports\n";
    cout << "0. ↩️  Back to Main Menu\n";
}

#endif