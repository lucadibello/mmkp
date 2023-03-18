//
// Created by Luca Di Bello on 18.03.23.
//

#include "FastMath.h"

float FastMath::fastMean(int startPosition, unsigned int nItems, std::vector<int> &values) {
    // Compute the mean of the first nItems elements of the vector
    int mean = 0;
    for (auto i = startPosition; i < startPosition + nItems; i++) {
        mean += values[i];
    }
    return static_cast<float>(mean) / static_cast<float>(nItems);
}
