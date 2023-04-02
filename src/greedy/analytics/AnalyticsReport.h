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
    void setAvgWeightItem(int classIndex, int itemIndex, float avgWeightValue);
    float getAvgWeightItem(int classIndex, int itemIndex) const;
    void setStdDevWeightItem(int classIndex, int itemIndex, float stdDevValue);
    float getStdDevWeightItem(int classIndex, int itemIndex) const;

    void print() const;

    float getMeanValueClass(int classIndex) const;
    float getMeanWeightClass(int classIndex) const;
private:
    int m_nClasses;
    const std::vector<int> *m_nItems;

    // Analytics of the whole problem
    double m_meanValue_global;
    double m_meanWeight_global;

    // Analytics of each class
    std::vector<float> m_meanWeight_class;
    std::vector<float> m_meanValue_class;

    // Analytics of each item
    // Notice: Position of the item in the vector: classIndex * nItemsPerClass + itemIndex
    std::vector<float> m_valueAvgWeightRatio_item;
    std::vector<float> m_stdDevValue_item;
    //std::vector<float> m_valueAvgWeight_item;
    std::vector<std::vector<float>> m_valueAvgWeight_item;
    // p value is the sum of the percentage for each weight class divided by the max capacity of the knapsack. (w1/Q1 + w2/Q2 + ... + wn/Qn)
    std::vector<double> m_pValue_item;

    // Final items ratio
    std::vector<double> m_itemRatio;
};


#endif //MMKP_ANALYTICSREPORT_H
