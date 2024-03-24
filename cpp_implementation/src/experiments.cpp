/*
    * COMP90077 - Assignment 1
    *
    * experiments.cpp
    * 
    * This file contains the driver program for running the experiments for this assignment
    * The experiments are as follows:
    * 1. Time vs Number of Insertions
    * 2. Time vs Deletion Percentage
    * 3. Time vs Search Percentage
    * 4. Time vs Length of Mixed Operations Sequence
    * 
    * The results of the experiments are saved to text files in the same directory.
    *
    * Author: Tanzid Sultan (ID# 1430660)
*/

#include <iostream>
#include "Treap.h"
#include "DataGenerator.h"
#include "DynamicArray.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
using namespace std;

// number of sequence per experiment
const int NUM_SEQUENCES = 5;


// writes a vector to binary file
bool saveVectorToFile(const std::vector<std::vector<int>>& vec, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: could not open file " << filename << " for writing.\n";
        return false;
    }

    for (const auto& innerVec : vec) {
        int size = innerVec.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outFile.write(reinterpret_cast<const char*>(innerVec.data()), size * sizeof(int));
    }

    if (!outFile) {
        std::cerr << "Error: write to file " << filename << " failed.\n";
        return false;
    }

    outFile.close();
    return true;
}


// loads a vector from binary file
std::vector<std::vector<int>> loadVectorFromFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: could not open file " << filename << " for reading.\n";
        return {};
    }

    std::vector<std::vector<int>> vec;
    while (inFile) {
        int size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (inFile) {
            std::vector<int> innerVec(size);
            inFile.read(reinterpret_cast<char*>(innerVec.data()), size * sizeof(int));
            vec.push_back(std::move(innerVec));
        }
    }

    if (!inFile.eof()) {
        std::cerr << "Error: read from file " << filename << " failed.\n";
        return {};
    }

    inFile.close();
    return vec;
}

void genAndSaveOpSequences(int experiment) {

    cout << "Generating operation sequences for experiment " << experiment << "...\n";
    // specify parameters of the operation sequences for the given experiment
    std::vector<int> L;
    std::vector<double> del_percent;
    std::vector<double> sch_percent;
    switch (experiment) {
        case 1:
            L = {100000, 200000, 500000, 800000, 1000000};
            del_percent = {0.0, 0.0, 0.0, 0.0, 0.0};
            sch_percent = {0.0, 0.0, 0.0, 0.0, 0.0};
            // create subdirectories for storing files
            system("mkdir -p output/experiment_1");
            break;

        case 2:
            L = {1000000, 1000000, 1000000, 1000000, 1000000};
            del_percent = {0.1, 0.5, 1.0, 5.0, 10.0};
            sch_percent = {0.0, 0.0, 0.0, 0.0, 0.0};
            system("mkdir -p output/experiment_2");
            break;

        case 3:
            L = {1000000, 1000000, 1000000, 1000000, 1000000};
            del_percent = {0.0, 0.0, 0.0, 0.0, 0.0};
            sch_percent = {0.1, 0.5, 1.0, 5.0, 10.0};
            system("mkdir -p output/experiment_3");
            break;

        case 4:
            L =  {100000, 200000, 500000, 800000, 1000000};
            del_percent = {5.0, 5.0, 5.0, 5.0, 5.0};
            sch_percent = {5.0, 5.0, 5.0, 5.0, 5.0};
            system("mkdir -p output/experiment_4");
            break;

        default:
            cout << "Invalid experiment number.\n";
            return;
    }   

    // initialize data generator
    DataGenerator dg;

    // generate the 5 operation sequences and save each of them to binary file
    for (size_t i = 0; i < L.size(); i++) {
        // generate insertion sequence
        std::vector<std::vector<int>> sigma = dg.genOpSequence(L[i], del_percent[i], sch_percent[i]);
        // save to binary file
        string filename = "output/experiment_" + to_string(experiment) + "/sigma_" + to_string(i+1) + ".bin";
        if (!saveVectorToFile(sigma, filename)) {
            cerr << "Error: could not save operation sequence to file.\n";
            return;
        }
        cout << "Operation sequence saved to file: " << filename << endl;
    }
}

// perform the given sequence of operations on the treap and competitor and measure the corresponding running times
std::vector<double> performOperationSequence(Treap& treap, DynamicArray& competitor, std::vector<std::vector<int>> sigma) {
    std::vector<double> times(2);
    // perform operation sequence on treap and measure execution time
    auto start = std::chrono::high_resolution_clock::now();   
    for (size_t j = 0; j < sigma.size(); j++) {
        if (sigma[j][0] == 1) {
            treap.insertItem(sigma[j][1], sigma[j][2]);
        } else if (sigma[j][0] == 2) {
            treap.deleteItem(sigma[j][1]);
        } else {
            treap.searchItem(sigma[j][1]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    // get treap execution time in seconds
    std::chrono::duration<double> duration = end - start;
    times[0] = duration.count();
    cout << "Treap time = " << times[0] << " seconds" << endl;

    // perform operation sequence on competitor and measure execution time
    start = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < sigma.size(); j++) {
        if (sigma[j][0] == 1) {
            competitor.insertItem(sigma[j][1], sigma[j][2]);
        } else if (sigma[j][0] == 2) {
            competitor.deleteItem(sigma[j][1]);
        } else {
            competitor.searchItem(sigma[j][1]);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    // get competitor execution time in seconds
    duration = end - start;
    times[1] = duration.count();
    cout << "Competitor time = " << times[1] << " seconds" << endl;

    return times;
}

// run all 5 operation sequences for the given experiment
void runExperiment(int experiment) {
    std::vector<double> treap_times = {0.0, 0.0, 0.0, 0.0, 0.0};
    std::vector<double> competitor_times = {0.0, 0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < NUM_SEQUENCES; i++) {
        cout << "\nOperation sequence --> sigma_" << i+1 << endl;
        // load operation sequence from file
        std::vector<std::vector<int>> sigma = loadVectorFromFile("output/experiment_" + to_string(experiment) + "/sigma_" + to_string(i+1) + ".bin");
        // initialize treap and competitor
        Treap treap;
        DynamicArray competitor;
        // perform operation sequence on treap and competitor, measure execution time
        std::vector<double> times = performOperationSequence(treap, competitor, sigma);
        treap_times[i] = times[0];
        competitor_times[i] = times[1];
    }
    
    // save the results to a file
    ofstream file("output/experiment_" + to_string(experiment) + "/running_times_exp_" + to_string(experiment) +".txt");
    if (file.is_open()) {
        file << "Treap Time, Competitor Time\n";

        for (int i = 0; i < NUM_SEQUENCES; i++) {
            file << treap_times[i] << ", " << competitor_times[i] << "\n";
        }
        file.close();
    } else {
        cerr << "Error: could not open file for writing.\n";
    }
}


int main(int argc, char** argv) {

    // get which experiment number to run from command line arguments
    if (argc != 2) {
        cerr << "Experiment option usage: ./driver <experiment_number>\n";
        return 1;
    }
    int experiment = atoi(argv[1]);
    if (experiment < 1 || experiment > 4) {
        cerr << "Error: experiment number must be between 1 and 4.\n";
        return 1;
    }

    // generate all 5 operation sequences for the experiment and and save them to file
    genAndSaveOpSequences(experiment);

    switch (experiment) {
        case 1:
            cout << "\nPerforming experiment 1: Time vs Number of Insertions:" << endl;
            break;
        case 2:
            cout << "\nPerforming experiment 2: Time vs Deletion Percentage:" << endl;
            break;       
        case 3:
            cout << "\nPerforming experiment 3: Time vs Search Percentage:" << endl;
            break;
        case 4:
            cout << "\nPerforming experiment 4: Time vs Length of Mixed Operations Sequence:" << endl;
            break;
    }

    // run the experiment
    runExperiment(experiment);
 
    return 0; // success!
}