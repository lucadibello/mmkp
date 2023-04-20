//
// Created by mattia on 20/04/23.
//
#include "LocalSearch.h"
#include <iostream>

void LocalSearch::compute(Data *instance) {
    std::cout << "----------------- Local search solution -----------------" << std::endl;
    srand(time(nullptr));

    for (long unsigned int i = 0; i < instance->capacities.size(); i++) {
        std::cout << instance->capacities[i] << "_";
    }
    std::cout << std::endl;

    while (!stopCondition()) {
        std::vector<int> neighborhood = computeNeighborhood(instance);

        // Update capacities
        std::vector<int> neighborhoodCapacities = instance->capacities;
        for (long unsigned int i = 0; i < neighborhood.size(); i++) {
            if (neighborhood[i] != instance->solution[i]) {
                for (int j = 0; j < instance->nresources; j++) {
                    neighborhoodCapacities[j] -= instance->weights[i][neighborhood[i] * instance->nresources + j];
                    neighborhoodCapacities[j] += instance->weights[i][instance->solution[i] * instance->nresources + j];
                }
            }
        }

        // Update solution
        instance->solution = neighborhood;
        instance->capacities = neighborhoodCapacities;
        int totValue = 0;
        for (long unsigned int i = 0; i < instance->solution.size(); i++) {
            totValue += instance->values[i][instance->solution[i]];
        }
        std::cout << "Solution new value: " << totValue << std::endl;
    }

    for (unsigned long i = 0; i < instance->capacities.size(); i++)
        std::cout << instance->capacities[i] << "_";
    std::cout << std::endl;
}

int LocalSearch::m_iterations = 0;

bool LocalSearch::stopCondition() {
    return m_iterations++ > 20000;
}

std::vector<int> LocalSearch::computeNeighborhood(Data *instance) {
    std::vector<int> neighborhood = instance->solution;

    // Choose two different target classes
    int firstTargetClass = rand() % instance->nclasses;
    int secondTargetClass = rand() % instance->nclasses;
    if(firstTargetClass == secondTargetClass)
        secondTargetClass = (firstTargetClass + 1) % instance->nclasses;

    // Items for the first target class
    int itemsFirstClass = instance->nitems[firstTargetClass];

    for (int i = 0; i < itemsFirstClass; i++) {
        // Skip item if it's already in the solution
        if (i == instance->solution[firstTargetClass])
            continue;

        std::vector<int> neighborhoodCapacities = instance->capacities;
        // Update capacities
        for (int j = 0; j < instance->nresources; j++) {
            neighborhoodCapacities[j] -= instance->weights[firstTargetClass][i * instance->nresources + j];
            neighborhoodCapacities[j] += instance->weights[firstTargetClass][
                    instance->solution[firstTargetClass] * instance->nresources + j];
        }
        // Check if neighborhood is feasible
        bool feasible = true;
        for (long unsigned int c = 0; c < neighborhoodCapacities.size(); c++) {
            if (neighborhoodCapacities[c] < 0)
                feasible = false;
        }

        // Update neighborhood
        if (feasible) {
            if (instance->values[firstTargetClass][i] > instance->values[firstTargetClass][instance->solution[firstTargetClass]]) {
                neighborhood[firstTargetClass] = i;
                break;
            }
        }
    }

    return neighborhood;
}
