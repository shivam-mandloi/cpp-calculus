#pragma once

#include <vector>
#include <iostream> // temp func will be removed / only for testing
#include "Function.hpp"

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

    void ResetVariable()
    {
        // used to reset variable used in function as static
        staticiIndex = 0;
        startIndex = 0;
        vecFunc = {};
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

    bool IsNumber(std::string str)
    {
        // check if string is number
        // used to find for constant
        for (auto ch : str)
        {
            if (!isdigit(ch) && ch != '-')
                return false;
        }
        return str == "-" ? false : true;
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
                if (str == "-" && func[index] == '1')
                {
                    str += func[index];
                    index += 1;
                }
                funcVec.push_back(str);
            }
            else if (isdigit(str[0]))
            {
                while (index < func.size() && isdigit(func[index]))
                {
                    str += func[index];
                    index += 1;
                }
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
        while (stack.size() || vec[index] != ")")
        {
            if (vec[index] == "(")
                stack.push_back("(");
            else if (vec[index] == ")")
                stack.pop_back();
            index += 1;
        }
        return index;
    }

    std::vector<std::string> ConvertToPostFix(std::vector<std::string> func, int endIndex)
    {
        /*
            This function converts an infix expression to a postfix expression.
        */
        std::vector<std::string> stack;
        while (startIndex < endIndex)
        {
            if (func[startIndex] == "(")
            {
                stack.push_back(func[startIndex]);
            }
            else if (func[startIndex] == ")")
            {
                while (stack.back() != "(")
                {
                    vecFunc.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
            }
            else if (IsOperator(func[startIndex]))
            {
                while (stack.size() && Priority(func[startIndex]) < Priority(stack.back()))
                {
                    vecFunc.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(func[startIndex]);
            }
            else if (IsFunction(func[startIndex]))
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
        while (stack.size())
        {
            vecFunc.push_back(stack.back());
            stack.pop_back();
        }
        return vecFunc;
    }

    struct Node *ConvertToExpressionTree(std::vector<std::string> funcVec, int endIndex)
    {
        std::vector<struct Node *> stack;
        while (staticiIndex < endIndex)
        {
            if (IsOperator(funcVec[staticiIndex]))
            {
                struct Node *right = stack.back();
                stack.pop_back();
                struct Node *left = stack.back();
                stack.pop_back();
                struct Node *temp = fn.CreateNode(OPERATOR, funcVec[staticiIndex], left, right);
                if(temp->value == "*")
                    temp = hf.OptimizeFunction(temp->leftNode, temp->rightNode);
                stack.push_back(temp);
            }
            else if (IsFunction(funcVec[staticiIndex]))
            {
                struct Node *temp = fn.CreateNode(FUNCTION, funcVec[staticiIndex]);
                staticiIndex += 2;
                int tempIndex = FindClosingParen(funcVec, staticiIndex);
                temp->leftNode = ConvertToExpressionTree(funcVec, tempIndex);
                stack.push_back(temp);
            }
            else
            {
                struct Node *temp;
                if (IsNumber(funcVec[staticiIndex]))
                    temp = fn.CreateNode(CONSTANT, funcVec[staticiIndex]);
                else
                    temp = fn.CreateNode(VARIABLE, funcVec[staticiIndex]);
                stack.push_back(temp);
            }
            staticiIndex += 1;
        }
        return stack.back();
    }
    struct Node *Convert(std::string func)
    {
        /*
            This function converts a user-provided function, given in infix notation, into an expression tree.
            This tree structure is utilized by other functions, such as derivative calculations.
        */
        std::vector<std::string> funcVec = ConvertToVector(func);
        PrintVector(funcVec);
        funcVec = ConvertToPostFix(funcVec, funcVec.size());
        PrintVector(funcVec);
        struct Node *temp = ConvertToExpressionTree(funcVec, funcVec.size());
        fn.PrintFunction(temp);
        std::cout << std::endl;
        ResetVariable();
        return temp;
    }

private:
    Function fn; // Initialize in Function.hpp
    HelpingFunction hf;
    int staticiIndex = 0;
    int startIndex = 0;
    std::vector<std::string> vecFunc = {};
};