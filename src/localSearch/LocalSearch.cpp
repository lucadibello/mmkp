//
// Created by mattia on 20/04/23.
//
#include "LocalSearch.h"
#include <iostream>

void LocalSearch::compute(Data * instance) {
    std::cout << "----------------- Local search solution -----------------" << std::endl;

    for(long unsigned int i = 0; i < instance->capacities.size(); i ++) {
        std::cout << instance->capacities[i] << "_";
    }
    std::cout << std::endl;

    while(!stopCondition()) {
        std::vector<int> neighborhood = computeNeighborhood(instance);

        // Check if neighborhood is feasible
        std::vector<int> neighborhoodCapacities = instance->capacities;
        for (long unsigned int i = 0; i < neighborhood.size(); i++) {
            if (neighborhood[i] != instance->solution[i]) {
                // Update capacities
                for (int j = 0; j < instance->nresources; j++) {
                    neighborhoodCapacities[j] -= instance->weights[i][neighborhood[i] * instance->nresources + j];
                    neighborhoodCapacities[j] += instance->weights[i][instance->solution[i] * instance->nresources + j];
                }
            }
        }
        bool feasible = true;
        // Print neighborhood capacities
        for (long unsigned int i = 0; i < neighborhoodCapacities.size(); i++) {
            std::cout << neighborhoodCapacities[i] << " ";
            if(neighborhoodCapacities[i] < 0)
                feasible = false;
        }
        std::cout << std::endl;

        if(feasible) {
            // Update solution
            instance->solution = neighborhood;
            instance->capacities = neighborhoodCapacities;
            int totValue = 0;
            for (long unsigned int i = 0; i < instance->solution.size(); i++) {
                totValue += instance->values[i][instance->solution[i]];
            }
            std::cout << "Solution new value: " << totValue << std::endl;
        }
    }
}

int LocalSearch::m_iterations = 0;
bool LocalSearch::stopCondition() {
    return m_iterations ++ > 1000;
}

std::vector<int> LocalSearch::computeNeighborhood(Data* instance) {
    std::vector<int> neighborhood = instance->solution;
    int targetClass = m_iterations % instance->nclasses;

    // Items for the target class
    int items = instance->nitems[targetClass];

    int max = instance->values[targetClass][0];
    int maxIndex = 0;
    for(int i = 1; i < items; i++) {
        if(instance->values[targetClass][i] > max) {
            max = instance->values[targetClass][i];
            maxIndex = i;
        }
    }

    neighborhood[targetClass] = maxIndex;
    return neighborhood;
}
