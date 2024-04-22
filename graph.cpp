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
template <class D, class K>
Graph<D, K>::Graph(vector<D> data, vector<K> keys, vector<vector<K>> edges){
    E = edges;
    for(int i = 0; i < keys.size(); i++){
        Node* newNode = new Node;  // Create a new Node
        newNode->key = keys[i];
        newNode->data = data[i];
        newNode->f1 = -1;
        newNode->f2 = -1;
        newNode->color = 0;
        newNode->dpi = nullptr;
        V.push_back(newNode);  // Add the new Node to the vector V
    }
    this->dfs();
}

//========================================================
// Get
// Return pointer to the vertex corresponding to the key k
// Parameters: key - key
// Pre-condition: key must be provided
// Post-condition: None
// Return: pointer to the vertex with the key k
//========================================================
template <class D, class K>
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
// Pre-condition: keys u anv v must be provided
// Post-condition: None
// Return: bool value indicating if vertex with key v is reachable from vertex with key u
//========================================================
template <class D, class K>
bool        Graph<D, K>::reachable(K u, K v)
{
    bfs(u);
    return (get(v)->colorbfs);         // Returns true if vertex with key v was visited from the bfs on key y
}

//========================================================
// BFS
// Performs breadth-first search algorithm
// Parameters: s - key of the source vertex
// Pre-condition: None
// Post-condition: None
// Return: None
//========================================================
template <class D, class K>
void            Graph<D, K>::bfs(K source){
    int time = 0;
    Node* Q[V.size()+1];
    int head = 0, tail = 0;
    for (Node* x : V){
        if(x->key != source){
            x-> dis = -1;
        }
        else{
            x-> dis = time;
            x->colorbfs = 1;
            Q[tail] = x;
            tail++;
        }
        x-> pi = nullptr;
    };

    while(tail != head){
        time++;
        Node* current = Q[head];
        head++;
        for(int i = 0; i < V.size(); i ++){
            if(V[i]->key == current->key){
                for(K edge : E[i]){
                    Node* edgep = this->Get(edge);
                    if(edgep->dis == -1){
                        edgep->dis = time;
                        edgep->colorbfs = 1;
                        edgep->pi = current;
                        Q[tail] = edgep;
                        tail++;
                    }
                }
            }
        }
    }  
}


//========================================================
// DFS
// Performs depth-first search algorithm
// Parameters: s - key of the source vertex
// Pre-condition: None
// Post-condition: None
// Return: None
//========================================================
template <class D, class K>
void            Graph<D, K>>::dfs(K source)template<class D, class K>
void Graph<D,K>::dfs(){
    int time = 0;
    Node* S[V.size()+1];
    for(Node* node : V){
        if(node->color == 0){
            time = dfs_visit(node, time);
        }
    }
}


template<class D, class K>
int Graph<D,K>::dfs_visit(Node* u, int time){
    time++;
    u->f1 = time;
    u->color = 1;
    for(int i = 0; i < V.size(); i++){
        if(V[i] == u){
            for( K key : E[i]){
                Node* edge = this->Get(key);
                if(edge->color == 0){
                    edge->dpi = u;
                    time = dfs_visit(edge, time);
                }
            }
        }
    }
    u->color = 2;
    time++;
    u->f2 =time;
    return time;
}     

//========================================================
// Print path
// Prints the shortes path from a vertex to another
// Parameters: u - key, v - key
// Pre-condition: keys u and v must be provided
// Post-condition: None
// Return: None
//========================================================
template <class D, class K>
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
template <class D, class K>
string          Graph<D, K>::edge_class(K u, K v)
{
}

//========================================================
// BFS tree
// Prints the bfs tree for the source vertex determined by given key
// Parameters: source - key of source vertex
// Pre-condition: key of the source vertex must be provided
// Post-condition: None
// Return: None
//========================================================
template <class D, class K>
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
