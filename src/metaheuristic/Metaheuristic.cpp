//
// Created by Luca Di Bello on 20.04.23.
//

#include "Metaheuristic.h"
#include <iostream>
#include <random>
#include <cmath>

/**
 * Pheromone maximum value.
 */
const unsigned int Metaheuristic::m_tMax = 1000;

/**
 * Pheromone minimum value.
 */
const unsigned int Metaheuristic::m_tMin = 0;

/**
 * Initialize the iteration counter.
 */
unsigned int Metaheuristic::m_iterations = 0;

/**
 * Simulated Annealing temperature.
 *
 * Used to compute the probability of accepting a worse solution.
 */
double Metaheuristic::m_temperature = 4321;

/**
 * Metaheuristic solver based Simulated Annealing.
 * @param instance The instance to solve.
 */
void Metaheuristic::compute(Data *instance, int timelimit) {
    // Configure random for simulated annealing
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    // If beast mode (< 1), set the decrease rate to a lower value
    double decreaseRate;
    if (timelimit <= 1) {
        decreaseRate = 0.99;
    } else if (timelimit <= 10) {
        decreaseRate = 0.9999;
    } else if (timelimit <= 60) {
        decreaseRate = 0.999999;
    } else {
        decreaseRate = 0.99999999;
    }


    // Compute current solution value
    long totalValue = computeTotalValue(instance->solution, instance);
    std::cout << "Initial solution value: " << totalValue << std::endl;

    // Start the iterations
    while(!stopCondition()) {
        // Generate a neighbor from the initial solution
        std::vector<int> neighbour = Metaheuristic::computeNeighbour(instance);

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
        } else {
            std::cout << "Rejecting worse solution with delta " << delta << std::endl;

            // If the neighbor is worse than the current solution, move to it with a probability
            double probability = exp(delta / m_temperature);
            double random = dis(gen);

            std::cout << "Probability: " << probability << std::endl;

            if (probability > random) {
                std::cout << "Accepting worse solution with probability " << probability << " and random " << random << "(delta=" << delta << ", temperature=" << m_temperature << ")" << std::endl;
                instance->solution = neighbour;
                instance->capacities = neighborCapacities;
                totalValue = neighborValue;
            }

            // Update temperature
            m_temperature *= decreaseRate;
        }

        std::cout << "Current solution value: " << totalValue << std::endl;
    }
}

/**
 * Compute a neighbour of the current solution
 * @param instance The instance of the Multi-Objective Multi-Dimensional Knapsack Problem
 * @return A std::vector<int> containing the new solution
 */
std::vector<int> Metaheuristic::computeNeighbour(Data *instance) {
    // Copy current solution
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
    for (int neighbourCapacity : neighbourCapacities) {
        if (neighbourCapacity < 0)
            feasible = false;
    }

    // Update neighbour if feasible
    if (feasible) {
        neighbour[firstTargetClass] = itemFirstClass;
        neighbour[secondTargetClass] = itemSecondClass;
    }

    return neighbour;
}


bool Metaheuristic::stopCondition() {
    return false;
}

long Metaheuristic::computeTotalValue(std::vector<int> solution, Data *instance) {
    long totalValue = 0;
    for (int i = 0; i < instance->nclasses; i++) {
        totalValue += instance->values[i][solution[i]];
    }
    return totalValue;
}

