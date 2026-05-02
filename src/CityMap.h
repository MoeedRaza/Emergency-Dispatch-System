#ifndef CITYMAP_H
#define CITYMAP_H

#include<iostream>
#include<vector>
// #include <climits>
#include <fstream>
#include "Colors.h"
using namespace std;

class CityMap {
private:
    //Struct for each location in the city
    struct Location {
        int id;              //Unique identifier
        string name;         // Location name
        string type;         // Hospital, Police, Residential, etc.
    };
    
    vector<Location> locations;               //List of locations in the city
    vector<vector<int>> adjacencyMatrix;      
    vector<vector<int>> distances;            // Shortest distances between locations
    int totalLocations;
    
public:
    CityMap() {
        totalLocations = 20;
        initializeLocations();
        initializeDistances();
        loadFromFile();
    }

    // For shortest distance
    int getDistance(int fromId, int toId) {
        if(fromId >= 0 && fromId < totalLocations && 
           toId >= 0 && toId < totalLocations) {
            return distances[fromId][toId];
        }
        return INT_MAX;
    }
    
    //Initializes all locations in Islamabad with sector names
    void initializeLocations() {
        // Islamabad locations with sector names
        locations = {
            {0, "Shifa Hospital", "Hospital"},
            {1, "Polyclinic Hospital", "Hospital"},
            {2, "G-8 Police Station", "Police"},
            {3, "F-10 Police Station", "Police"},
            {4, "F-8 Fire Station", "Fire"},
            {5, "G-9 Fire Station", "Fire"},
            {6, "I-8 Rescue Center", "Rescue"},
            {7, "F-10 Rescue Center", "Rescue"},
            {8, "G-6 Sector", "Residential"},
            {9, "F-7 Sector", "Residential"},
            {10, "E-7 Sector", "Residential"},
            {11, "I-8 Sector", "Residential"},
            {12, "H-8 Sector", "Commercial"},
            {13, "F-6 Sector", "Commercial"},
            {14, "Blue Area", "Commercial"},
            {15, "Islamabad Highway", "Road"},
            {16, "7th Avenue", "Road"},
            {17, "Jinnah Avenue", "Road"},
            {18, "Airport", "Transport"},
            {19, "Zero Point", "Transport"}
        };
        
        adjacencyMatrix.resize(totalLocations, vector<int>(totalLocations, 0));
        distances.resize(totalLocations, vector<int>(totalLocations, INT_MAX));
        
        for(int i = 0; i < totalLocations; i++) {
            distances[i][i] = 0;
        }
    }
    
    // Initializes distances between locations
    void initializeDistances() {
        //Add connections between locations with distances in km
        addConnection(0, 2, 3);   // Shifa Hospital to G-8 Police
        addConnection(0, 8, 2);   // Shifa Hospital to G-6
        addConnection(0, 15, 4);  // Shifa Hospital to Highway
        
        addConnection(1, 3, 2);   // Polyclinic to F-10 Police
        addConnection(1, 9, 3);   // Polyclinic to F-7
        addConnection(1, 17, 2);  // Polyclinic to Jinnah Ave
        
        addConnection(2, 4, 5);   // G-8 Police to F-8 Fire
        addConnection(2, 8, 4);   // G-8 Police to G-6
        
        addConnection(3, 5, 4);   // F-10 Police to G-9 Fire
        addConnection(3, 7, 1);   // F-10 Police to F-10 Rescue
        
        addConnection(4, 6, 6);   // F-8 Fire to I-8 Rescue
        addConnection(4, 12, 3);  // F-8 Fire to H-8
        
        addConnection(5, 11, 2);  // G-9 Fire to I-8 Sector
        addConnection(5, 16, 3);  // G-9 Fire to 7th Ave
        
        addConnection(6, 11, 1);  // I-8 Rescue to I-8 Sector
        
        addConnection(7, 10, 2);  // F-10 Rescue to E-7
        
        addConnection(8, 12, 5);  // G-6 to H-8
        addConnection(8, 13, 3);  // G-6 to F-6
        
        addConnection(9, 14, 2);  // F-7 to Blue Area
        addConnection(9, 17, 1);  // F-7 to Jinnah Ave
        
        addConnection(10, 14, 4); // E-7 to Blue Area
        
        addConnection(11, 18, 18); // I-8 to Airport
        
        addConnection(12, 16, 2); // H-8 to 7th Ave
        
        addConnection(13, 17, 2); // F-6 to Jinnah Ave
        
        addConnection(14, 19, 3); // Blue Area to Zero Point
        
        addConnection(15, 18, 10); // Highway to Airport
        addConnection(15, 19, 5);  // Highway to Zero Point
        
        addConnection(16, 19, 4); // 7th Ave to Zero Point
        
        addConnection(17, 19, 1); // Jinnah Ave to Zero Point
        
        calculateAllShortestPaths();
    }
    
    // Add a bidirectional connection
    void addConnection(int from, int to, int distance) {
        adjacencyMatrix[from][to] = distance;
        adjacencyMatrix[to][from] = distance;
        distances[from][to] = distance;
        distances[to][from] = distance;
    }
    
    // Floyd-Warshall Algorithm to calculate all pairs shortest paths
    void calculateAllShortestPaths() {
        for(int k = 0; k < totalLocations; k++) {
            for(int i = 0; i < totalLocations; i++) {
                for(int j = 0; j < totalLocations; j++) {
                    if(distances[i][k] != INT_MAX && distances[k][j] != INT_MAX) {
                        if(distances[i][j] > distances[i][k] + distances[k][j]) {
                            distances[i][j] = distances[i][k] + distances[k][j];
                        }
                    }
                }
            }
        }
    }
    
    // For name of location
    string getLocationName(int id) {
        if(id >= 0 && id < locations.size()) {
            return locations[id].name;
        }
        return "Unknown";
    }
    
    //For type of location
    string getLocationType(int id) {
        if(id >= 0 && id < locations.size()) {
            return locations[id].type;
        }
        return "Unknown";
    }
    
    //For finding shortest path using Dijkstra's algorithm and displaying it
    void findShortestPath(int startId, int endId) {
        if(startId < 0 || startId >= totalLocations || 
           endId < 0 || endId >= totalLocations) {
            cout << RED << "Invalid locations!\n" << RESET;
            return;
        }
        
        //Checks if path exists
        if(distances[startId][endId] == INT_MAX) {
            cout << RED << "No path exists between these locations!\n" << RESET;
            return;
        }
        
        //Display data
        cout << CYAN << "\n=== SHORTEST ROUTE ===\n" << RESET;
        cout << "From: " << locations[startId].name << " (" << locations[startId].type << ")\n";
        cout << "To: " << locations[endId].name << " (" << locations[endId].type << ")\n";
        cout << "Total Distance: " << distances[startId][endId] << " km\n";
        cout << "Estimated Time: " << distances[startId][endId] * 2 << " minutes\n";
        
        vector<int> path = dijkstra(startId, endId);
        
        if(!path.empty()) {
            cout << "\nRoute: ";
            for(int i = 0; i < path.size(); i++) {
                cout << locations[path[i]].name;
                if(i != path.size() - 1) {
                    cout << " → ";
                }
            }
            cout << endl;
        }
    }
    
    // Dijkstra's algorithm to find shortest path
    vector<int> dijkstra(int start, int end) {
        vector<int> dist(totalLocations, INT_MAX);
        vector<int> prev(totalLocations, -1);
        vector<bool> visited(totalLocations, false);
        
        dist[start] = 0;
        
        for(int count = 0; count < totalLocations - 1; count++) {
            int u = -1;
            int minDist = INT_MAX;
            
            for(int v = 0; v < totalLocations; v++) {
                if(!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }
            
            if(u == -1 || u == end) break;
            visited[u] = true;
            
            for(int v = 0; v < totalLocations; v++) {
                if(!visited[v] && adjacencyMatrix[u][v] != 0 && 
                   dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjacencyMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
        
        vector<int> path;
        for(int at = end; at != -1; at = prev[at]) {
            path.insert(path.begin(), at);
        }
        
        if(path[0] != start) {
            path.clear();
        }
        
        return path;
    }
    
    //Displays all locations
    void showAllLocations() {
        cout << CYAN << "\n=== ISLAMABAD LOCATIONS ===\n" << RESET;
        cout << "ID\tLocation\t\tType\n";
        cout << "----------------------------------------\n";
        
        for(int i = 0; i < locations.size(); i++) {
            cout << i << "\t" << locations[i].name;
            if(locations[i].name.length() < 16) cout << "\t";
            cout << "\t" << locations[i].type << endl;
        }
    }
    
    //Displays emergency service locations
    void showEmergencyLocations() {
        cout << CYAN << "\n=== EMERGENCY SERVICE LOCATIONS ===\n" << RESET;
        
        cout << "\n🏥 HOSPITALS:\n";
        for(int i = 0; i < locations.size(); i++) {
            if(locations[i].type == "Hospital") {
                cout << "  " << i << ". " << locations[i].name << endl;
            }
        }
        
        cout << "\n🚔 POLICE STATIONS:\n";
        for(int i = 0; i < locations.size(); i++) {
            if(locations[i].type == "Police") {
                cout << "  " << i << ". " << locations[i].name << endl;
            }
        }
        
        cout << "\n🚒 FIRE STATIONS:\n";
        for(int i = 0; i < locations.size(); i++) {
            if(locations[i].type == "Fire") {
                cout << "  " << i << ". " << locations[i].name << endl;
            }
        }
        
        cout << "\n🚑 RESCUE CENTERS:\n";
        for(int i = 0; i < locations.size(); i++) {
            if(locations[i].type == "Rescue") {
                cout << "  " << i << ". " << locations[i].name << endl;
            }
        }
    }
    
    //Saves map to file
    void saveMapToFile() {
        ofstream file("data/city_map.txt");
        if(file.is_open()) {
            file << "=== ISLAMABAD CITY MAP ===\n";
            file << "Total Locations: " << locations.size() << "\n\n";
            
            file << "LOCATIONS:\n";
            for(const auto& loc : locations) {
                file << loc.id << ". " << loc.name << " (" << loc.type << ")\n";
            }
            
            file << "\nCONNECTIONS (Distances in km):\n";
            for(int i = 0; i < totalLocations; i++) {
                for(int j = i + 1; j < totalLocations; j++) {
                    if(adjacencyMatrix[i][j] > 0) {
                        file << locations[i].name << " ↔ " 
                             << locations[j].name << " : " 
                             << adjacencyMatrix[i][j] << " km\n";
                    }
                }
            }
            
            file.close();
            cout << GREEN << "✓ City map saved to city_map.txt\n" << RESET;
        }
    }
    
    void loadFromFile() {
        // Could load custom map from file here
    }
    
    // For finding nearest emergency service
    void findNearestEmergencyService(int locationId, const string& serviceType) {
        int nearestId = -1;
        int minDistance = INT_MAX;
        
        cout << CYAN << "\n=== FINDING NEAREST " << serviceType << " ===\n" << RESET;
        cout << "Emergency Location: " << getLocationName(locationId) << endl;
        
        for(int i = 0; i < locations.size(); i++) {
            if(locations[i].type == serviceType) {
                int distance = distances[locationId][i];
                if(distance < minDistance) {
                    minDistance = distance;
                    nearestId = i;
                }
            }
        }
        
        if(nearestId != -1 && minDistance != INT_MAX) {
            cout << "Nearest " << serviceType << ": " << getLocationName(nearestId) << endl;
            cout << "Distance: " << minDistance << " km\n";
            cout << "Estimated arrival time: " << minDistance * 2 << " minutes\n";
            findShortestPath(nearestId, locationId);
        } else {
            cout << RED << "No " << serviceType << " found!\n" << RESET;
        }
    }
};

#endif