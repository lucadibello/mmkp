#ifndef __DATA_H
#define __DATA_H
#include <string>
#include <vector>

class data
{
public:

    int nclasses;
    int nresources;
    std::vector<int> capacities;
    std::vector<int> nitems;
    std::vector<std::vector<int>> values;
    std::vector<std::vector<int>> weights;
    std::vector<int> solution;
    double ptime;

    int read_input(const std::string& instance);
    int read_output(const std::string& instance);
    int read_time(const std::string& instance);
    int verify_solution(double* val);
};

#endif