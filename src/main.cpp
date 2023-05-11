#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "data.h"
#include "src/greedy/Greedy.h"
#include "src/metaheuristic/Metaheuristic.h"
#include <cstdlib>
#include <csignal>

static Data instance;
static std::string output;

char *getOption(int argc, char *argv[], const char *option)
{
    for (int i = 0; i < argc; ++i)
        if (strcmp(argv[i], option) == 0)
            return argv[i + 1];
    return nullptr;
}

inline bool exists(const std::string &name)
{
    return (access(name.c_str(), F_OK) != -1);
}

void writeSolution()
{
    std::ofstream outfile;
    outfile.open(output, std::ios_base::out);
    for (auto i = 0; i < instance.nclasses; i++)
    {
        outfile << instance.solution[i] << " ";
    }
    outfile.close();
}

void signalHandler(int signum)
{
    std::cout << "Running finalizing code. Interrupt signal (" << signum << ") received.\n";

    writeSolution();

    exit(signum);
}

int main(int argc, char *argv[])
{
    // register signal SIGINT and signal handler
    signal(SIGINT, signalHandler);

    char *timelimit = getOption(argc, argv, std::string("-t").c_str());
    char *input = getOption(argc, argv, std::string("-i").c_str());

    if (timelimit == nullptr || input == nullptr)
    {
        std::cout << "Parameters are not correctly specified!\n";
        std::exit(1);
    }

    int inttimelimit = atoi(timelimit);
    std::cout << "Instance name:" << input << "\n";
    std::cout << "Time limit:" << inttimelimit << "\n";
    output = input;
    output.append(".out");
    std::cout << "Output name:" << output << "\n";

    instance.read_input(input);

    // Compute greedy solution here!
    Greedy::compute(&instance, inttimelimit);

    // Compute local search here!
    Metaheuristic::compute(&instance, inttimelimit);
}
