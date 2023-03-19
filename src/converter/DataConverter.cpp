//
// Created by Manuele Nolli on 16.03.2023.
//
#include <cstring>
#include "src/data.h"
#include <cstdio>
#include <thread>
#include <iostream>
#include <fstream>


static Data instance;

char *getOption(int argc, char *argv[], const char *option) {
    for (int i = 0; i < argc; ++i)
        if (strcmp(argv[i], option) == 0)
            return argv[i + 1];
    return nullptr;
}


int main(int argc, char *argv[]) {
    char *input = getOption(argc, argv, std::string("-i").c_str());

    instance.read_input(input);

    std::string output = input;
    output.append(".dat");
    std::cout << "Output name:" << output << "\n";
    std::ofstream outfile(output);
    std::cout.rdbuf(outfile.rdbuf());

    // Print information related to dataset
    //printf("\nTotal classes: %d, Total items: %d\n", instance.nclasses, instance.nresources);
    for (auto i = 0; i < instance.nresources; i++) {
        //printf("Class n: %d has capacity of %d\n", i, instance.capacities[i]);

        // Print the items of the class (value + weights)
        for (auto j = 0; j < instance.nitems[i]; j++) {
            //printf("Item n: %d has value of %d and weights of ", j, instance.values[i][j]);
            for (auto k = 0; k < instance.nresources; k++) {
                //printf("%d ", instance.weights[i][j * instance.nresources + k]);
            }
            // printf("\n");
        }
    }

    std::cout << "%%writefile " << output << std::endl;

    int nClasses = instance.nclasses;
    int nItems = instance.nitems[0];
    int nResources = instance.nresources;

    std::cout << "param nc := " << nClasses  << ";" << std::endl;
    std::cout << "param nn := " << nItems << ";" << std::endl;
    std::cout << "param nr := " << nResources << ";" << std::endl;

    std::cout << std::endl;

    std::cout << "# Max capacity" << std::endl;
    std::cout << "param q :=" << std::endl;
    for (int i = 0; i < instance.capacities.size(); i++) {
        std::cout << "\t" << i + 1 << " " << instance.capacities[i] << std::endl;
    }
    std::cout << ";" << std::endl;


    std::cout << std::endl;

    std::cout << "# Volume (columns = N = items,  rows = C = classes)" << std::endl;
    std::cout << "param v (tr): ";
    for (int c = 0; c < nClasses; c++) {
        std::cout << c + 1 << " ";
    }
    std::cout << ":= " << std::endl;

    // Print volume matrix
    for (int i = 0; i < nItems; i++) {
        std::cout << i + 1;
        for (int c = 0; c < nClasses; c++) {
            std::cout << " " << instance.values[c][i];
        }
        std::cout << std::endl;
    }
    std::cout << ";" << std::endl;
    std::cout << std::endl;

    std::cout << "# Weights" << std::endl;
    std::cout << "param w := ";
    for (int r = 0; r < nResources; r++) {
        std::cout << "# Resource" << r + 1 << " (columns = N = items,  rows = C = classes)" << std::endl;

        std::cout << "[*,*," << r + 1 << "](tr):" << " ";
        for (int c = 0; c < nClasses; c++) {
            std::cout << c + 1 << " ";
        }
        std::cout << ":= " << std::endl;

        for (int i = 0; i < nItems; i++) {
            std::cout << i + 1 << " ";
            for (int c = 0; c < nClasses; c++) {
               std::cout << instance.weights[c][i * nResources + r] << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << ";" << std::endl;
}