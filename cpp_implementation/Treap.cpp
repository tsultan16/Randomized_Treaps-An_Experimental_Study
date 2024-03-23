#include "Treap.h"
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <queue>
#include <iomanip>

// define rng seed static variable
int Treap::seed = 1234;  

// constructor definition (initialize size, root, generator, and distribution)
Treap::Treap(): size(0), root(nullptr), generator(seed), distribution(0,1) {
}

// destructor definition
Treap::~Treap() {
    destroyTreap(root);
}


// use BFS/postorder traversal to visit all nodes and deallocate the memory
void Treap::destroyTreap(Node* node) {
    if (node != nullptr) {
        destroyTreap(node->left);
        destroyTreap(node->right);
        delete node;
    }
}

int Treap::getSize() const {
    return size;
}

Node* Treap::getRoot() const {
    return root;
}

// draw random sample from continuous uniform distribution [a,b) 
float Treap::generateRand() {
    return distribution(generator);
}

Node* Treap::searchItem(int key_sch) const {
    // perform binary search starting from root (in case there are multiple nodes with this key, return the first one found)
    Node* current = root;
    while (current != nullptr) {
        if (key_sch < current->key) {
            current = current->left;
        } else if (key_sch > current->key) {
            current = current->right;
        } else {
            return current;
        }
    }
    return nullptr;
}

// recursive BST insertion
Node* Treap::bstInsert(Node* node, int id, int key, float priority) {
    if (key < node->key) {
        if (node->left == nullptr) {
            Node* new_node = new Node{id, key, priority, node, nullptr, nullptr};
            node->left = new_node;
            return new_node;
        } else {
            return bstInsert(node->left, id, key, priority);
        }
    } else if (key > node->key) {
        if (node->right == nullptr) {
            Node* new_node = new Node{id, key, priority, node, nullptr, nullptr};
            node->right = new_node;
            return new_node;
        } else {
            return bstInsert(node->right, id, key, priority);
        }
    } else {
        // if key already exists, use the id to break the tie
        if (id < node->id) {
            if (node->left == nullptr) {
                Node* new_node = new Node{id, key, priority, node, nullptr, nullptr};
                node->left = new_node;
                return new_node;
            } else {
                return bstInsert(node->left, id, key, priority);
            }
        } else {
            if (node->right == nullptr) {
                Node* new_node = new Node{id, key, priority, node, nullptr, nullptr};
                node->right = new_node;
                return new_node;
            } else {
                return bstInsert(node->right, id, key, priority);
            }
        }
    }        
}

void Treap::insertItem(int id, int key) {
    // sample a uniform random priority from [0,1)
    float priority = generateRand();
    
    if (root == nullptr) {
        root = new Node{id, key, priority, nullptr, nullptr, nullptr};
    
    } else {
        // starting from root, traverse down the tree to find the correct position to insert the new node
        Node* new_node = bstInsert(root, id, key, priority);   
        // fix heap property violation
        maintainHeapPropertyInsert(new_node);

    }    
    size++;
}


void Treap::deleteItem(int key_del) {
    // use binary search to find the node with given key (in case of multiple nodes with this key, we delete the first one found)
    Node* current = root;
    while (current != nullptr) {
        if (key_del < current->key) {
            current = current->left;
        } else if (key_del > current->key) {
            current = current->right;
        } else {
            // if key found, perform rotations to move the node to a leaf position
            rotateToLeaf(current);
            // now delete this leaf node from the tree
            if (current->parent != nullptr) {
                if (current->parent->left == current) {
                    current->parent->left = nullptr;
                } else {
                    current->parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }
            delete current;
            return;
        }
    }
    //std::cout << "Key " << key_del << " not found." << std::endl;
}


// restores heap property violations after an insert
void Treap::maintainHeapPropertyInsert(Node* node) {
    // check for heap property violation
    while ((node != root) and (node->priority < node->parent->priority)) {
        if (node == node->parent->left) {
            // perform right rotation if node is a left child
            rightRotation(node); 
        } else {
            // perform left rotation if node is a right child
            leftRotation(node);
        }
    }

}


void Treap::rotateToLeaf(Node* node) {
    // perform rotations to bring node down to a leaf position
    while ((node->left != nullptr) and (node->right != nullptr)) {
        if (node->left == nullptr) {
            // perform left rotation on right child if node only has a right child
            leftRotation(node->right);
        } else if (node->right == nullptr) {
            // perform right rotation on left child if node only has a left child
            rightRotation(node->left);
        } else {
            // if node has two children, then perform rotation on the child with the smaller priority
            if (node->left->priority < node->right->priority) {
                rightRotation(node->left);
            } else {
                leftRotation(node->right);
            }
        }
    }     
}


void Treap::leftRotation(Node* x) {
    /*
        Intially:
              y
            /   \
           A     x
                / \ 
               B   C

        After left rotation on node x:       
              x
            /  \
           y    C
          / \ 
         A   B

    */
    Node* y = x->parent;  // parent of x
    Node* g = y->parent;  // grandparent of x
    Node* B = x->left;
    // perform left rotation
    x->left = y;
    y->parent = x;
    y->right = B;
    if (B != nullptr) {
        B->parent = y;
    }
    x->parent = g;
    if (g != nullptr) {
        if (g->left == y) {
            g->left = x;
        } else {
            g->right = x;
        }
    } else {
        root = x;
    }
}


void Treap::rightRotation(Node* x) {
    /*
        Initially:    
              y
            /  \
           x    C
          / \ 
         A   B

        After right rotation on node x:
                x
              /   \
             A     y
                  / \ 
                 B   C
        
    */
    Node* y = x->parent;  // parent of x
    Node* g = y->parent;  // grandparent of x
    Node* B = x->right;
    // perform right rotation
    x->right = y;
    y->parent = x;
    y->left = B;
    if (B != nullptr) {
        B->parent = y;
    }
    x->parent = g;
    if (g != nullptr) {
        if (g->left == y) {
            g->left = x;
        } else {
            g->right = x;
        }
    } else {
        root = x;
    }
}



int Treap::findTreeHeight() const {
    // perform level order traversal (i.e. BFS) to find the height of the tree
    int height = 0;
    if (root == nullptr) {
        return height;
    } else {
        // intiialize BFS queue
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            // get number of nodes in current level
            int n = q.size();
            // create a queue to store nodes in next level
            std::queue<Node*> q_next;
            // visit all nodes in current level, i.e. pop them out of the queue and get their children
            for (int i = 0; i < n; i++) {
                Node* current = q.front();
                q.pop();
                if (current->left) {
                    q_next.push(current->left);
                }
                if (current->right) {
                    q_next.push(current->right);
                }
            }
            q = q_next;
            height++;
        }
        return height;
    }
}


//////////////////////////
// for tree visualization
//////////////////////////

void Treap::exportToDot(Node* node, std::ofstream& dotFile) {
    // internal nodes with only one child assigned a null child
    if (node->left) {
        dotFile << "\t\"" << node->key << ", " << std::fixed << std::setprecision(2) << node->priority << "\" -> \"" << node->left->key << ", " << std::fixed << std::setprecision(2) << node->left->priority << "\";\n";
        exportToDot(node->left, dotFile);
    } else {
        dotFile << "\t\"" << node->key << ", " << std::fixed << std::setprecision(2) << node->priority << "\" -> \"null_L_" << node->key << "\";\n";
    }

    if (node->right) {
        dotFile << "\t\"" << node->key << ", " << std::fixed << std::setprecision(2) << node->priority << "\" -> \"" << node->right->key << ", " << std::fixed << std::setprecision(2) << node->right->priority << "\";\n";
        exportToDot(node->right, dotFile);
    } else {
        dotFile << "\t\"" << node->key << ", " << std::fixed << std::setprecision(2) << node->priority << "\" -> \"null_R_" << node->key << "\";\n";
    }
}

void Treap::exportTree(const std::string& filename) {
    std::ofstream dotFile(filename);
    dotFile << "digraph Tree {\n";
    exportToDot(root, dotFile);
    dotFile << "}\n";
    dotFile.close();
}