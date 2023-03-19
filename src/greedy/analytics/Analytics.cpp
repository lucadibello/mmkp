//
// Created by Luca Di Bello on 16.03.23.
//

#include "Analytics.h"
#include "src/utility/FastMath.h"

#include <iostream>

AnalyticsReport Analytics::run(const Data * instance) {
    // Compute the average value and weight of the whole problem + each class + each item and save them into an AnalyticsReport object
    AnalyticsReport report{
        instance->nclasses,
        &instance->nitems
    };

    // Build report incrementally (compute all required values in the same loop to speed up the process, we want a super fast solution)
    double totalValue = 0;
    double totalWeight = 0;
    long totalItems = 0;
    for (auto i = 0; i < instance->nclasses; i++) {
        const int nItemsPerClass = instance->nitems[i];

        // Update total number of items
        totalItems += nItemsPerClass;

        // Cycle through all items of the class
        int classMeanValue = 0;
        float classMeanWeight = 0;
        for (auto j = 0; j < nItemsPerClass; j++) {
            if(j == 24)
                std::cout << "24" << std::endl;
            const int itemValue = instance->values[i][j];
            //std::vector<int> itemWeights = instance->weights[i];
            const float weightMean = FastMath::fastMean(j * instance-> nresources, instance->nresources, &instance->weights[i]);

            // Update counters
            classMeanValue += itemValue;
            classMeanWeight += weightMean;

            // Compute the average value/weight ratio of the item
            const float ratioValue = static_cast<float>(itemValue) / weightMean;

            // Update the average value/weight ratio of the item
            report.setValueAvgWeightRatioItem(i, j, ratioValue);
        }

        // Update the average value and weight of the class
        const float computedClassMean = static_cast<float>(classMeanValue) / static_cast<float>(instance->nitems[i]);
        const float computedWeightMean = classMeanWeight / static_cast<float>(instance->nitems[i]);

        // Update the average value and weight of the class
        report.setMeanValueClass(i, computedClassMean);
        report.setMeanWeightClass(i, computedWeightMean);

        // Update the average value and weight of the whole problem
        totalValue += classMeanValue;
        totalWeight += classMeanWeight;
    }

    // Update the average value and weight of the whole problem
    report.setMeanValueGlobal(totalValue / static_cast<double>(totalItems));
    report.setMeanWeightGlobal(totalWeight / static_cast<double>(totalItems));
    report.setMeanRatioGlobal(totalValue / totalWeight);

    // Return the report
    return report;
}
