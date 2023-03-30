//
// Created by Luca Di Bello on 22.03.23.
//

#include "Greedy.h"
#include "src/greedy/analytics/AnalyticsReport.h"
#include "src/greedy/analytics/Analytics.h"
#include "src/utility/EasyInstance.h"
#include <iostream>
#include <algorithm>

static float valueDividedByAvgWeightImportance = 1;
static float stdDevDividedByAvgWeightImportance = 1;


void sortClassesByRatioStd(std::vector<int> &classes, const AnalyticsReport &report) {
    std::sort(classes.begin(), classes.end(), [&report](int i, int j) {
        double ratio_i = report.getMeanValueClass(i) / report.getMeanWeightClass(i);
        double ratio_j = report.getMeanValueClass(j) / report.getMeanWeightClass(j);
        return ratio_i > ratio_j;
    });
}

void sortItemsByRatioStd(std::vector<int> &items, const AnalyticsReport &report, int classIndex, const Data *instance) {
    std::cout << "Sorting items..." << std::endl;
    std::sort(items.begin(), items.end(), [&report, classIndex, &instance](int i, int j) {
        double piValue_i = 0;
        double piValue_j = 0;
        for (auto k = 0; k < instance->nresources; k++) {
            piValue_i += (instance->weights[classIndex][i * instance->nresources + k] /
                          (double) instance->capacities[k]);
            piValue_j += (instance->weights[classIndex][j * instance->nresources + k] /
                          (double) instance->capacities[k]);
        }
        double ratio_i = (((float) instance->values[classIndex][i] / report.getAvgWeightItem(classIndex, i)) *
                          valueDividedByAvgWeightImportance +
                          ((float) instance->values[classIndex][i] / report.getStdDevWeightItem(classIndex, i)) *
                          stdDevDividedByAvgWeightImportance) /
                         piValue_i;
        double ratio_j = (((float) instance->values[classIndex][j] / report.getAvgWeightItem(classIndex, j)) *
                          valueDividedByAvgWeightImportance +
                          ((float) instance->values[classIndex][j] / report.getStdDevWeightItem(classIndex, j)) *
                          stdDevDividedByAvgWeightImportance) /
                         piValue_j;
        return ratio_i > ratio_j;
    });
}

void sortAll(std::vector<int> &classes, std::vector<std::vector<int>> &items, const AnalyticsReport &report,
             const Data *instance) {
    std::cout << "Sorting classes and items..." << std::endl;
    sortClassesByRatioStd(classes, report);
    for (int i = 0; i < classes.size(); i++) {
        sortItemsByRatioStd(items[i], report, classes[i], instance);
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
    sortClassesByRatioStd(sortedClasses, report);
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
    for (int i = 0; i < sortedClasses.size(); i++) {
        int classIndex = sortedClasses[i];
        bool itemTook = false;

        sortedItems[i] = std::vector<int>(instance->nitems[i]);
        for (int j = 0; j < instance->nitems[i]; j++) {
            sortedItems[i][j] = j;
        }

        sortItemsByRatioStd(sortedItems[i], report, classIndex, instance);

        for (int itemIndex: sortedItems[i]) {
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
