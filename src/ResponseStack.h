#ifndef RESPONSESTACK_H
#define RESPONSESTACK_H

#include <iostream>
#include <fstream>
#include "Colors.h"
using namespace std;

//Struct for each response record in the stack
struct ResponseRecord {
    int emergencyId;
    string action;
    string timestamp;
    ResponseRecord* next;
};

class ResponseStack {
    ResponseRecord* top;
    
public:
    ResponseStack() {
        top = nullptr;
        loadFromFile();
    }
    
    ~ResponseStack() {
        saveToFile();
        // Clean up memory
        while(top != nullptr) {
            ResponseRecord* temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    //Pushes a new response record onto the stack
    void push(int emergencyId, const string& action) {
        ResponseRecord* newRecord = new ResponseRecord;
        newRecord->emergencyId = emergencyId;
        newRecord->action = action;
        
        // Simple timestamp simulation
        time_t now = time(0);
        char* timeStr = ctime(&now);
        newRecord->timestamp = string(timeStr);
        newRecord->timestamp.pop_back(); // Remove newline
        
        newRecord->next = top;
        top = newRecord;
        
        cout << GREEN << "✓ Response logged to stack\n" << RESET;
    }
    
    //Removes the top record from the stack
    void pop() {
        if(top == nullptr) {
            cout << RED << "Stack is empty!\n" << RESET;
            return;
        }
        
        ResponseRecord* temp = top;
        top = top->next;
        delete temp;
        
        cout << YELLOW << "Top record removed from stack\n" << RESET;
    }
    
    //Displays all records in the stack
    void displayAll() {
        if(top == nullptr) {
            cout << "No response records yet.\n";
            return;
        }
        
        cout << CYAN << "\n=== EMERGENCY RESPONSE HISTORY (LIFO) ===\n" << RESET;
        ResponseRecord* current = top;
        int count = 1;
        
        while(current != nullptr) {
            cout << "Record #" << count++ << ":\n";
            cout << "  Emergency ID: E" << current->emergencyId << endl;
            cout << "  Action: " << current->action << endl;
            cout << "  Time: " << current->timestamp << endl;
            cout << "  -------------------------\n";
            current = current->next;
        }
    }
    
    //Displays the most recent response records
    void displayRecent(int count = 5) {
        if(top == nullptr) {
            cout << "No response records yet.\n";
            return;
        }
        
        cout << CYAN << "\n=== RECENT " << count << " RESPONSES ===\n" << RESET;
        ResponseRecord* current = top;
        int displayed = 0;
        
        while(current != nullptr && displayed < count) {
            cout << "E" << current->emergencyId << " - " << current->action << " (" << current->timestamp << ")\n";
            current = current->next;
            displayed++;
        }
    }
    
    //Saves stack to file
    void saveToFile() {
        ofstream file("data/response_history.txt");
        if(file.is_open()) {
            ResponseRecord* current = top;
            while(current != nullptr) {
                file << current->emergencyId << "|"
                     << current->action << "|"
                     << current->timestamp << endl;
                current = current->next;
            }
            file.close();
        }
    }
    
    //Loads stack from file
    void loadFromFile() {
        ifstream file("data/response_history.txt");
        if(file.is_open()) {
            string line;
            while(getline(file, line)) {
                size_t pos1 = line.find('|');
                size_t pos2 = line.find('|', pos1 + 1);
                
                if(pos1 != string::npos && pos2 != string::npos) {
                    int id = stoi(line.substr(0, pos1));
                    string action = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    string timestamp = line.substr(pos2 + 1);
                    
                    // Push to stack
                    ResponseRecord* newRecord = new ResponseRecord;
                    newRecord->emergencyId = id;
                    newRecord->action = action;
                    newRecord->timestamp = timestamp;
                    newRecord->next = top;
                    top = newRecord;
                }
            }
            file.close();
        }
    }
    
    //Checks if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }
    
    //Returns the number of records in the stack
    int getSize() {
        int count = 0;
        ResponseRecord* current = top;
        while(current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};

#endif