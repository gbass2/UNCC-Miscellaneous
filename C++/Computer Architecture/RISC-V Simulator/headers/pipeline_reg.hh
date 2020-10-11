#ifndef PIPELINE_REG_H
#define PIPELINE_REG_H

#include <string>
#include <vector>
#include <deque>
#include <tuple>


class PipelineReg{
private:
    std::deque<std::string> instructionsQueue  = {"fld","fadd.d","fsd", "addi", "bne", "halt"}; // Holds the instruction set. Currently in order for assignemnt 2
    std::vector<std::tuple<std::string,std::string,std::string>> registers = {{"f0","0(X1)",""}, {"f4","f0","f2"}, {"f4","0(X1)",""}, {"x1","x1","-8"},{"x1","x2",""}}; // Holds the register names being used for assignment 2
    std::vector<double *> memory; // Stores the memory values. Not for assignment 2

    // double f0, f2, f4; // Temorarily stores the result until the store stage for assignment 2

    friend class Pipeline; // Allows Pipeline class to access these private variables
};

# endif // PIPELINE_REG_H
