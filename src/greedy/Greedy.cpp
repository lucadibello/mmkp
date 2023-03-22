//
// Created by Luca Di Bello on 22.03.23.
//

#include "Greedy.h"
#include "src/greedy/analytics/AnalyticsReport.h"
#include "src/greedy/analytics/Analytics.h"
#include "src/utility/EasyInstance.h"
#include <iostream>

void sortClassesByRatioStd(std::vector<int> &classes, const AnalyticsReport &report) {
    // Class at index i has ratio: report.getMeanValueClass
    std::sort(classes.begin(), classes.end(), [&report](int i, int j) {
        double ratio_i = report.getMeanValueClass(i) / report.getMeanWeightClass(i);
        double ratio_j = report.getMeanValueClass(j) / report.getMeanWeightClass(j);
        return ratio_i > ratio_j;
    });
}

void sortItemsByRatioStd(std::vector<int> &items, const AnalyticsReport &report, int classIndex) {
    // Item at index i has ratio: report.getValueAvgWeightRatioItem
    std::sort(items.begin(), items.end(), [&report, classIndex](int i, int j) {
        double ratio_i = report.getValueAvgWeightRatioItem(classIndex, i);
        double ratio_j = report.getValueAvgWeightRatioItem(classIndex, j);
        return ratio_i > ratio_j;
    });
}

void sortAll(std::vector<int> &classes, std::vector<std::vector<int>> &items, const AnalyticsReport &report) {
    sortClassesByRatioStd(classes, report);
    for (int i = 0; i < classes.size(); i++) {
        sortItemsByRatioStd(items[i], report, classes[i]);
    }
}


void printCapacities(Data *instance) {
    std::cout << "Capacities: ";
    for (auto k = 0; k < instance->nresources; k++){
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

    // Sort from most valuable class to least valuable class
    sortAll(sortedClasses, sortedItems, report);

    // Print all items for each class and print their most valuable / least valuable ratio
    for (int i = 0; i < sortedClasses.size(); i++) {
        std::cout << "Sorted items for class " << sortedClasses[i] << " (average: " << report.getMeanValueClass(sortedClasses[i]) / report.getMeanWeightClass(sortedClasses[i]) << "): ";
        for (int j = 0; j < sortedItems[i].size(); j++) {
            std::cout << "(" << sortedItems[i][j] << "," << report.getValueAvgWeightRatioItem(sortedClasses[i], sortedItems[i][j]) << ") ";
        }
        std::cout << std::endl;
    }

    // FIXME: POSSIBILE IMPROVEMENT
    // - A parte cercare gli item con il rapporto valore/peso maggiore
    // - Implementare un meccanismo di wear leveling per evitare di riempire completamente la capacità di una risorsa
    //  --> Si potrebbe fare calcolando un indice di "wear" per ogni oggetto (peso oggetto / capacità risorsa) e scegliere quelli con valor


    std::cout << "======= CALCULATING SOLUTION =======" << std::endl;

    // Now, pick the first element that fits in the knapsack
    // Note: if item i is picked, then all items j with j > i are discarded
    for (int i = 0; i < sortedClasses.size(); i++) {
        int classIndex = sortedClasses[i];
        for (int itemIndex : sortedItems[i]) {
            if (EasyInstance::doesItemFit(instance, classIndex, itemIndex)) {
                // Pick right solution!
                EasyInstance::pickSolution(instance, classIndex, itemIndex);
                // Print capacities
                printCapacities(instance);
                break;
            } else {
                std::cout << "Item " << itemIndex << " of class " << classIndex << " does not fit in the knapsack" << std::endl;
            }
        }
    }
    std::cout << "======= SOLUTION CALCULATED =======" << std::endl;

    // Print solution to stdout
    std::cout << "Solution: ";
    for (int i = 0; i < instance->nclasses; i++) {
        std::cout << "Class #" << i << " -> Item #" << instance->solution[i] << std::endl;
    }
}
