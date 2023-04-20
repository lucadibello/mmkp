//
// Created by Luca Di Bello on 20.04.23.
//

#include "Metaheuristic.h"

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
 * Metaheuristic solver based on the Random Ant Colony Optimization (R-Ant) algorithm using a Max-Min Ant System (MMAS) strategy.
 * @param instance
 */
void Metaheuristic::compute(Data *instance, unsigned int kAnts) {
    // Initialize the pheromone trails to the maximum value
    std::vector<std::vector<unsigned int>> t(instance->nclasses, std::vector<unsigned int>(instance->nitems[0], 0));
    for (auto i = 0; i < instance->nclasses; i++) {
        for (auto j = 0; j < instance->nitems[i]; j++) {
            t[i][j] = m_tMax;
        }
    }

    // Start the iterations
    while(!stopCondition()) {
        // Run the ants
    }
}


bool Metaheuristic::stopCondition() {
    return ++m_iterations >= 100;
}

