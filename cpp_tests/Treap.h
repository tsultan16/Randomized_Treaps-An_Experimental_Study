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
        static int seed;
        float generateRand();
        Node* bstInsert(Node* new_node, int id, int key, float priority);
        void maintainHeapPropertyInsert(Node* node);
        void rotateToLeaf(Node* node);
        void leftRotation(Node* node);
        void rightRotation(Node* node);
        void exportToDot(Node* node, std::ofstream& dotFile);

    public:
        Treap(); // constructor
        ~Treap(); // destructor
        Node* getRoot() const;
        Node* searchItem(int key_sch) const;     
        void insertItem(int id, int key);
        void deleteItem(int key_del);
        void exportTree(const std::string& filename);
        int findTreeHeight() const;

};


#endif
