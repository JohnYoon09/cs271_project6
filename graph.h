#ifndef GRAPH_H
#define GRAPH_H_H
#include <string>
#include <vector> 
#include <tuple>
using namespace std;
template <class D, class K> //D is data type and K is key type
class Graph{
    
    private: 
        struct Node{
            D data;
            K key;
            *Node pi;
            int dis;
        }
        *Node E[];
        K V[][];

    public:
        Graph(vector<D> data, vector<K> keys, vector<vector<K>> edges); //constructor

        *Node Get(K key);
        bool reachable(K u, K v);
        void bfs(K source);
        void print_path(K u, K v);
        string edge_class(K u, K v);
        void bfs_tree(K source);

}