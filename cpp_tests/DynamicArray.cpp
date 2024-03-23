#include "DynamicArray.h"
#include <stdexcept>
#include <cassert>

// constructor definition
DynamicArray::DynamicArray() : capacity(2), size(0) {
    // create a 2d array of size capacity x 2
    arr = new int*[capacity];
    for (int i=0; i<capacity; i++) {
        arr[i] = new int[2];
    }
}

// destructor definition
DynamicArray::~DynamicArray() {
    for (int i = 0; i < capacity; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

// get size of array
int DynamicArray::getSize() const {
    return size;
}

// get capacity of array
int DynamicArray::getCapacity() const {
    return capacity;
}

// get the element at a given index
int* DynamicArray::get(int idx) const {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[idx];
}

// double the array capacity
void DynamicArray::grow() {
    assert(size == capacity);
    // create new array of double the capacity
    capacity *= 2;
    int** arr_new = new int*[capacity];
    for (int i=0; i<capacity; i++) {
        arr_new[i] = new int[2];
    }
    // copy the old array to the new array
    for (int i=0; i<size; i++) {
        arr_new[i][0] = arr[i][0];
        arr_new[i][1] = arr[i][1];
    }
    // delete the old array
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    // assign the new array to the old array
    arr = arr_new;        
}

// halve the array capacity
void DynamicArray::shrink() {
    assert(size<capacity/4);
    // create new array of half the capacity
    capacity /= 2;
    int** arr_new = new int*[capacity];
    for (int i=0; i<capacity; i++) {
        arr_new[i] = new int[2];
    }
    // copy the old array to the new array
    for(int i =0; i < size; i++) {
        arr_new[i][0] = arr[i][0];
        arr_new[i][1] = arr[i][1];
    }
    // delete the old array
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    // assign the new array to the old array
    arr = arr_new;
}

// search for an item in the array
int* DynamicArray:: searchItem(int key_sch) const {
    // scan the array from beginning to end to find the given key (in case there are multiple keys, return the first one found)
    for (int i =0; i < size; i++) {
        if (arr[i][1] == key_sch) {
            return arr[i];
        } 
    }
    return nullptr;
}

void DynamicArray::insertItem(int id, int key) {
    // add the new item at the end of the array
    arr[size][0] = id;
    arr[size][1] = key;
    size++;
    // if array is full, double the capacity
    if (size == capacity) {
        grow();
    }
}

void DynamicArray::deleteItem(int key_del) {
    // search for item to be deleted
    int* item = searchItem(key_del);
    // if item is found, swap it with the last element and decrease size of array
    if (item != nullptr) {
        item[0] = arr[size-1][0];
        item[1] = arr[size-1][1];
        size--;
        // if array is less than 1/4 full, halve the capacity
        if (size < capacity/4) {
            shrink();
        }
    }
}
