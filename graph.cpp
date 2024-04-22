//=================================
// Charlie Horner and John Yoon
// graph.h
// Apr 2024
// This file implements the templated graph class
//=================================

#include "graph.h"
#include <sstream>

//========================================================
// Constructor
// Initialize the Graph
// Parameters: None
// Pre-condition: None
// Post-condition: Graph is created
// Return: None
//========================================================
template <typename D, typename K>
        Graph<D, K>::Graph(vector<D> data, vector<K> keys, vector<vector<K>> edges)
{
}

//========================================================
// Get
// Return pointer to the vertex corresponding to the key k
// Parameters: k - key
// Pre-condition: None
// Post-condition: None
// Return: pointer to the vertex with the key k
//========================================================
template <typename D, typename K>
*Node        Graph<D, K>::get(K key)
{
    for(auto &node : V) {           // Iterate through all vertices in the Graph
        if(node->key == key) {
            return node;            // Returns pointer to the vertex if found
        }
    }
    return nullptr;                 // Returns nullptr if not found
}

//========================================================
// Reachable
// Determines if one vertex is reachable from another vertex by providing keys of the vertices
// Parameters: u - key, v - key
// Pre-condition: None
// Post-condition: None
// Return: bool value indicating if vertex with key v is reachable from vertex with key u
//========================================================
template <typename D, typename K>
bool        Graph<D, K>::reachable(K u, K v)
{
    bfs(u);
    return (get(v)->color);         // Returns true if vertex with key v was visited from the bfs on key y
}

//========================================================
// BFS
// Performs breadth-first search algorithm
// Parameters: s - key of the source vertex
// Pre-condition: None
// Post-condition: None
// Return: None
//========================================================
template <typename D, typename K>
void            Graph<D, K>::bfs(K source)
{

}

//========================================================
// Print path
// Prints the shortes path from a vertex to another
// Parameters: u - key, v - key
// Pre-condition: None
// Post-condition: None
// Return: None
//========================================================
template <typename D, typename K>
void            Graph<D, K>::print_path(K u, K v)
{
    if(reachable(u, v)) {                               // We only move on if there exists a path
        stringstream ss;
        if(u == v) {
            ss << u;
            return;
        }
        vector<k> temp;
        Node *ver = get(v);
        while(ver->key != u) {
            temp.push(ver->key);
            ver = ver->pi;
        }
        temp.push(u);
        for(int i = temp.size() - 1; i > 0; i--) {      // Iterate in reverse order so we start with u
            ss << temp[i] << " -> ";
        }
        ss << temp[0];                                  // Add the first element in the vector which is key v
        cout << ss.str() << endl;
    }
}

//========================================================
// Edge class
// Determines the string representation of the edge classification of the edge from vertex u to v
// Parameters: u - key, v - key
// Pre-condition: None
// Post-condition: None
// Return: String representation of the edge classification
//========================================================
template <typename D, typename K>
string          Graph<D, K>::edge_class(K u, K v)
{
}

//========================================================
// BFS tree
// Prints the bfs tree for the source vertex determined by given key
// Parameters: s - key of source vertex
// Pre-condition: None
// Post-condition: None
// Return: None
//========================================================
template <typename D, typename K>
void            Graph<D, K>::bfs_tree(K source)
{
    Node *sNode = get(source);                  
    if(sNode != nullptr) {                      // We only move on if we have a valid source vertex
        stringstream ss;
        sNode->color = true;
        sNode->dis = 0;
        sNode->pi = nullptr;
        for(auto& node: V) {                    // Iterate through all vertices
            node->color = false;
            node->dis = -1;
            node->pi = nullptr;
        }
        queue<Node*> temp;                      // Initialize queue for traversal
        temp.push(sNode);
        ss << sNode->key << endl;
        while(!temp.empty()) {
            int lvl = temp.size();              // Indicates number of vertices at current level
            vector<K> lvlK;
            for(int i = 0; i < lvl; i++) {
                Node * u = temp.front();
                temp.pop();
                for(const K& v: V[u->key]) {
                    Node *vNode = get(v);       // Get the pointer to the vertex
                    if(!vNode->color) {
                        vNode->color = true;
                        vNode->dis = u->dis + 1;
                        vNode->pi = u;
                        temp.push(vNode);
                        lvlK.push_back(v);
                    }
                }
            }
            for(const K& key: lvlK) {
                ss << key << " ";
            }
            ss << endl;
        }
        cout << ss.str();
    }
}