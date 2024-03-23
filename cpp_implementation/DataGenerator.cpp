#include "DataGenerator.h"
#include <stdexcept>
#include <cassert>
#include <iostream>

// define rng seed static variable
int DataGenerator::seed = 1234;  

// constructor definition 
DataGenerator::DataGenerator(): id_next(1), generator(seed) {
}

// destructor definition
DataGenerator::~DataGenerator() {
}

// draw random sample from uniform distribution [a,b] 
int DataGenerator::generateRandInt(int a, int b) {
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}


std::vector<int> DataGenerator::genElement() {
    std::vector<int> x(2);
    x[0] = id_next;
    // sample a uniform random integer key from [0,10^7]
    x[1] = generateRandInt(0, 1e7);
    id_next++;
    data.push_back(x);
    return x;
}


// generate an insertion operation
std::vector<int> DataGenerator::genInsertion() {
    std::vector<int> insertion(3);
    insertion[0] = 1; // insertion operation
    // generate new element: x = [id, key]
    std::vector<int> x = genElement();
    insertion[1] = x[0]; // id
    insertion[2] = x[1]; // key
    return insertion;
}

// generate a deletion operation
std::vector<int> DataGenerator::genDeletion() {
    std::vector<int> deletion(2);
    deletion[0] = 2; // deletion operation
    // sample a uniform random integer id from [1,id_next-1]
    int idx = generateRandInt(1, id_next-1);
    //std::cout << "deletion idx = " << idx << std::endl;
    // get the key associated with this id
    int key_del = data[idx-1][1];
    //std::cout << "deleting key = " << key_del << std::endl;
    deletion[1] = key_del; 
    return deletion;
}

// generate a search operation
std::vector<int> DataGenerator::genSearch() {
    std::vector<int> search(2);
    search[0] = 3; // search operation
    // sample a uniform random integer key from [0,10^7]
    int key_sch = generateRandInt(0, 1e7);
    search[1] = key_sch;
    return search;
}


