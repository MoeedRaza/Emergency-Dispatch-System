#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
using namespace std;

//Struct for vehicles in the linked list
struct Node {
    int id;
    char type[20];
    Node* next;
};

class LinkedList {
    Node* head;
    int count;
    
public:
    LinkedList() { 
        head = nullptr; 
        count = 0;
    }
    
    ~LinkedList() {
        // Clean up memory
        Node* current = head;
        while(current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    //Inserts a new vehicle at the beginning
    void insert(int id, const char type[]) {
        Node* newNode = new Node;
        newNode->id = id;
        
        // Copy type string
        int i = 0;
        while(type[i] && i < 19) {
            newNode->type[i] = type[i];
            i++;
        }
        newNode->type[i] = '\0';
        
        // Add to beginning
        newNode->next = head;
        head = newNode;
        count++;
    }
    
    //Displays all vehicles
    void traverse() {
        if(head == nullptr) {
            cout << "No vehicles in the list.\n";
            return;
        }
        
        Node* current = head;
        int serial = 1;
        while(current != nullptr) {
            cout << "  " << serial++ << ". ID: " << current->id << " | Type: " << current->type << endl;
            current = current->next;
        }
    }
    
    //Returns the count of vehicles
    int getCount() {
        return count;
    }
    
    //Saves all vehicles to a file
    void saveToFile(const char* filename) {
        ofstream file(filename);
        if(file.is_open()) {
            Node* current = head;
            while(current != nullptr) {
                file << current->id << " " << current->type << endl;
                current = current->next;
            }
            file.close();
        }
    }
};

#endif