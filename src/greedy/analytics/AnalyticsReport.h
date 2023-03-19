//
// Created by Luca Di Bello on 16.03.23.
//

#ifndef MMKP_ANALYTICSREPORT_H
#define MMKP_ANALYTICSREPORT_H

#include <vector>

class AnalyticsReport {
public:
    AnalyticsReport(int nClasses, const std::vector<int> *nItemsPerClass);
    ~AnalyticsReport();

    void setMeanValueGlobal(double meanValue);
    void setMeanWeightGlobal(double meanWeight);
    void setMeanValueClass(int classIndex, float meanValue);
    void setMeanWeightClass(int classIndex, float meanWeight);
    void setValueAvgWeightRatioItem(int classIndex, int itemIndex, float ratioValue);
    void print() const;

    void setMeanRatioGlobal(double d);

private:
    int m_nClasses;
    const std::vector<int> *m_nItems;

    // Analytics of the whole problem
    double m_meanValue_global;
    double m_meanWeight_global;
    double m_meanRatio_global;

    // Analytics of each class
    std::vector<float> m_meanWeight_class;
    std::vector<float> m_meanValue_class;

    // Analytics of each item
    // Notice: Position of the item in the vector: classIndex * nItemsPerClass + itemIndex
    std::vector<float> m_valueAvgWeightRatio_item;
};


#endif //MMKP_ANALYTICSREPORT_H
