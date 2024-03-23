"""
    Treap vs. Competitor experiments.
"""

import argparse
import random
import time
from a1_utils import DataGenerator, Treap, Competitor
import tqdm as tqdm
import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm

# get experiment number to run from command line arguments
parser = argparse.ArgumentParser(description="Treap vs. Competitor experiments.")
parser.add_argument('--experiment', type=int, choices=[1, 2, 3, 4], required=True,
                    help='The experiment number to run')
args = parser.parse_args()
experiment = args.experiment


############################################
# Experiment 1: Time vs Number of Insertions
############################################

if experiment == 1:

    print(f"\nPerforming experiment 1: Time vs Number of Insertions:\n")

    L_ins = [0.1e6, 0.2e6, 0.5e6, 0.8e6, 1e6]
    treap_times = []
    competitor_times = []

    for L in L_ins:
        # initialize data generator
        data_gen = DataGenerator()
        # initialize treap
        treap = Treap()
        # initialize competitor
        competitor = Competitor()
        # generate insertion sequence
        sigma = []
        for i in range(int(L)):
            sigma.append(data_gen.gen_insertion())

        # perform insertions on treap and time the sequence
        t1 = time.time()    
        for op, x in tqdm(sigma, desc="Processing treap operations", ncols=100):
            treap.perform_operation(op, x)
        t2 = time.time()
        treap_times.append(t2-t1)

        # perform insertions on competitor and time the sequence
        t1 = time.time()
        for op, x in tqdm(sigma, desc="Processing competitor operations", ncols=100):
            competitor.perform_operation(op, x)
        t2 = time.time()
        competitor_times.append(t2-t1)     
        print(f"\nL = {L:.1e}, Treap time: {treap_times[-1]:.2e} s, Competitor time: {competitor_times[-1]:.2e} s\n")  

    # plot time vs number of insertions
    """
    plt.plot(L_ins, treap_times, label='Treap', color='r')
    plt.plot(L_ins, competitor_times, label='Competitor', color='b')
    plt.xlabel('Number of Insertions')
    plt.ylabel('Time (s)')
    plt.legend()
    plt.show()
    """

###########################################
# Experiment 2: Time vs Deletion Percentage
###########################################

if experiment == 2:
    print(f"\nPerforming experiment 2: Time vs Deletion Percentage:\n")
    
    L = 1e6
    percent_del = [0.1, 0.5, 1, 5, 10]
    treap_times = []
    competitor_times = []

    for pdel in percent_del:
        # initialize data generator
        data_gen = DataGenerator()
        # initialize treap
        treap = Treap()
        # initialize competitor
        competitor = Competitor()
        # generate operation sequence
        sigma = []
        for i in range(int(L)):
            # generate uniform random number from [0,1]
            r = random.random()
            if r < pdel/100:
                sigma.append(data_gen.gen_deletion())
            else:    
                sigma.append(data_gen.gen_insertion())

        # perform operations on treap and time the sequence
        t1 = time.time()    
        for op, x in tqdm(sigma, desc="Processing treap operations", ncols=100):
            treap.perform_operation(op, x)
        t2 = time.time()
        treap_times.append(t2-t1)

        # perform operations on competitor and time the sequence
        t1 = time.time()
        for op, x in tqdm(sigma, desc="Processing competitor operations", ncols=100):
            competitor.perform_operation(op, x)
        t2 = time.time()
        competitor_times.append(t2-t1)   
        print(f"\ndel % = {pdel}, Treap time: {treap_times[-1]:.2e} s, Competitor time: {competitor_times[-1]:.2e} s\n")  


    # plot time vs number of insertions
    """
    plt.plot(percent_del, treap_times, label='Treap', color='r')
    plt.plot(percent_del, competitor_times, label='Competitor', color='b')
    plt.xlabel('% Deletions')
    plt.ylabel('Time (s)')
    plt.legend()
    """

#########################################
# Experiment 3: Time vs Search Percentage
#########################################
    
if experiment == 3:
    print(f"\nPerforming experiment 3: Time vs Search Percentage:\n")

    L = 1e6
    percent_sch = [0.1, 0.5, 1, 5, 10]
    treap_times = []
    competitor_times = []

    for psch in percent_sch:
        # initialize data generator
        data_gen = DataGenerator()
        # initialize treap
        treap = Treap()
        # initialize competitor
        competitor = Competitor()
        # generate operation sequence
        sigma = []
        for i in range(int(L)):
            # generate uniform random number from [0,1]
            r = random.random()
            if r < psch/100:
                sigma.append(data_gen.gen_search())
            else:    
                sigma.append(data_gen.gen_insertion())

        # perform operations on treap and time the sequence
        t1 = time.time()    
        for op, x in tqdm(sigma, desc="Processing treap operations"):
            treap.perform_operation(op, x)
        t2 = time.time()
        treap_times.append(t2-t1)

        # perform operations on competitor and time the sequence
        t1 = time.time()
        for op, x in tqdm(sigma, desc="Processing competitor operations"):
            competitor.perform_operation(op, x)
        t2 = time.time()
        competitor_times.append(t2-t1)   
        print(f"\nsearch % = {psch}, Treap time: {treap_times[-1]:.2e} s, Competitor time: {competitor_times[-1]:.2e} s\n")  

    # plot time vs number of insertions
    """
    plt.plot(percent_sch, treap_times, label='Treap', color='r')
    plt.plot(percent_sch, competitor_times, label='Competitor', color='b')
    plt.xlabel('% Searches')
    plt.ylabel('Time (s)')
    plt.legend()
    """


###################################################
# Experiment 4: Time vs Length of Mixed Op Sequence 
###################################################
    
if experiment == 4:   
    print(f"\nPerforming experiment 4: Time vs Length of Mixed Operation Sequence:\n")

    L_ins = [0.1e6, 0.2e6, 0.5e6, 0.8e6, 1e6]
    treap_times = []
    competitor_times = []

    for L in L_ins:
        # initialize data generator
        data_gen = DataGenerator()
        # initialize treap
        treap = Treap()
        # initialize competitor
        competitor = Competitor()
        # generate operation sequence
        sigma = []
        for i in range(int(L)):
            # generate uniform random number from [0,1]
            r = random.random()
            # with 5% probability generate deletion operation
            if r < 0.05:
                sigma.append(data_gen.gen_deletion())
            # with 5% probability generate search operation
            elif r < 0.1:
                sigma.append(data_gen.gen_search())    
            # with 90% probability generate insertion operation
            else:    
                sigma.append(data_gen.gen_insertion())

        # perform operations on treap and time the sequence
        t1 = time.time()    
        for op, x in tqdm(sigma, desc="Processing treap operations"):
            treap.perform_operation(op, x)
        t2 = time.time()
        treap_times.append(t2-t1)

        # perform operations on competitor and time the sequence
        t1 = time.time()
        for op, x in tqdm(sigma, desc="Processing competitor operations"):
            competitor.perform_operation(op, x)
        t2 = time.time()
        competitor_times.append(t2-t1)   
        print(f"\nL = {L:.1e}, Treap time: {treap_times[-1]:.2e} s, Competitor time: {competitor_times[-1]:.2e} s\n")  


# save experiment results to file 
np.savetxt('experiment_'+str(experiment)+"_times.txt", (treap_times, competitor_times))

# Read experiment results from file
#treap_times, competitor_times = np.loadtxt('experiment_'+str(experiment)+"_times.txt")




