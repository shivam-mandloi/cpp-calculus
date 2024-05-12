#pragma once

#include <vector>
#include <iostream> // temp func will be removed / only for testing
#include "Node.hpp"

class ConvertToExpression
{

    /*
        This class only recognise sin(a) not sina
        this rule is for every function
    */
public:
    void PrintVector(std::vector<std::string> vec)
    {
        // temp func will be removed
        // only for testing

        for (auto ch : vec)
        {
            std::cout << ch << ",";
        }
        std::cout << std::endl;
    }

    bool IsOperator(std::string ch)
    {
        // Return true if input is operator
        return ch == "/" || ch == "*" || ch == "^" || ch == "+" || ch == "-" || ch == "(" || ch == ")" ? true : false;
    }

    bool IsFunction(std::string ch)
    {
        // Return true if input is function
        return ch == "sin" || ch == "cos" || ch == "tan" || ch == "cot" || ch == "sec" || ch == "csc" || ch == "log" || ch == "exp" ? true : false;
    }

    int Priority(std::string ch)
    {
        // Return priority for different operator
        if (ch == "^")
            return 4;
        if (ch == "/" || ch == "*")
            return 3;
        if (ch == "+" || ch == "-")
            return 2;
        return 1;
    }

    std::vector<std::string> ConvertToVector(std::string func)
    {
        /*
            This function converts a string into a vector
            because the function may contain not only operators but also trigonometric functions.
        */
        std::vector<std::string> funcVec;
        int index = 0;
        std::cout << func << std::endl;
        while (index < func.size())
        {
            if (func[index] == ' ')
            {
                index += 1;
                continue;
            }
            std::string str = "";
            str += func[index];
            index += 1;
            if (IsOperator(str))
            {
                funcVec.push_back(str);
            }
            else
            {
                std::string tempStr = "";
                tempStr += func[index];
                while (index < func.size() && !IsOperator(tempStr))
                {
                    if (func[index] != ' ')
                        str += tempStr;
                    index += 1;
                    tempStr = "";
                    tempStr += func[index];
                }
                funcVec.push_back(str);
            }
        }
        return funcVec;
    }

    int FindClosingParen(std::vector<std::string> vec, int index)
    {
        std::vector<std::string> stack;
        while(stack.size() || vec[index] != ")")
        {
            if(vec[index] == "(")
                stack.push_back("(");
            else if(vec[index] == ")")
                stack.pop_back();
            index+=1;
        }
        return index;
    }

    std::vector<std::string> ConvertToPostFix(std::vector<std::string> func, int endIndex)
    {
        /*
            This function converts an infix expression to a postfix expression.
        */
        static std::vector<std::string> vecFunc;
        std::vector<std::string> stack;
        static int startIndex = 0;
        while(startIndex < endIndex)
        {
            if(func[startIndex] == "(")
            {
                stack.push_back(func[startIndex]);
            }
            else if(func[startIndex] == ")")
            {
                while(stack.back() != "(")
                {
                    vecFunc.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
            }
            else if(IsOperator(func[startIndex]))
            {
                while(stack.size() && Priority(func[startIndex]) < Priority(stack.back()))
                {
                    vecFunc.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(func[startIndex]);
            }
            else if(IsFunction(func[startIndex]))
            {
                vecFunc.push_back(func[startIndex]);
                startIndex += 2;
                int temp = FindClosingParen(func, startIndex);
                vecFunc.push_back("(");
                ConvertToPostFix(func, temp);
                vecFunc.push_back(")");
            }
            else
            {
                vecFunc.push_back(func[startIndex]);
            }
            startIndex += 1;
        }
        while(stack.size())
        {
            vecFunc.push_back(stack.back());
            stack.pop_back();
        }
        return vecFunc;
    }

    struct Node *Convert(std::string func)
    {
        /*
            This function converts a user-provided function, given in infix notation, into an expression tree.
            This tree structure is utilized by other functions, such as derivative calculations.
        */
        std::vector<std::string> funcVec = ConvertToVector(func);
        PrintVector(funcVec);
        PrintVector(ConvertToPostFix(funcVec, funcVec.size()));
        return nullptr;
    }
};