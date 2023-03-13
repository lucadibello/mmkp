//
// Created by Luca Di Bello on 13.03.23.
//

#ifndef MMKP_EASYINSTANCE_H
#define MMKP_EASYINSTANCE_H


#include "src/data.h"

class EasyInstance {
public:
    static void pickSolution(Data & instance, int classIndex, int itemIndex);
    static bool doesItemFit(Data & instance, int classIndex, int itemIndex);
};


#endif //MMKP_EASYINSTANCE_H
