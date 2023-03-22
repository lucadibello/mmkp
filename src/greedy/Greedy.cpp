//
// Created by Luca Di Bello on 22.03.23.
//

#include "Greedy.h"
#include "src/greedy/analytics/AnalyticsReport.h"
#include "src/greedy/analytics/Analytics.h"
#include "src/utility/EasyInstance.h"

void Greedy::compute(Data *instance) {
    // Compute analysis of the dataset
    AnalyticsReport report = Analytics::run(instance);
    // NOTICE: To print the report --> report.print();
    report.print();

    /* ******************** */
    /*    Greedy Solution   */
    /* ******************** */

}
