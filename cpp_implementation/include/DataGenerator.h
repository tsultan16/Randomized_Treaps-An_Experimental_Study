/*
    * COMP90077 - Assignment 1
    *
    * DataGenerator.h
    *
    * This header file contains the interface for the DataGenerator class.
    * 
    * Author: Tanzid Sultan (ID# 1430660)
*/

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include <random>

// DataGenerator Interface
class DataGenerator {
    private:
        int id_next;
        std::vector<std::vector<int>> data;                   // vector for storing all the generated data
        std::mt19937 generator;                               // pseudo-rng (Mersenne Twister)
        std::uniform_real_distribution<double> distribution;  // continuous uniform distribution
        static int SEED;
        static float ZERO;

        int generateRandInt(int a, int b);
        float generateRand();

    public:
        DataGenerator();  // constructor
        ~DataGenerator(); // destructor
 
        std::vector<int> genElement();
        std::vector<int> genInsertion();
        std::vector<int> genDeletion();
        std::vector<int> genSearch();
        std::vector<std::vector<int>> genOpSequence(int L, float del_percent, float sch_percent);
};

#endif