//
// Created by Luca Di Bello on 20.04.23.
//

#ifndef MMKP_METAHEURISTIC_H
#define MMKP_METAHEURISTIC_H


#include "src/data.h"

class Metaheuristic {
public:
    static void compute(Data * instance, unsigned int kAnts);

private:
    const static unsigned int m_tMax;
    const static unsigned int m_tMin;
    static unsigned int m_iterations;
    static bool stopCondition();
};


#endif //MMKP_METAHEURISTIC_H
