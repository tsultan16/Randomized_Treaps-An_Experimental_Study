#include <iostream>
#include "DynamicArray.h"
#include "DataGenerator.h"
using namespace std;

int main() {
    // create a data generator object
    DataGenerator dg;

    // create a dynamic array object
    DynamicArray arr;
    // perform some insertions
    for (int i = 0; i < 12; i++) {
        std::vector<int> insertion = dg.genInsertion();
        arr.insertItem(insertion[1], insertion[2]);
    }

    cout << "After insertions" << endl;
    cout << "Size: " << arr.getSize() << endl;
    cout << "Capacity: " << arr.getCapacity() << endl;
    // print out all elements in the array
    for (int i = 0; i < arr.getSize(); i++) {
        int* item = arr.get(i);
        cout << "Item# "  << i << ": " << item[0] << " " << item[1] << endl;
    }
    cout << endl;

    // perform some deletions
    for (int i = 0; i < 3; i++) {
        std::vector<int> deletion = dg.genDeletion();
        cout << "Deleting item with key: " << deletion[1] << endl;
        arr.deleteItem(deletion[1]);
    }

    cout << "\nAfter deletions" << endl;
    cout << "Size: " << arr.getSize() << endl;
    cout << "Capacity: " << arr.getCapacity() << endl;
    // print out all elements in the array
    for (int i = 0; i < arr.getSize(); i++) {
        int* item = arr.get(i);
        cout << "Item# "  << i << ": " << item[0] << " " << item[1] << endl;
    }
    cout << endl;

    // perform some searches
    for (int i = 0; i < 3; i++) {
        std::vector<int> search = dg.genSearch();
        cout << "Searching for item with key: " << search[1] << endl;
        int* item = arr.searchItem(search[1]);
        if (item != nullptr) {
            cout << "Item found: " << item[0] << " " << item[1] << endl;
        } else {
            cout << "Item not found" << endl;
        }
    }

}