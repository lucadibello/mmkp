#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "data.h"
#include "src/utility/EasyInstance.h"
#include "src/greedy/analytics/AnalyticsReport.h"
#include "src/greedy/analytics/Analytics.h"
#include <cstdlib>
#include <cstdio>
#include <csignal>

static Data instance;
static std::string output;

char* getOption(int argc, char* argv[], const char* option)
{
  for( int i = 0; i < argc; ++i)
    if(strcmp(argv[i], option) == 0 )
      return argv[i+1];
  return nullptr;
}

inline bool exists (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

void writeSolution() {
    printf("\nSolution:\n");
    int total_value = 0;
    for (auto i = 0; i < instance.nclasses; i++){
        const int itemValue = instance.values[i][instance.solution[i]];
        printf("Class n: %d has item n: %d with value: %d\n", i, instance.solution[i], itemValue);
        total_value += itemValue;
    }
    printf("Total value: %d\n", total_value);

    std::ofstream outfile;
    outfile.open(output, std::ios_base::out);
    for (auto i = 0; i < instance.nclasses; i++){
        outfile << instance.solution[i] << " ";
    }
    outfile.close();
}

void signalHandler( int signum ) {
   std::cout << "Running finalizing code. Interrupt signal (" << signum << ") received.\n";

   writeSolution();

   exit(signum);  
}

int main(int argc, char *argv[]) {

    // register signal SIGINT and signal handler  
    signal(SIGINT, signalHandler); 

    char* timelimit = getOption(argc, argv, std::string("-t").c_str());
    char* input = getOption(argc, argv, std::string("-i").c_str());

    if (timelimit == nullptr || input == nullptr){
        std::cout << "Parameters are not correctly specified!\n";
        std::exit(1);
    }

    int inttimelimit = atoi(timelimit);
    std::cout << "Instance name:" << input << "\n" ;
    std::cout << "Time limit:" << inttimelimit << "\n" ;
    output = input;
    output.append(".out");
    std::cout << "Output name:" << output << "\n";

    instance.read_input(input);

    // Compute analysis of the dataset
    AnalyticsReport report = Analytics::run(&instance);
    // NOTICE: To print the report --> report.print();
    report.print();

    /* ******************** */
    /*    Greedy Solution   */
    /* ******************** */

    // === Multi-Objective Multi-Dimensional Knapsack Problem ===
    // Greedy algorithm explanation:
    // - Find the item with the highest value and lowest average weight that fits the capacity of the multi-dimensional knapsack
    // - If there are multiple items with the same value, choose the one with the lowest average weight

    // Cycle through all classes
    for (auto i = 0; i < instance.nclasses; i++){
        // Cycle through all items of the class
        for (auto j = 0; j < instance.nitems[i]; j++){
            // If any item of the class has not been chosen yet, choose the first item
            if (instance.solution[i] == 0){
                // Save the solution in the array of solutions
                EasyInstance::pickSolution(instance, i, j);
            } else {
                // Check if the current item j fits the capacity of the multi-dimensional knapsack
                if (EasyInstance::doesItemFit(instance, i, j)){

                    // save values of the current best item in two variables to avoid multiple array accesses in the following if statements
                    const int bestItemValue = instance.values[i][instance.solution[i]];
                    const int currentItemValue = instance.values[i][j];

                    // If the chosen item fits the capacity of the multi-dimensional knapsack, check if it is better than the current best item
                    // An item is better of the current best item if:
                    //      1. It has a higher value than the current best item (higher value = better)
                    //      2. It has the same value as the current best item, but a lower average weight (lower average weight = better)

                    // Case 1: Check if item j has an higher value that the current best item
                    if (currentItemValue > bestItemValue){
                        EasyInstance::pickSolution(instance, i, j);
                    } else if (currentItemValue == bestItemValue){
                        // Case 2: Check if item j has the same value as the current best item, but a lower average weight
                        double avg_weight_j = 0;
                        double avg_weight_solution = 0;

                        // Compute average weight of item j and the current solution item
                        for (auto k = 0; k < instance.nresources; k++){
                            avg_weight_j += instance.weights[i][j * instance.nresources + k];
                            avg_weight_solution += instance.weights[i][instance.solution[i] * instance.nresources + k];
                        }
                        avg_weight_j /= instance.nresources;
                        avg_weight_solution /= instance.nresources;

                        // Check if item j has a lower average weight than the current best item
                        if (avg_weight_j < avg_weight_solution){
                            EasyInstance::pickSolution(instance, i, j);
                        }
                    }
                }
            }
        }
    }

    // Write solution to file
    writeSolution();
}
