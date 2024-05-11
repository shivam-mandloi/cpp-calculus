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

    void FunctionPostFix(std::vector<std::string> vec, std::vector<std::string> *postFunc, int *index)
    {
        std::vector<std::string> stack;
        std::vector<std::string> parenStack;
        while(*index < vec.size())
        {
            //PrintVector(*postFunc);
            if(vec[*index] == ")")
            {
                if(!parenStack.size())
                    break;
                while(stack.back() != "(")
                {
                    postFunc->push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
                parenStack.pop_back();
            }
            else if(vec[*index] == "(")
            {
                stack.push_back("(");
                parenStack.push_back("(");
            }
            else if(IsOperator(vec[*index]))
            {
                while(stack.size() && Priority(stack.back()) > Priority(vec[*index]))
                {
                    postFunc->push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(vec[*index]);
            }
            else if(IsFunction(vec[*index]))
            {
                postFunc->push_back(vec[*index]);
                index+=2;
                postFunc->push_back("(");
                FunctionPostFix(vec, postFunc, index);
                postFunc->push_back(")");
                if(stack.size())
                {
                    postFunc->push_back(stack.back());
                    stack.pop_back();
                }
            }
            else
            {
                postFunc->push_back(vec[*index]);
            }
            (*index)+=1;
        }
        while(stack.size())
        {
            postFunc->push_back(stack.back());
            stack.pop_back();
        }
    }

    std::vector<std::string> ConvertToPostFix(std::vector<std::string> func)
    {
        /*
            This function converts an infix expression to a postfix expression.
        */
        std::vector<std::string> funcVec;
        std::vector<std::string> stack;
        int index = 0;
        while(index < func.size())
        {
            // PrintVector(funcVec);
            // std::cout << index << std::endl;
            if(func[index] == ")")
            {
                while(func[index] == "(")
                {
                    funcVec.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
            }
            else if (IsOperator(func[index]))
            {
                while(stack.size() && Priority(stack.back()) > Priority(func[index]))
                {
                    funcVec.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(func[index]);
            }
            else if (IsFunction(func[index]))
            {
                funcVec.push_back(func[index]);
                index+=2;
                funcVec.push_back("(");
                FunctionPostFix(func, &funcVec, &index);
                funcVec.push_back(")");
                if(stack.size())
                {
                    funcVec.push_back(stack.back());
                    stack.pop_back();
                }
            }
            else
            {
                funcVec.push_back(func[index]);
            }
            index++;
        }
        while(stack.size())
        {
            funcVec.push_back(stack.back());
            stack.pop_back();
        }
        return funcVec;
    }

    struct Node *Convert(std::string func)
    {
        /*
            This function converts a user-provided function, given in infix notation, into an expression tree.
            This tree structure is utilized by other functions, such as derivative calculations.
        */
        std::vector<std::string> funcVec = ConvertToVector(func);
        PrintVector(funcVec);
        PrintVector(ConvertToPostFix(funcVec));
        return nullptr;
    }
};