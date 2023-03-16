//
// Created by Luca Di Bello on 16.03.23.
//

#ifndef MMKP_ANALYTICSREPORT_H
#define MMKP_ANALYTICSREPORT_H

#include <vector>

class AnalyticsReport {
private:
    // Analytics of the whole problem
    float m_meanValue_global;
    float m_meanWeight_global;

    // Analytics of each class
    std::vector<float> m_meanValue_class;
    std::vector<float> m_meanWeight_class;

    // Analytics of each item
    std::vector<float> m_valueAvgWeightRatio_item;

public:
    AnalyticsReport();
    ~AnalyticsReport();

    void setMeanValueGlobal(float meanValue);
    void setMeanWeightGlobal(float meanWeight);
    void setMeanValueClass(int classIndex, float meanValue);
    void setMeanWeightClass(int classIndex, float meanWeight);
    void setValueAvgWeightRatioItem(int classIndex, int itemIndex, float ratioValue);
};


#endif //MMKP_ANALYTICSREPORT_H
