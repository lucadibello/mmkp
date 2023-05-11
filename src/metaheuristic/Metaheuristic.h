//
// Created by Luca Di Bello on 20.04.23.
//

#ifndef MMKP_METAHEURISTIC_H
#define MMKP_METAHEURISTIC_H


#include <random>
#include "src/data.h"

class Metaheuristic {
public:
    [[noreturn]] static void compute(Data * instance, int timelimit);

private:
    static long computeTotalValue(std::vector<int> solution, Data *instance);
    static double m_temperature;
    static std::vector<int> computeNeighbour(Data *instance, std::uniform_int_distribution<> disInt);
};


#endif //MMKP_METAHEURISTIC_H
