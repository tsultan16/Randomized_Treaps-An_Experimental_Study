/*
    * COMP90077 - Assignment 1
    *
    * Treap.h
    *
    * This header file contains the interface for the Treap class.
    * 
    * Author: Tanzid Sultan (ID# 1430660)
*/

#ifndef TREAP_H
#define TREAP_H
#include <vector>
#include <random>
#include <fstream>
#include <string>

// Treap node struct
struct Node {
    int id;
    int key;
    float priority;
    Node* parent;
    Node* left;
    Node* right;
};


// Treap Interface
class Treap {
    private:
        Node* root;
        int size;
        std::mt19937 generator;  // pseudo-rng (Mersenne Twister)
        std::uniform_real_distribution<double> distribution;  // continuous uniform distribution
        static int SEED;
        Node* bstInsert(Node* new_node, int id, int key, float priority);
        void maintainHeapPropertyInsert(Node* node);
        void rotateToLeaf(Node* node);
        void leftRotation(Node* node);
        void rightRotation(Node* node);
        void destroyTreap(Node* node);
        void exportToDot(Node* node, std::ofstream& dotFile);

    public:
        Treap(); // constructor
        ~Treap(); // destructor
        int getSize() const;
        Node* getRoot() const;
        float generateRand();
        Node* searchItem(int key_sch) const;     
        void insertItem(int id, int key);
        void deleteItem(int key_del);
        void exportTree(const std::string& filename);
        int findTreeHeight() const;
        void performOperation(std::vector<int> op);  

};


#endif
