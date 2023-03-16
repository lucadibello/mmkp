//
// Created by Luca Di Bello on 16.03.23.
//

#include "Analytics.h"

AnalyticsReport &Analytics::run(const Data &instance) {
    // Compute the average value and weight of the whole problem + each class + each item and save them into an AnalyticsReport object
    AnalyticsReport report{};

    // Build report incrementally (compute all required values in the same loop to speed up the process, we want a super fast solution)
    for (auto i = 0; i < instance.nclasses; i++) {
        // Cycle through all items of the class
        for (auto j = 0; j < instance.nitems[i]; j++) {
            const int itemValue = instance.values[i][j];
            const int itemWeight = instance.weights[i][j];
        }
    }
}
