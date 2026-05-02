#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
using namespace std;

//Struct for user data
struct User {
    int id;
    char name[30];
};

class HashTable {
    static const int SIZE = 100;
    User table[SIZE];
    bool used[SIZE];
    int userCount;
    
public:
    HashTable() : userCount(0) {
        for(int i = 0; i < SIZE; i++) {
            used[i] = false;
        }
        loadFromFile();
    }
    
    ~HashTable() {
        saveToFile();
    }
    
    int hash(int key) { 
        return key % SIZE; 
    }
    
    //Inserts a new user
    void insert(int id, const char name[]) {
        int i = hash(id);
        
        // Handle collision with linear probing
        int attempts = 0;
        while(used[i] && attempts < SIZE) {
            i = (i + 1) % SIZE;
            attempts++;
        }
        
        if(attempts >= SIZE) {
            cout << "Hash table is full!\n";
            return;
        }
        
        table[i].id = id;
        
        int j = 0;
        while(name[j] && j < 29) { 
            table[i].name[j] = name[j]; 
            j++; 
        }
        table[i].name[j] = '\0';
        
        used[i] = true;
        userCount++;
        
        cout << "User stored at index " << i << endl;
    }
    
    //Searches for a user by ID
    bool search(int id) {
        int i = hash(id);
        int attempts = 0;
        
        while(attempts < SIZE) {
            if(used[i] && table[i].id == id) {
                return true;
            }
            i = (i + 1) % SIZE;
            attempts++;
        }
        return false;
    }
    
    //Displays all users in the hash table
    void traverse() {
        if(userCount == 0) {
            cout << "No users registered yet.\n";
            return;
        }
        
        cout << "\n=== REGISTERED USERS ===\n";
        cout << "ID\tName\n";
        cout << "----------------------\n";
        
        for(int i = 0; i < SIZE; i++) {
            if(used[i]) {
                cout << table[i].id << "\t" << table[i].name << endl;
            }
        }
        cout << "Total users: " << userCount << endl;
    }
    
    //Returns the count of users
    int getCount() {
        return userCount;
    }
    
private:
    //Saves users to file
    void saveToFile() {
        ofstream file("users_data.txt");
        if(file.is_open()) {
            for(int i = 0; i < SIZE; i++) {
                if(used[i]) {
                    file << table[i].id << " " << table[i].name << endl;
                }
            }
            file.close();
            cout << "Users saved to file.\n";
        }
        else {
            cout << "Error saving users to file!\n";
        }
    }
    
    //Loads users from file
    void loadFromFile() {
        ifstream file("users_data.txt");
        if(file.is_open()) {
            int id;
            char name[30];
            
            while(file >> id) {
                file.ignore(); // ignore space
                file.getline(name, 30);
                insert(id, name);
            }
            file.close();
            cout << "Loaded " << userCount << " users from file.\n";
        }
    }
};

#endif