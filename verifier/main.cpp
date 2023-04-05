#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <cstring>
#include "data.h"

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

int main(int argc, char *argv[]) {

    char* timelimit = getOption(argc, argv, std::string("-t").c_str());
    char* input = getOption(argc, argv, std::string("-i").c_str());
    char* stats = getOption(argc, argv, std::string("-s").c_str());
    char* instancesDir = getOption(argc, argv, std::string("-d").c_str());

    // check if user wants to run a set of instances
    if (input == nullptr && instancesDir != nullptr) {
        std::cout << "[!] Running all instances in directory " << instancesDir << "\n";
        exit(1);
    }

    if (timelimit == nullptr || input == nullptr){
        std::cout << "[!] Parameters are not correctly specified!\n";

        // Print usage
        std::cout << "Usage: " << argv[0] << " -i <input> -t <timelimit> [-s <stats>]\n";
        std::cout << "\t-i <input> : Input file name\n";
        std::cout << "\t-t <timelimit> : Time limit in seconds\n";
        std::cout << "\t-s <stats> : Stats file name\n";

        exit(1);
    }

    int inttimelimit = atoi(timelimit);
    std::cout << "Instance path:" << input << "\n" ;
    std::cout << "Time limit: " << inttimelimit << " seconds" << "\n" ;
    std::string output(input);
    output.append(".out");
    std::cout << "Output file path:" << output << "\n";

    if (stats == nullptr){
        // Notify that we are running a trivial solution
        std::cout << "[!] Running trivial solution, no stats will be generated\n";

        // Run trivial code to get a solution
        data instance;
        instance.read_input(input);
        std::ofstream outfile;
        outfile.open(output, std::ios_base::out);

        // Check if output file can be opened
        if (!outfile.is_open()) {
            std::cout << "Cannot open output file\n";
            exit(1);
        }

        for (auto i = 0; i<instance.nclasses; i++){
            outfile << instance.solution[i] << " ";
        }
        outfile.close();
    } else {
        std::string time(input);
        time.append(".time");
        std::cout << "Time file path:" << time << "\n";

        // Open stats in append
        std::ofstream outfile;
        outfile.open(stats, std::ios_base::app);

        if (!exists(input)) {
            outfile << "," << input << ",0.0,0.0,Input does not exist" << std::endl;
            outfile.close();
            exit(0);
        } else if (!exists(output)) {
            outfile << "," << input << ",0.0,0.0,Output does not exist" << std::endl;
            outfile.close();
            exit(0);
        } else if (!exists(time)) {
            outfile << "," << input << ",0.0,0.0,Time does not exist" << std::endl;
            outfile.close();
            exit(0);
        }

        data instance;
        int res = instance.read_input(input);
        if (res == 1) {
            outfile << "," << input << ",0.0,0.0,Cannot open output" << std::endl;
            outfile.close();
            exit(0);
        }
        if (res == 2) {
            outfile << "," << input << ",0.0,0.0,Not enough selected items" << std::endl;
            outfile.close();
            exit(0);
        }
        if (res == 3) {
            outfile << "," << input << ",0.0,0.0,Selected item does not exist" << std::endl;
            outfile.close();
            exit(0);
        }
        res = instance.read_time(time);
        if (res == 1) {
            outfile << "," << input << ",0.0,0.0,Unable to read time" << std::endl;
            outfile.close();
            exit(0);
        }


        // Load solutions from output file
        res = instance.read_output(output);
        if (res == 1) {
            outfile << "," << input << ",0.0,0.0,Unable to read output" << std::endl;
            outfile.close();
            exit(0);
        } else if (res == 2) {
            outfile << "," << input << ",0.0,0.0,Not enough selected items" << std::endl;
            outfile.close();
            exit(0);
        } else if (res == 3) {
            outfile << "," << input << ",0.0,0.0,Selected item does not exist" << std::endl;
            outfile.close();
            exit(0);
        }

        double value = 0.0;
        res = instance.verify_solution(&value);
        if (res == 1) {
            outfile << "," << input << ",0.0,0.0,Solution is not feasible" << std::endl;
            outfile.close();
            exit(0);
        }

        outfile << "," << input << "," << value << "," << instance.ptime << ",Solution is feasible" << std::endl;
        outfile.close();
        exit(0);
    }
}
