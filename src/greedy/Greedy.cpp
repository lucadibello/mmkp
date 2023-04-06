//
// Created by Luca Di Bello on 22.03.23.
//

#include "Greedy.h"
#include "src/utility/EasyInstance.h"
#include <iostream>
#include <algorithm>

void sortClassesByRatioStd(std::vector<int> &classes, const Data *instance) {
    std::sort(classes.begin(), classes.end(), [&instance](int i, int j) {

        double ratio_i = 0;
        double ratio_j = 0;

        //class i
        //double sum_v_i = 0;
        for (auto m = 0; m < instance->nresources; m++) {
            double sum_w_i = 0;
            //sum_v_i += instance->values[i][m];
            for (auto k = 0; k < instance->nitems[i]; k++) {
                sum_w_i += instance->weights[i][k * instance->nresources + m];
            }
            ratio_i += (sum_w_i / (double) instance->nitems[i]) /
                       instance->capacities[m];  // average weight of class i for every item divided by the capacity of the knapsack for that dimension
        }
        //ratio_i = sum_v_i / ratio_i;

        //class j
        //double sum_v_j = 0;
        for (auto m = 0; m < instance->nresources; m++) {
            double sum_w_j = 0;
            //sum_v_j += instance->values[j][m];
            for (auto k = 0; k < instance->nitems[j]; k++) {
                sum_w_j += instance->weights[j][k * instance->nresources + m];
            }
            ratio_j += (sum_w_j / (double) instance->nitems[j]) /
                       instance->capacities[m];  // average weight of class j for every item divided by the capacity of the knapsack for that dimension
        }
        //ratio_j = sum_v_j / ratio_j;

        // start with the worst class
        return ratio_i > ratio_j;
    });
}

void sortItemsByRatioStd(std::vector<int> &items, int classIndex, const Data *instance) {
    std::sort(items.begin(), items.end(), [classIndex, &instance](int i, int j) {
        double ratio_i = 0;
        double ratio_j = 0;
        for (auto k = 0; k < instance->nresources; k++) {
            ratio_i += (instance->weights[classIndex][i * instance->nresources + k] /
                        (double) instance->capacities[k]);
            ratio_j += (instance->weights[classIndex][j * instance->nresources + k] /
                        (double) instance->capacities[k]);
        }
        // less ratio is better
        return ratio_i < ratio_j;
    });
}

void Greedy::compute(Data *instance, int timeLimit) {
    // Is in beast mode?
    bool beastMode = timeLimit <= 1;

    /* ******************** */
    /*    Greedy Solution   */
    /* ******************** */

    // Create an array of classes + items indices for each class to be sorted
    std::vector<int> sortedClasses(instance->nclasses);
    std::vector<std::vector<int>> sortedItems(instance->nclasses);
    long totalItems = 0;
    for (int i = 0; i < instance->nclasses; i++) {
        sortedClasses[i] = i;
        sortedItems[i] = std::vector<int>(instance->nitems[i]);
        for (int j = 0; j < instance->nitems[i]; j++) {
            sortedItems[i][j] = j;
            totalItems++;
        }
    }

    bool skipSortings = false;
    if (beastMode) {
        long tot = instance->nclasses * totalItems;
        if (tot > 1750000) {
            skipSortings = true;
        }
    }

    // Now, pick the first element that fits in the knapsack
    // Note: if item i is picked, then all items j with j > i are discarded
    if (skipSortings) {
        sortClassesByRatioStd(sortedClasses, instance);
    }

    for (int i = 0; i < instance->nclasses; i++) {
        if (!skipSortings) {
            sortClassesByRatioStd(sortedClasses, instance);
        }
        int classIndex = sortedClasses[0];
        sortItemsByRatioStd(sortedItems[classIndex], classIndex, instance);
        bool itemTook = false;

        for (int itemIndex: sortedItems[classIndex]) {
            if (EasyInstance::doesItemFit(instance, classIndex, itemIndex)) {
                // Pick right solution!
                EasyInstance::pickSolution(instance, classIndex, itemIndex);
                // Print capacities
                itemTook = true;
                break;
            }
        }
        if (!itemTook) {
            exit(1);
        }
        sortedClasses.erase(sortedClasses.begin());
    }
}
