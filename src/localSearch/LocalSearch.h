//
// Created by mattia on 20/04/23.
//

#ifndef MMKP_LOCALSEARCH_H
#define MMKP_LOCALSEARCH_H


#include "src/data.h"

class LocalSearch {
public:
    static void compute(Data * instance);

    static std::vector<int> computeNeighborhood(Data* instance);

private:
    static int m_iterations;
    static bool stopCondition();
};

#endif //MMKP_LOCALSEARCH_H
