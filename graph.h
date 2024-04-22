//=================================
// Charlie Horner and John Yoon
// graph.h
// Apr 2024
// This file contains the class header for the templated graph class
//=================================

#ifndef GRAPH_H
#define GRAPH_H_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
#include <queue>
#include <tuple>

using namespace std;
template <class D, class K> // D is data type and K is key type
class Graph{
    
    private: 
        struct Node{
            D data;
            K key;
            *Node pi;
            bool color;
            int dis;
        };
        *Node E[];
        K V[][];

    public:
        Graph(vector<D> data, vector<K> keys, vector<vector<K>> edges); // Constructor

        *Node get(K key); // Pointer to vertex of the given key
        bool reachable(K u, K v); // Check if vertex of key v is reachable from vertex of key u
        void bfs(K source); // BFS from source vertex of the given key
        void print_path(K u, K v); // Print shortest path from vertex of key u to vertex of key v
        string edge_class(K u, K v); // String representation of the edge classification of edge from u to v
        void bfs_tree(K source); // Print bfs tree for the vertex of the given key

};

#include "graph.cpp"

#endif