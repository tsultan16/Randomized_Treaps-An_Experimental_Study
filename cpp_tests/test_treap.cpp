#include <iostream>
#include "Treap.h"
#include "DataGenerator.h"

using namespace std;


int main() {
    // create a data generator object
    DataGenerator dg;
    // create a treap object
    Treap treap;
    
    /*
    // perform some insertions
    for (int i = 0; i < 30; i++) {
        //std::vector<int> insertion = dg.genInsertion();
        //treap.insertItem(insertion[1], insertion[2]);
        int key = dg.generateRandInt(0, 200);
        treap.insertItem(i+1, key);
        cout << "Inserting item with key: " << key << endl;
    }
    cout << "After insertions, tree height = " << treap.findTreeHeight() << endl;
   
    // perform some searches
    for (int i = 0; i < 10; i++) {
        int key = dg.generateRandInt(0, 200);
        cout << "Searching for item with key: " << key << endl;
        Node* item = treap.searchItem(key);
        if (item != nullptr) {
            cout << "Item found: " << item->id << " " << item->key << endl;
        } else {
            cout << "Item not found" << endl;
        }
    }

    // perform some deletions
    std::vector<int> deletionKeys;
    for (int i = 0; i < 10; i++) {
        int key = dg.generateRandInt(0, 200);
        cout << "Deleting item with key: " << key << endl;
        treap.deleteItem(key);
        deletionKeys.push_back(key);
    }

    // perform searches on the deleted keys
    for (int i = 0; i < 10; i++) {
        cout << "Searching for item with key: " << deletionKeys[i] << endl;
        Node* item = treap.searchItem(deletionKeys[i]);
        if (item != nullptr) {
            cout << "Item found: " << item->id << " " << item->key << endl;
        } else {
            cout << "Item not found" << endl;
        }
    }
    */

    // perform long sequence of mixed operations
    for (int i = 0; i < 100000; i++) {
        int op = dg.generateRandInt(1, 3);
        //cout << "i = " << i << ", op = " << op << endl;
        if (op == 1) {
            std::vector<int> insertion = dg.genInsertion();
            //cout << "Inserting item with key: " << insertion[2] << endl;
            treap.insertItem(insertion[1], insertion[2]);
        } else if (op == 2) {
            std::vector<int> deletion = dg.genDeletion();
            //cout << "Deleting item with key: " << deletion[1] << endl;
            treap.deleteItem(deletion[1]);
        } else {
            std::vector<int> search = dg.genSearch();
            //cout << "Searching for item with key: " << search[1] << endl;
            Node* item = treap.searchItem(search[1]);
            if (item != nullptr) {
                //cout << "Item found: " << item[0] << " " << item[1] << endl;
            } else {
                //cout << "Item not found" << endl;
            }
        }
    }
    cout << "After mixed operations, treap size: " << treap.getSize() << ", treap height: " << treap.findTreeHeight() << endl;
    

    // save to dot file for visualization
    // (to create png image of the tree run this from command line: 'dot -Tpng tree.dot -o tree.png')
    //treap.exportTree("tree.dot");


}
