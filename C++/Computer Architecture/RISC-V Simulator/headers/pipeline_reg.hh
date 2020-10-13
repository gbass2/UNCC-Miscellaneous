#ifndef PIPELINE_REG_H
#define PIPELINE_REG_H

#include <string>
#include <vector>
#include <deque>
#include <tuple>


class PipelineReg{
protected:
    std::deque<std::string> instructionQueue  = {"fld","fadd.d","fsd", "addi", "bne", "halt"}; // Holds the instruction set. In order for assignement 2
    std::deque<std::tuple<std::string,std::string,std::string>> registers = {{"f0","0(x1)",""}, {"f4","f0","f2"}, {"f4","0(x1)",""}, {"x1","x1","-8"},{"x1","x2",""}, {"","",""}}; // Holds the register names being used for assignment 2

    friend class Pipeline; // Allows Pipeline class to access these private variables
    friend class CPU; // Allows Store class to access these private variables

};

# endif // PIPELINE_REG_H
