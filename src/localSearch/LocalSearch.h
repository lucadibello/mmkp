//
// Created by mattia on 20/04/23.
//

#ifndef MMKP_LOCALSEARCH_H
#define MMKP_LOCALSEARCH_H


#include "src/data.h"

class LocalSearch {
public:
    static void compute(Data * instance);

private:
    static bool stopCondition();
    static std::vector<int> computeNeighbour(Data* instance);
};

#endif //MMKP_LOCALSEARCH_H
