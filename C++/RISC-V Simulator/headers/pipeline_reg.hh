#ifndef PIPELINE_REG_H
#define PIPELINE_REG_H

#include <string>
#include <vector>


class PipelineReg{
private:
    std::vector<std::string> instructionsQueue {"fld","fadd.d","fsd", "addi", "bne", "halt"}; // Hold the instruction set. Currently in order for assignemnt 2
    std::vector<double *> memory; // Stores the values from the store stage only for assignment 2
    // Temorarily stores the reuslt until the store stage for assignment 2
    double f0, f2, f4;

    friend class Pipeline; // Allows Pipeline class to access these private variables
};

# endif // PIPELINE_REG_H
