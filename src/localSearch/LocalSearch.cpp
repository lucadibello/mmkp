//
// Created by mattia on 20/04/23.
//
#include "LocalSearch.h"

/**
 * Compute the local search algorithm for the Multi-Objective Multi-Dimensional Knapsack Problem
 * Interrupt the algorithm when a SIGINT is received
 * @param instance The instance of the Multi-Objective Multi-Dimensional Knapsack Problem
 */
void LocalSearch::compute(Data *instance) {
    // Initialize random seed
    srand(time(nullptr));

    // Continue until stop condition is reached
    while (!stopCondition()) {
        std::vector<int> neighbour = computeNeighbour(instance);

        // Update capacities
        std::vector<int> neighborCapacities = instance->capacities;
        for (long unsigned int i = 0; i < neighbour.size(); i++) {
            // Update only classes that have changed
            if (neighbour[i] != instance->solution[i]) {
                for (int j = 0; j < instance->nresources; j++) {
                    neighborCapacities[j] -= instance->weights[i][neighbour[i] * instance->nresources + j];
                    neighborCapacities[j] += instance->weights[i][instance->solution[i] * instance->nresources + j];
                }
            }
        }

        // Update solution
        instance->solution = neighbour;
        instance->capacities = neighborCapacities;
    }
}

/**
 * Check if the stop condition is reached
 * @return Always return false
 */
bool LocalSearch::stopCondition() {
    return false;
}

/**
 * Compute a neighbour of the current solution
 * @param instance The instance of the Multi-Objective Multi-Dimensional Knapsack Problem
 * @return A std::vector<int> containing the new solution
 */
std::vector<int> LocalSearch::computeNeighbour(Data *instance) {
    std::vector<int> neighbour = instance->solution;

    // Choose two different target classes
    int firstTargetClass = rand() % instance->nclasses;
    int secondTargetClass = rand() % instance->nclasses;
    if(firstTargetClass == secondTargetClass)
        secondTargetClass = (firstTargetClass + 1) % instance->nclasses;

    // Pick random items for the two target classes
    int itemFirstClass = rand() % instance->nitems[firstTargetClass];
    int itemSecondClass = rand() % instance->nitems[secondTargetClass];

    std::vector<int> neighbourCapacities = instance->capacities;
    // Update capacities
    for (int j = 0; j < instance->nresources; j++) {
        neighbourCapacities[j] -= instance->weights[firstTargetClass][itemFirstClass * instance->nresources + j];
        neighbourCapacities[j] += instance->weights[firstTargetClass][instance->solution[firstTargetClass] * instance->nresources + j];
        neighbourCapacities[j] -= instance->weights[secondTargetClass][itemSecondClass * instance->nresources + j];
        neighbourCapacities[j] += instance->weights[secondTargetClass][instance->solution[secondTargetClass] * instance->nresources + j];
    }
    // Check if neighbour is feasible
    bool feasible = true;
    for (long unsigned int c = 0; c < neighbourCapacities.size(); c++) {
        if (neighbourCapacities[c] < 0)
            feasible = false;
    }

    // Update neighbour is solution is feasible AND better
    if (feasible &&
                instance->values[firstTargetClass][itemFirstClass] + instance->values[secondTargetClass][itemSecondClass] >
                instance->values[firstTargetClass][instance->solution[firstTargetClass]] + instance->values[secondTargetClass][instance->solution[secondTargetClass]]) {
        neighbour[firstTargetClass] = itemFirstClass;
        neighbour[secondTargetClass] = itemSecondClass;
    }

    return neighbour;
}
