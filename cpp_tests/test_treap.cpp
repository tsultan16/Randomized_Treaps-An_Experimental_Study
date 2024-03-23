#include <iostream>
#include "Treap.h"
#include "DataGenerator.h"

using namespace std;


int main() {
    // create a data generator object
    DataGenerator dg;
    // create a treap object
    Treap treap;
    // perform some insertions
    for (int i = 0; i < 15; i++) {
        //std::vector<int> insertion = dg.genInsertion();
        //treap.insertItem(insertion[1], insertion[2]);
        int key = dg.generateRandInt(0, 200);
        treap.insertItem(i+1, key);
        cout << "Inserting item with key: " << key << endl;
    }

    cout << "After insertions, tree height = " << treap.findTreeHeight() << endl;
   
    // save to dot file for visualization
    // (to create png image of the tree run this from command line: 'dot -Tpng tree.dot -o tree.png')
    treap.exportTree("tree.dot");


}
