#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v) {
        V = v;
        adj.resize(v);
    }

    //Adds an undirected edge
    void addEdge(int u,int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //Displays the adjacency list
    void display() {
        for(int i=0;i<V;i++) {
            cout << i << ": ";
            for(int j=0;j<adj[i].size();j++)
                cout << adj[i][j] << " ";
            cout << endl;
        }
    }
};

#endif