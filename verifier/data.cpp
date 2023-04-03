#include "data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int data::read_input(const string& instance) {
    cout << "Read instance: " << instance << " ";

    fstream newfile;
    newfile.open(instance, ios::in);
    if (newfile.is_open()) {
        string line;
        getline(newfile, line);
        istringstream sizes(line);
        sizes >> nclasses >> nresources;

        nitems.resize(nclasses);
        values.resize(nclasses);
        weights.resize(nclasses);
        solution.resize(nclasses);
        capacities.resize(nresources);

        getline(newfile, line);
        istringstream resources(line);
        for (auto i = 0; i < nresources; i++) {
            resources >> capacities[i];
        }

        for (auto i = 0; i < nclasses; i++) {
            solution[i] = 0;
            getline(newfile, line);
            istringstream isnitems(line);
            isnitems >> nitems[i];
            values[i].resize(nitems[i]);
            weights[i].resize(nitems[i] * nresources);
            for (auto j = 0; j < nitems[i]; j++) {
                getline(newfile, line);
                istringstream itemdata(line);
                itemdata >> values[i][j];
                for (auto z = 0; z < nresources; z++) {
                    itemdata >> weights[i][j * nresources + z];
                }
            }
        }
        newfile.close();
        cout << "Done." << endl << endl;

#ifdef MYDEBUG
        // Print for debug purposes
        cout << nclasses << " " << nresources << endl;
        for (auto i = 0; i<nresources; i++){
                cout << capacities[i] << " ";
        }
        cout << endl;
        for (auto i = 0; i<nclasses; i++){
                cout << nitems[i] << endl;
                for (auto j = 0; j<nitems[i]; j++){
                    cout << values[i][j] << " ";
                    for (auto z = 0; z<nresources; z++){
                        cout << weights[i][j * nresources + z] << " ";
                    }
                    cout << endl;
                }
        }
#endif

    }
    return 0;
}

int data::read_output(const string& instance) {
    cout << "Read solution: " << instance << " ";

    fstream newfile;
    newfile.open(instance, ios::in);

    if (newfile.is_open()) {
        string line;
        getline(newfile, line);
        istringstream items(line);

        solution.resize(nclasses);
        for (auto i = 0; i < nclasses; i++) {
            if (!(items >> solution[i])) {
                // Solution does not contain enough integer values
                newfile.close();
                return 2;
            }
            if (solution[i] >= nitems[i]) {
                // Solution contains an item that does not exist
                newfile.close();
                return 3;
            }
        }
        newfile.close();
    } else {
        // Cannot open file
        return 1;
    }

    cout << "Done." << endl;
    return 0;
}

int data::read_time(const string& instance) {
    fstream newfile;
    newfile.open(instance, ios::in);
    if (newfile.is_open()) {
        newfile >> ptime;
    } else {
        return 1;
    }
    return 0;
}

int data::verify_solution(double *val) {
    cout << "Verify solution: " << endl;
    double tmpval = 0.0;
    vector<int> consumption(nresources, 0);

    // Cycle through all classes
    for (auto i = 0; i < nclasses; i++) {
        // Add value of solution of class i
        tmpval += values[i][solution[i]];

        // Print solution + related weights
        cout << "[Class #"<< i << "] " << values[i][solution[i]] << " (index: " << solution[i] << ") = ";
        cout << "[";
        for (auto k = 0; k < nresources; k++) {
            cout << weights[i][solution[i] * nresources + k] << " ";
        }
        cout << "]" << endl;

        // Compute current knapsack consumption after picking solution of class i
        for (auto k = 0; k < nresources; k++) {
            consumption[k] += weights[i][solution[i] * nresources + k];

            // Check if knapsack is overloaded
            if (consumption[k] > capacities[k]) {
                cout << "Unfeasible on resource " << k << " (consumption: " << consumption[k] << ", capacity: " << capacities[k] << ")" << endl;

                cout << "Print current knapsack remaining: ";
                for (auto k = 0; k < nresources; k++) {
                    cout << capacities[k] - consumption[k] << " ";
                }
                cout << endl;

                return 1;
            }
        }

        for (auto k = 0; k < nresources; k++) {
            cout << capacities[k] - consumption[k] << " ";
        }
        cout << endl;
    }

    // Print current knapsack consumption
    cout << "Consumption: ";
    for (auto k = 0; k < nresources; k++) {
        cout << consumption[k] << " ";
    }
    cout << endl;

    *val = tmpval;
    cout << "Feasible, value " << tmpval << endl;
    return 0;
}
