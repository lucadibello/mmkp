//
// Created by Luca Di Bello on 16.03.23.
//

#include "AnalyticsReport.h"

/**
 * Constructor method.
 */
AnalyticsReport::AnalyticsReport(): m_meanValue_global(0), m_meanWeight_global(0) {}

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
 * Set the mean value of the whole problem, taking into account the value of all the items of all the classes.
 * @param meanValue Mean value of the whole problem.
 */
void AnalyticsReport::setMeanValueGlobal(float meanValue) {
    m_meanValue_global = meanValue;
}

/**
 * Set the mean weight of the whole problem, taking into account the weight of all the items of all the classes.
 * @param meanWeight
 */
void AnalyticsReport::setMeanWeightGlobal(float meanWeight) {
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
}