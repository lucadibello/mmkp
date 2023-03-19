//
// Created by Luca Di Bello on 16.03.23.
//

#ifndef MMKP_ANALYTICS_H
#define MMKP_ANALYTICS_H

#include "./AnalyticsReport.h"
#include "src/data.h"


class Analytics {
public:
    static AnalyticsReport run(const Data * instance);
};


#endif //MMKP_ANALYTICS_H
