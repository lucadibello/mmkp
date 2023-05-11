//
// Created by Luca Di Bello on 20.04.23.
//

#include "Metaheuristic.h"
#include <iostream>
#include <random>
#include <cmath>

/**
 * Simulated Annealing temperature.
 *
 * Used to compute the probability of accepting a worse solution.
 */
double Metaheuristic::m_temperature = 600;

/**
 * Metaheuristic solver based Simulated Annealing.
 * @param originalInstance The instance to solve.
 */
[[noreturn]] void Metaheuristic::compute(Data *originalInstance, int timelimit) {
    // Configure random for simulated annealing
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    std::uniform_int_distribution<> disInt(0, originalInstance->nclasses - 1);

    std::cout << "Starting simulated annealing with timelimit " << timelimit << std::endl;

    // Lower time = higher decrease rate
    double decreaseRate;
    if (timelimit <= 1) {
        decreaseRate = 0.99;
    } else if (timelimit <= 10) {
        decreaseRate = 0.999;
    } else if (timelimit <= 60) {
        decreaseRate = 0.9999;
    } else {
        decreaseRate = 0.99999;
    }

    // Compute current solution value
    long totalValue = computeTotalValue(originalInstance->solution, originalInstance);
    long optimalValue = totalValue;
    std::cout << "Initial solution value: " << totalValue << std::endl;

    // Create a temporary instance to store the local solution
    Data *instance = originalInstance->copy();

    // Start the iterations
    while(true) {
        // Generate a neighbor from the initial solution
        std::vector<int> neighbour = Metaheuristic::computeNeighbour(instance, disInt);

        // Update capacities
        std::vector<int> neighborCapacities = instance->capacities;
        bool isSame = true;
        for (long unsigned int i = 0; i < neighbour.size(); i++) {
            // Update only classes that have changed
            if (neighbour[i] != instance->solution[i]) {
                // Update same flag
                isSame = false;
                for (int j = 0; j < instance->nresources; j++) {
                    neighborCapacities[j] -= instance->weights[i][neighbour[i] * instance->nresources + j];
                    neighborCapacities[j] += instance->weights[i][instance->solution[i] * instance->nresources + j];
                }
            }
        }

        // If same solution generated (no feasible neighbor has been found), continue
        if (isSame) {
            continue;
        }

        // Compute the neighbor value and the delta
        long neighborValue = computeTotalValue(neighbour, instance);
        auto delta = static_cast<double>(neighborValue - totalValue);

        // If the neighbor is better than the current solution, move to it
        if (delta >= 0) {
            instance->solution = neighbour;
            instance->capacities = neighborCapacities;
            totalValue = neighborValue;

            // Check if found solution is also an optimal solution
            if (totalValue > optimalValue) {
                optimalValue = totalValue;

                // Save solution to instance
                originalInstance->solution = neighbour;
                std::cout << "Found new optimal solution with value " << optimalValue << std::endl;
            } else {
                std::cout << "--- accepting better solution with delta " << delta << std::endl;
            }
        } else {
            // If the neighbor is worse than the current solution, move to it with a probability
            double probability = exp(delta / m_temperature);
            double random = dis(gen);

            if (probability > random) {
                std::cout << "--- accepting worse solution with probability " << probability << " and random " << random << "(delta=" << delta << ", temperature=" << m_temperature << ")" << std::endl;
                instance->solution = neighbour;
                instance->capacities = neighborCapacities;
                totalValue = neighborValue;
            }

            // Update temperature
            m_temperature *= decreaseRate;
        }

        // Print current solution vs optimal solution
        std::cout << "Current solution value: " << totalValue << " (optimal: " << optimalValue << ")" << std::endl;
    }
}

long Metaheuristic::computeTotalValue(std::vector<int> solution, Data *instance) {
    long totalValue = 0;
    for (int i = 0; i < instance->nclasses; i++) {
        totalValue += instance->values[i][solution[i]];
    }
    return totalValue;
}

std::vector<int> Metaheuristic::computeNeighbour(Data *instance, std::uniform_int_distribution<> classDistribution) {
    // Create two generators for the two target classes
    std::random_device rd;
    std::mt19937 gen(rd());

    // Copy current solution
    std::vector<int> neighbour = instance->solution;

    // Choose two different target classes
    int firstTargetClass;
    int secondTargetClass;
    do {
        firstTargetClass = classDistribution(gen);
        secondTargetClass = classDistribution(gen);
    } while (firstTargetClass == secondTargetClass);

    // Create a distribution for the items of the first target class
    std::uniform_int_distribution<> itemDistribution(0, instance->nitems[firstTargetClass] - 1);
    std::uniform_int_distribution<> itemDistribution2(0, instance->nitems[secondTargetClass] - 1);

    // Pick random items for the two target classes
    int itemFirstClass = itemDistribution(gen);
    int itemSecondClass = itemDistribution2(gen);

    // Update capacities
    std::vector<int> neighbourCapacities = instance->capacities;
    for (int j = 0; j < instance->nresources; j++) {
        neighbourCapacities[j] -= instance->weights[firstTargetClass][itemFirstClass * instance->nresources + j];
        neighbourCapacities[j] += instance->weights[firstTargetClass][instance->solution[firstTargetClass] * instance->nresources + j];
        neighbourCapacities[j] -= instance->weights[secondTargetClass][itemSecondClass * instance->nresources + j];
        neighbourCapacities[j] += instance->weights[secondTargetClass][instance->solution[secondTargetClass] * instance->nresources + j];
    }

    // Check if neighbour is feasible
    bool feasible = true;
    for (int neighbourCapacity : neighbourCapacities) {
        if (neighbourCapacity < 0)
            feasible = false;
    }

    // Update neighbour if feasible, otherwise return the current solution
    if (feasible) {
        neighbour[firstTargetClass] = itemFirstClass;
        neighbour[secondTargetClass] = itemSecondClass;
    }

    return neighbour;
}

