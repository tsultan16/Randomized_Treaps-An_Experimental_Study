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
using namespace std;

int main(int argc, char** argv) {

    // get which experiment number to run from command line arguments
    if (argc != 2) {
        cerr << "Experiment option usage: ./experiments <experiment_number>\n";
        return 1;
    }
    int experiment = atoi(argv[1]);
    if (experiment < 1 || experiment > 4) {
        cerr << "Error: experiment number must be between 1 and 4.\n";
        return 1;
    }

    ////////////////
    // Experiment 1
    ////////////////
    if (experiment == 1) {
        cout << "\nPerforming experiment 1: Time vs Number of Insertions:" << endl;
        int L_ins[] = {100000, 200000, 500000, 800000, 1000000};
        double treap_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double competitor_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};

        for (int i = 0; i < 5; i++) {
            cout << "\nL = " << L_ins[i] << endl;

            // initialize data generator, treap, and competitor
            DataGenerator dg;
            Treap treap;
            DynamicArray competitor;

            // generate insertion sequence
            std::vector<std::vector<int>> sigma;
            for(int j = 0; j < L_ins[i]; j++) {
                std::vector<int> insertion = dg.genInsertion();
                sigma.push_back(insertion);
            }

            // perform operation sequence on treap and measure execution time
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L_ins[i]; j++) {
                treap.insertItem(sigma[j][1], sigma[j][2]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            std::chrono::duration<double> duration = end - start;
            treap_times[i] = duration.count();
            cout << "Treap time = " << treap_times[i] << " seconds" << endl;

            // perform operation sequence on competitor and measure execution time
            start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L_ins[i]; j++) {
                competitor.insertItem(sigma[j][1], sigma[j][2]);
            }
            end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            duration = end - start;
            competitor_times[i] = duration.count();
            cout << "Competitor time = " << competitor_times[i] << " seconds" << endl;
        }

        // save the results to a file
        ofstream file("experiment1.txt");
        if (file.is_open()) {
            file << "L_ins, Treap Time, Competitor Time\n";

            for (int i = 0; i < 5; i++) {
                file << L_ins[i] << ", "<< treap_times[i] << ", " << competitor_times[i] << "\n";
            }
            file.close();
        } else {
            cerr << "Error: could not open file for writing.\n";
            return 1;
        }

    }    
 
    ////////////////
    // Experiment 2
    ////////////////
    if (experiment == 2) {
        cout << "\nPerforming experiment 2: Time vs Deletion Percentage:" << endl;
        int L = 1000000;
        double del_percent[] = {0.1, 0.5, 1.0, 5.0, 10.0};
        double treap_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double competitor_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};

        for (int i = 0; i < 5; i++) {
            cout << "\ndel % = " << del_percent[i] << endl;

            // initialize data generator, treap, and competitor
            DataGenerator dg;
            Treap treap;
            DynamicArray competitor;

            // generate operations sequence
            std::vector<std::vector<int>> sigma;
            for(int j = 0; j < L; j++) {
                // sample a uniform random priority from [0,1)
                float r = treap.generateRand();
                // generate a deletion operation with probability del_percent[i]
                if (r < del_percent[i]/100.0) {
                    std::vector<int> deletion = dg.genDeletion();
                    sigma.push_back(deletion);
                } else {
                    std::vector<int> insertion = dg.genInsertion();
                    sigma.push_back(insertion);
                }
            }

            // perform operation sequence on treap and measure execution time
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L; j++) {
                if (sigma[j][0] == 1) {
                    treap.insertItem(sigma[j][1], sigma[j][2]);
                } else {
                    treap.deleteItem(sigma[j][1]);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            std::chrono::duration<double> duration = end - start;
            treap_times[i] = duration.count();
            cout << "Treap time = " << treap_times[i] << " seconds" << endl;

            // perform operation sequence on competitor and measure execution time
            start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L; j++) {
                if (sigma[j][0] == 1) {
                    competitor.insertItem(sigma[j][1], sigma[j][2]);
                } else {
                    competitor.deleteItem(sigma[j][1]);
                }
            }
            end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            duration = end - start;
            competitor_times[i] = duration.count();
            cout << "Competitor time = " << competitor_times[i] << " seconds" << endl;
        }

        // save the results to a file
        ofstream file("experiment2.txt");
        if (file.is_open()) {
            file << "del_%, Treap Time, Competitor Time\n";

            for (int i = 0; i < 5; i++) {
                file << del_percent[i] << ", "<< treap_times[i] << ", " << competitor_times[i] << "\n";
            }
            file.close();
        } else {
            cerr << "Error: could not open file for writing.\n";
            return 1;
        }

    }  

    ////////////////
    // Experiment 3
    ////////////////
    if (experiment == 3) {
        cout << "\nPerforming experiment 3: Time vs Search Percentage:" << endl;
        int L = 1000000;
        double sch_percent[] = {0.1, 0.5, 1.0, 5.0, 10.0};
        double treap_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double competitor_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};

        for (int i = 0; i < 5; i++) {
            cout << "\nsch % = " << sch_percent[i] << endl;

            // initialize data generator, treap, and competitor
            DataGenerator dg;
            Treap treap;
            DynamicArray competitor;

            // generate operations sequence
            std::vector<std::vector<int>> sigma;
            for(int j = 0; j < L; j++) {
                // sample a uniform random priority from [0,1)
                float r = treap.generateRand();
                // generate a search operation with probability sch_percent[i]
                if (r < sch_percent[i]/100.0) {
                    std::vector<int> search = dg.genSearch();
                    sigma.push_back(search);
                } else {
                    std::vector<int> insertion = dg.genInsertion();
                    sigma.push_back(insertion);
                }
            }

            // perform operation sequence on treap and measure execution time
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L; j++) {
                if (sigma[j][0] == 1) {
                    treap.insertItem(sigma[j][1], sigma[j][2]);
                } else {
                    treap.searchItem(sigma[j][1]);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            std::chrono::duration<double> duration = end - start;
            treap_times[i] = duration.count();
            cout << "Treap time = " << treap_times[i] << " seconds" << endl;

            // perform operation sequence on competitor and measure execution time
            start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L; j++) {
                if (sigma[j][0] == 1) {
                    competitor.insertItem(sigma[j][1], sigma[j][2]);
                } else {
                    competitor.searchItem(sigma[j][1]);
                }
            }
            end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            duration = end - start;
            competitor_times[i] = duration.count();
            cout << "Competitor time = " << competitor_times[i] << " seconds" << endl;
        }

        // save the results to a file
        ofstream file("experiment3.txt");
        if (file.is_open()) {
            file << "sch_%, Treap Time, Competitor Time\n";

            for (int i = 0; i < 5; i++) {
                file << sch_percent[i] << ", "<< treap_times[i] << ", " << competitor_times[i] << "\n";
            }
            file.close();
        } else {
            cerr << "Error: could not open file for writing.\n";
            return 1;
        }
    }  

    ////////////////
    // Experiment 4
    //////////////// 
    if (experiment == 4) {
        cout << "\nPerforming experiment 4: Time vs Length of Mixed Operations Sequence:" << endl;
        int L_ops[] = {100000, 200000, 500000, 800000, 1000000};
        double treap_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double competitor_times [] = {0.0, 0.0, 0.0, 0.0, 0.0};

        for (int i = 0; i < 5; i++) {
            cout << "\nL = " << L_ops[i] << endl;

            // initialize data generator, treap, and competitor
            DataGenerator dg;
            Treap treap;
            DynamicArray competitor;

            // generate operations sequence
            std::vector<std::vector<int>> sigma;
            for(int j = 0; j < L_ops[i]; j++) {
                // sample a uniform random priority from [0,1)
                float r = treap.generateRand();
                if (r < 0.05) {
                    // with 5% probability generate deletion operation
                    std::vector<int> deletion = dg.genDeletion();
                    sigma.push_back(deletion);
                } else if (r < 0.1) {
                    // with 5% probability generate search operation
                    std::vector<int> search = dg.genSearch();
                    sigma.push_back(search);
                } else {
                    // with 90% probability generate insertion operation
                    std::vector<int> insertion = dg.genInsertion();
                    sigma.push_back(insertion);
                }
            }

            // perform operation sequence on treap and measure execution time
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L_ops[i]; j++) {
                if (sigma[j][0] == 1) {
                    treap.insertItem(sigma[j][1], sigma[j][2]);
                } else if (sigma[j][0] == 2) {
                    treap.deleteItem(sigma[j][1]);
                } else {
                    treap.searchItem(sigma[j][1]);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            std::chrono::duration<double> duration = end - start;
            treap_times[i] = duration.count();
            cout << "Treap time = " << treap_times[i] << " seconds" << endl;

            // perform operation sequence on competitor and measure execution time
            start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < L_ops[i]; j++) {
                if (sigma[j][0] == 1) {
                    competitor.insertItem(sigma[j][1], sigma[j][2]);
                } 
                else if (sigma[j][0] == 2) {
                    competitor.deleteItem(sigma[j][1]);
                } else {
                    competitor.searchItem(sigma[j][1]);
                }
            }
            end = std::chrono::high_resolution_clock::now();
            // get execution time in seconds
            duration = end - start;
            competitor_times[i] = duration.count();
            cout << "Competitor time = " << competitor_times[i] << " seconds" << endl;
        }

        // save the results to a file
        ofstream file("experiment4.txt");
        if (file.is_open()) {
            file << "L_ops, Treap Time, Competitor Time\n";

            for (int i = 0; i < 5; i++) {
                file << L_ops[i] << ", "<< treap_times[i] << ", " << competitor_times[i] << "\n";
            }
            file.close();
        } else {
            cerr << "Error: could not open file for writing.\n";
            return 1;
        }
    }  

    return 0; // success!
}