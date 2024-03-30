/*
    * COMP90077 - Assignment 1
    *
    * DataGenerator.cpp
    *
    * This file contains the implementation of the DataGenerator class.
    * 
    * Author: Tanzid Sultan (ID# 1430660)
*/

#include "DataGenerator.h"
#include <stdexcept>
#include <cassert>
#include <iostream>

// define rng seed static variable
int DataGenerator::SEED = 1234;  
//define zero static variable
float DataGenerator::ZERO = 1e-9;

// constructor definition 
DataGenerator::DataGenerator(): id_next(1), generator(SEED), distribution(0,1) {
}

// destructor definition
DataGenerator::~DataGenerator() {
}

// draw random sample from continuous uniform distribution [0,1) 
float DataGenerator::generateRand() {
    return distribution(generator);
}

// draw random sample from uniform distribution [a,b] 
int DataGenerator::generateRandInt(int a, int b) {
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

// generate a new element
std::vector<int> DataGenerator::genElement() {
    std::vector<int> x(2);
    x[0] = id_next;
    // sample a uniform random integer key from [0,10^7]
    x[1] = generateRandInt(0, 1e7);
    id_next++;
    // keep a copy of the generated data (need this for genDeletion operation)
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
    // get the key associated with the element that had been generated with this id
    int key_del = data[idx-1][1];
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

// generate operation sequence of specified length with specified probabilities for each operation
std::vector<std::vector<int>> DataGenerator::genOpSequence(int L, float del_percent, float sch_percent) {
    assert(L > 0);   
    assert(del_percent >= 0 and del_percent <= 100);
    assert(sch_percent >= 0 and sch_percent <= 100);

    std::vector<std::vector<int>> sigma;
    for(int j = 0; j < L; j++) {
        std::vector<int> op;
        if ((del_percent <= ZERO) and (sch_percent <= ZERO)) {
            // with 100% probability generate insertion operation
            op = genInsertion();

        } else if ((sch_percent <= ZERO) and (del_percent > ZERO)) {
            float r = generateRand();
            if (r < del_percent/100.0) {
                // with del_percent % probability generate deletion operation
                op = genDeletion();
            } else {
                // with 100-del_percent % probability generate insertion operation
                op = genInsertion();
            }
        
        } else if ((del_percent <= ZERO) and (sch_percent > ZERO)) {
            float r = generateRand();
            if (r < sch_percent/100.0) {
                // with sch_percent % probability generate search operation
                op = genSearch();
            } else {
                // with 100-del_percent % probability generate insertion operation
                op = genInsertion();
            }
        
        } else {
            // sample a uniform random priority from [0,1)
            float r = generateRand();
            if (r < del_percent/100.0) {
                // with del_percent % probability generate deletion operation
                op = genDeletion();
            } else if (r < (del_percent/100.0 + sch_percent/100.0)) {
                // with sch_percent % probability generate search operation
                op = genSearch();
            } else {
                // with 100-del_percent-sch_percent % probability generate insertion operation
                op = genInsertion();
            }
        }
        sigma.push_back(op);
    }
    return sigma;
}