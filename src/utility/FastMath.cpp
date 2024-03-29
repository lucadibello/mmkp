//
// Created by Luca Di Bello on 18.03.23.
//

#include <complex>
#include <iostream>
#include "FastMath.h"

float FastMath::fastMean(int startPosition, unsigned int nItems, const std::vector<int> *values) {
    // Compute the mean of the first nItems elements of the vector
    int mean = 0;
    for (auto i = startPosition; i < startPosition + (int) nItems; i++) {
        int v = values->at(i);
        mean += v;
    }
    return static_cast<float>(mean) / static_cast<float>(nItems);
}

float FastMath::fastStdDev(int startPosition, unsigned int nItems, const std::vector<int> *values) {
    // Compute the standard deviation of the first nItems elements of the vector
    float mean = fastMean(startPosition, nItems, values);
    float sumSqDiff = 0;
    for (auto i = startPosition; i < startPosition + (int) nItems; i++) {
        int v = values->at(i);
        float diff = static_cast<float>(v) - mean;
        sumSqDiff += diff * diff;
    }
    return std::sqrt(sumSqDiff / static_cast<float>(nItems));
}

