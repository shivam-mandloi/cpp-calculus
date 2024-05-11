#pragma once

#include<vector>
#include "Node.hpp"

class ConvertToExpression
{
    bool IsOperator(char ch)
    {
        return ch == '/' || ch == '*' || ch == '^' || ch == '+' || ch == '-' ? true : false;
    }

    std::vector<std::string> ConvertToVector(std::string func)
    {
        /*
            This function converts a string into a vector 
            because the function may contain not only operators but also trigonometric functions.
        */
        std::vector<std::string> funcVec;
        int index = 0;
        while(index != func.size())
        {

        }
    }

    std::vector<std::string> ConvertToPostFix(std::vector<std::string> func)
    {
        /*
This function converts an infix expression to a postfix expression.
*/

    }

    struct Node* Convert(std::string func)
    {
        /*
            This function converts a user-provided function, given in infix notation, into an expression tree.
            This tree structure is utilized by other functions, such as derivative calculations.
        */
    }
};