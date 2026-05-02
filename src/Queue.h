#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Struct for emergency node
struct Emergency {
    int id;
    int type;
    Emergency* next;
};

class Queue {
    Emergency* front;                 //Front of the queue(oldest emergency)
    Emergency* rear;                  //Rear of the queue(newest emergency) 
    int nextId;                       //Next emergency ID to assign
    vector<string> emergencyTypes;    //Types of emergencies
    
public:
    Queue() {
        front = rear = nullptr;
        nextId = 1000;
        emergencyTypes = {"Medical", "Fire", "Police", "Accident", "Rescue"};
        loadLastId();
    }
    
    ~Queue() {
        saveLastId();
    }
    
    //Gets the next emergency ID
    int getNextId() {
        return nextId++;
    }
    
    //Adds a new emergency to the queue
    void enqueue(int id, int type) {
        Emergency* newEmergency = new Emergency;
        newEmergency->id = id;
        newEmergency->type = type;
        newEmergency->next = nullptr;
        
        if(rear == nullptr) {
            front = rear = newEmergency;
        }
        else {
            rear->next = newEmergency;
            rear = newEmergency;
        }
        
        // Save to log file
        ofstream log("data/emergency_log.txt", ios::app);
        if(log.is_open()) {
            log << "E" << id << " | Type: " << emergencyTypes[type-1] << endl;
            log.close();
        }
    }
    
    //Removes the emergency from the queue
    void dequeue() {
        if(front == nullptr) {
            cout << "No emergencies in queue!\n";
            return;
        }
        
        Emergency* temp = front;
        front = front->next;
        
        if(front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
    }
    
    //Displays all emergencies in the queue
    void traverse() {
        if(front == nullptr) {
            cout << "No active emergencies.\n";
            return;
        }
        
        Emergency* current = front;
        int count = 1;
        while(current != nullptr) {
            cout << count << ". ID: E" << current->id << " | Type: ";
            
            if(current->type >= 1 && current->type <= emergencyTypes.size()) {
                cout << emergencyTypes[current->type - 1];
            }
            else {
                cout << "Unknown";
            }
            
            cout << endl;
            current = current->next;
            count++;
        }
    }
    
    //Checks if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }
    
    //Returns the number of emergencies in the queue
    int getSize() {
        int count = 0;
        Emergency* current = front;
        while(current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
private:
    //Saves the last used emergency ID to a file
    void saveLastId() {
        ofstream file("last_emergency_id.txt");
        if(file.is_open()) {
            file << nextId;
            file.close();
        }
    }
    
    void loadLastId() {
        ifstream file("data/last_emergency_id.txt");
        if(file.is_open()) {
            file >> nextId;
            file.close();
        }
    }
};

#endif