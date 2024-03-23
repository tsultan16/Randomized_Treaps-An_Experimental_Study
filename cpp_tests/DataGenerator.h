#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include <random>

// data generator interface
class DataGenerator {
    private:
        int id_next;
        std::vector<std::vector<int>> data; // vector for storing all the generated data
        std::mt19937 generator;  // pseudo-rng (Mersenne Twister)
        static int seed;

    public:
        DataGenerator(); // constructor
        ~DataGenerator(); // destructor
 
        int generateRandInt(int a, int b);
        std::vector<int> genElement();
        std::vector<int> genInsertion();
        std::vector<int> genDeletion();
        std::vector<int> genSearch();

};

#endif