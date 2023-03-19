//
// Created by Luca Di Bello on 16.03.23.
//

#include "AnalyticsReport.h"

#include <utility>
#include <iostream>

/**
 * Constructor method.
 */
AnalyticsReport::AnalyticsReport(int nClasses, const std::vector<int> *nItemsPerClass): m_nClasses{nClasses}, m_nItems{nItemsPerClass}, m_meanValue_global(0), m_meanWeight_global(0) {
    // Initialize vectors size to avoid memory allocation during the execution (speed up the process)
    m_meanValue_class.resize(nClasses);
    m_meanWeight_class.resize(nClasses);
    int nItems = 0;
    for(int i = 0; i < nItemsPerClass->size(); i ++)
        nItems += nItemsPerClass->at(i);
    m_valueAvgWeightRatio_item.resize(nItems);
    //m_valueAvgWeightRatio_item[i * m_nItems[i] + j]
}


/**
 * Destructor method.
 */
AnalyticsReport::~AnalyticsReport() {
    // Clear vectors
    m_meanValue_class.clear();
    m_meanWeight_class.clear();
    m_valueAvgWeightRatio_item.clear();
}

/**
 * Set the mean ratio of the whole problem, taking into account the value/weight ratio of all the items of all the classes.
 * @param meanRatio Mean ratio of the whole problem.
 */
void AnalyticsReport::setMeanRatioGlobal(double meanRatio) {
    m_meanRatio_global = meanRatio;
}

/**
 * Set the mean value of the whole problem, taking into account the value of all the items of all the classes.
 * @param meanValue Mean value of the whole problem.
 */
void AnalyticsReport::setMeanValueGlobal(double meanValue) {
    m_meanValue_global = meanValue;
}

/**
 * Set the mean weight of the whole problem, taking into account the weight of all the items of all the classes.
 * @param meanWeight
 */
void AnalyticsReport::setMeanWeightGlobal(double meanWeight) {
    m_meanWeight_global = meanWeight;
}

/**
 * Set the mean value of a class, taking into account the value of all the items of the class.
 * @param classIndex Index of the class.
 * @param meanValue Mean value of the class.
 */
void AnalyticsReport::setMeanValueClass(int classIndex, float meanValue) {
    m_meanValue_class[classIndex] = meanValue;
}

/**
 * Set the mean weight of a class, taking into account the weight of all the items of the class.
 * @param classIndex Index of the class.
 * @param meanWeight Mean weight of the class.
 */
void AnalyticsReport::setMeanWeightClass(int classIndex, float meanWeight) {
    m_meanWeight_class[classIndex] = meanWeight;
}

/**
 * Set the value/average weight ratio of an item.
 * @param classIndex Index of the class.
 * @param itemIndex Index of the item.
 * @param ratioValue Value/average weight ratio of the item.
 */
void AnalyticsReport::setValueAvgWeightRatioItem(int classIndex, int itemIndex, float ratioValue) {
    m_valueAvgWeightRatio_item[classIndex * m_nItems->at(classIndex) + itemIndex] = ratioValue;
}

void AnalyticsReport::print() const {
    std::cout << "==== Analytics report ====" << std::endl;
    std::cout << "- Number of classes: " << m_nClasses << std::endl;
    std::cout << "- Mean value of the whole problem: " << m_meanValue_global << std::endl;
    std::cout << "- Mean weight of the whole problem: " << m_meanWeight_global << std::endl;
    std::cout << "- Mean ratio the whole problem: " << m_meanWeight_global << std::endl;
    for (auto i = 0; i < m_nClasses; i++) {
        std::cout << "- Class " << i << std::endl;
        std::cout << "\t- Mean value of the class: " << m_meanValue_class[i] << std::endl;
        std::cout << "\t- Mean weight of the class: " << m_meanWeight_class[i] << std::endl;
        for (auto j = 0; j < m_nItems->at(i); j++) {
            std::cout << "\t- Item " << j << std::endl;
            std::cout << "\t\t- Value/average weight ratio: " << m_valueAvgWeightRatio_item[i * m_nItems->at(i) + j] << std::endl;
        }
    }
}
