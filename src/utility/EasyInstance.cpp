//
// Created by Luca Di Bello on 13.03.23.
//

#include "EasyInstance.h"

/**
 * Save the solution (best item) for the given class of the Multi-Objective Multi-Dimensional Knapsack Problem and update the capacities of the multi-dimensional knapsack
 * @param instance The instance of the Multi-Objective Multi-Dimensional Knapsack Problem
 * @param classIndex The index of the class
 * @param itemIndex The index of the item
 */
void EasyInstance::pickSolution(Data &instance, const int classIndex, const int itemIndex) {
    // Save the solution in the array of solutions
    instance.solution[classIndex] = itemIndex;

    // Update the capacity of the multi-dimensional knapsack
    for (auto k = 0; k < instance.nresources; k++){
        instance.capacities[k] -= instance.weights[classIndex][itemIndex * instance.nresources + k];
    }
}

/**
 * Check if the item "itemIndex" of the class "classIndex" fits the capacity of the multi-dimensional knapsack
 * @param instance  The instance of the Multi-Objective Multi-Dimensional Knapsack Problem
 * @param classIndex The index of the class
 * @param itemIndex The index of the item
 * @return True if the item fits the capacity of the multi-dimensional knapsack, false otherwise
 */
bool EasyInstance::doesItemFit(Data &instance, int classIndex, int itemIndex) {
    // Ensure that item "itemIndex" fits the capacity of all dimensions of the multi-dimensional knapsack at class "classIndex"
    for (auto k = 0; k < instance.nresources; k++){
        // if item weight of dimension k > knapsack capacity of dimension k = item does not fit
        if (instance.weights[classIndex][itemIndex * instance.nresources + k] > instance.capacities[k]){
            return false;
        }
    }
    return true;
}
