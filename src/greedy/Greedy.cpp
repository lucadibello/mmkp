//
// Created by Luca Di Bello on 22.03.23.
//

#include "Greedy.h"
#include "src/greedy/analytics/AnalyticsReport.h"
#include "src/greedy/analytics/Analytics.h"
#include "src/utility/EasyInstance.h"
#include <iostream>
#include <algorithm>

void sortClassesByRatioStd(std::vector<int> &classes, const Data *instance) {
    std::sort(classes.begin(), classes.end(), [&instance](int i, int j) {

        double ratio_i = 0;
        double ratio_j = 0;

        //class i
        double sum_v_i = 0;
        for (auto m = 0; m < instance->nresources; m++) {
            double sum_w_i = 0;
            sum_v_i += instance->values[i][m];
            for (auto k = 0; k < instance->nitems[i]; k++) {
                sum_w_i += instance->weights[i][k * instance->nresources + m];
            }
            ratio_i += (sum_w_i / (double) instance->nitems[i]) /
                       instance->capacities[m];  // average weight of class i for every item divided by the capacity of the knapsack for that dimension
        }
        ratio_i = sum_v_i / ratio_i;

        //class j
        double sum_v_j = 0;
        for (auto m = 0; m < instance->nresources; m++) {
            double sum_w_j = 0;
            sum_v_j += instance->values[j][m];
            for (auto k = 0; k < instance->nitems[j]; k++) {
                sum_w_j += instance->weights[j][k * instance->nresources + m];
            }
            ratio_j += (sum_w_j / (double) instance->nitems[j]) /
                       instance->capacities[m];  // average weight of class j for every item divided by the capacity of the knapsack for that dimension
        }
        ratio_j = sum_v_j / ratio_j;

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
        ratio_i = instance->values[classIndex][i] / ratio_i;
        ratio_j = instance->values[classIndex][j] / ratio_j;
        // more ratio is better
        return ratio_i > ratio_j;
    });
}

void sortAll(std::vector<int> &classes, std::vector<std::vector<int>> &items, const Data *instance) {
    std::cout << "Sorting classes and items..." << std::endl;
    sortClassesByRatioStd(classes, instance);
    for (int c : classes) {
        sortItemsByRatioStd(items[c], c, instance);
    }
}


void printCapacities(Data *instance) {
    std::cout << "Capacities: ";
    for (auto k = 0; k < instance->nresources; k++) {
        std::cout << instance->capacities[k] << " ";
    }
    std::cout << std::endl;
}

void Greedy::compute(Data *instance) {
    // Compute analysis of the dataset
    AnalyticsReport report = Analytics::run(instance);

    /* ******************** */
    /*    Greedy Solution   */
    /* ******************** */

    std::cout << "Computing greedy solution..." << std::endl;

    // Create an array of classes + items indices for each class to be sorted
    std::vector<int> sortedClasses(instance->nclasses);
    std::vector<std::vector<int>> sortedItems(instance->nclasses);
    for (int i = 0; i < instance->nclasses; i++) {
        sortedClasses[i] = i;
        sortedItems[i] = std::vector<int>(instance->nitems[i]);
        for (int j = 0; j < instance->nitems[i]; j++) {
            sortedItems[i][j] = j;
        }
    }

    std::cout << "======= CALCULATING SOLUTION =======" << std::endl;

    // Now, pick the first element that fits in the knapsack
    // Note: if item i is picked, then all items j with j > i are discarded
    for (int i = 0; i < instance->nclasses; i++) {
        sortAll(sortedClasses, sortedItems, instance);

        int classIndex = sortedClasses[0];
        bool itemTook = false;


        for (int itemIndex: sortedItems[classIndex]) {
            if (EasyInstance::doesItemFit(instance, classIndex, itemIndex)) {
                // Pick right solution!
                EasyInstance::pickSolution(instance, classIndex, itemIndex);
                // Print capacities
                itemTook = true;
                printCapacities(instance);
                break;
            } else {
                std::cout << "Item " << itemIndex << " of class " << classIndex << " does not fit in the knapsack"
                          << std::endl;
            }
        }
        if (!itemTook) {
            std::cout << "No item of class " << classIndex << " fits in the knapsack" << std::endl;
            std::cout << "Done " << i << " classes out of " << sortedClasses.size() << std::endl;
            exit(1);
        }
        sortedClasses.erase(sortedClasses.begin());
    }

    std::cout << "======= SOLUTION CALCULATED =======" << std::endl;

    // Print solution to stdout
    std::cout << "Solution: " << std::endl;
    for (int i = 0; i < instance->nclasses; i++) {
        std::cout << "Class #" << i << " -> Item #" << instance->solution[i] << std::endl;
    }

    std::cout << "Remaining capacities: ";
    for (auto k = 0; k < instance->nresources; k++) {
        std::cout << instance->capacities[k] << " ";
    }
    std::cout << std::endl;
}
