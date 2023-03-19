//
// Created by Luca Di Bello on 18.03.23.
//

#ifndef MMKP_FASTMATH_H
#define MMKP_FASTMATH_H

#include <vector>

class FastMath {
public:
    static float fastMean(int startPosition, unsigned int nItems, const std::vector<int> *values);
};


#endif //MMKP_FASTMATH_H
