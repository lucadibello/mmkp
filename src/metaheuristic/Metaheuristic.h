//
// Created by Luca Di Bello on 20.04.23.
//

#ifndef MMKP_METAHEURISTIC_H
#define MMKP_METAHEURISTIC_H


#include "src/data.h"

class Metaheuristic {
public:
    static void compute(Data * instance);

private:
    const static unsigned int m_tMax;
    const static unsigned int m_tMin;
    static unsigned int m_iterations;
    static bool stopCondition();
    static long computeTotalValue(std::vector<int> solution, Data *instance);
    static double m_temperature;
    static std::vector<int> computeNeighbour(Data *instance);
};


#endif //MMKP_METAHEURISTIC_H
