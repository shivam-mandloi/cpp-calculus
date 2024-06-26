#pragma once

#include <unordered_map>
#include "Function.hpp"

class HelpingFunction
{
public:
    // Copy a function node to create a deep copy.
    struct Node *CopyFunction(struct Node *node)
    {
        /*
            This function creates a deep copy of a given function node.
            It is particularly useful in differentiation as it allows us to manipulate a copy of the function without altering the original.
        */
        if (!node)
            return nullptr;
        struct Node *newNode = new Node();
        newNode->type = node->type;
        newNode->value = node->value;
        newNode->leftNode = CopyFunction(node->leftNode);
        newNode->rightNode = CopyFunction(node->rightNode);
        return newNode;
    }

    // Optimize a function node representing a multiplication operation.
    struct Node *OptimizeFunction(struct Node *left, struct Node *right)
    {
        /*
            This function is used in the context of function differentiation, specifically for the operator node '*' and '/'.
            It handles cases where two functions are multiplied together, optimizing the resulting function node.
            There are four potential cases:
                1. When both functions are constants.
                2. When one function is a constant and the other is a function.
                3. When one function is a function and the other is a constant.
                4. When both functions are functions.
        */
        if (left->value == "0" || right->value == "0")
            return fn.CreateNode(CONSTANT, "0");
        if (right->type == CONSTANT)
        {
            if (left->type == CONSTANT)
                left->value = std::to_string(std::stod(left->value) * std::stod(right->value));
            else if (left->type == OPERATOR && left->value == "*" && left->leftNode->type == CONSTANT)
                left->leftNode->value = std::to_string(std::stod(right->value) * std::stod(left->leftNode->value));
            else
                left = fn.CreateNode(OPERATOR, "*", right, left);
        }
        else if (right->type == OPERATOR && right->value == "*" && right->leftNode->type == CONSTANT)
        {
            if (left->type == CONSTANT)
                right->leftNode->value = std::to_string(std::stod(left->value) * std::stod(right->leftNode->value));
            else if (left->type == OPERATOR && left->value == "*" && left->leftNode->type == CONSTANT)
                right = fn.CreateNode(OPERATOR, "*", fn.CreateNode(CONSTANT, std::to_string(std::stod(left->leftNode->value) * std::stod(right->leftNode->value))), fn.CreateNode(OPERATOR, "*", left->rightNode, right->rightNode));
            else
                right = fn.CreateNode(OPERATOR, "*", right, left);
            left = right;
        }
        else
        {
            left = fn.CreateNode(OPERATOR, "*", left, right);
        }
        return left;
    }

    // Derivative of trigonometric functions.
    struct Node *DerivativeTrigonometryFunction(struct Node *node)
    {
        struct Node *newNode;
        if (node->value == "sin")
            newNode = fn.CreateNode(FUNCTION, "cos", node->leftNode);
        if (node->value == "cos")
            newNode = fn.CreateNode(OPERATOR, "*", fn.CreateNode(CONSTANT, "-1"), fn.CreateNode(FUNCTION, "sin", node->leftNode));
        if (node->value == "tan")
            newNode = fn.CreateNode(OPERATOR, "^", fn.CreateNode(FUNCTION, "sec", node->leftNode), fn.CreateNode(CONSTANT, "2"));
        if (node->value == "cot")
            newNode = fn.CreateNode(OPERATOR, "*", fn.CreateNode(CONSTANT, "-1"), fn.CreateNode(OPERATOR, "^", fn.CreateNode(FUNCTION, "csc", node->leftNode), fn.CreateNode(CONSTANT, "2")));
        if (node->value == "sec")
            newNode = fn.CreateNode(OPERATOR, "*", fn.CreateNode(FUNCTION, "sec", node->leftNode), fn.CreateNode(FUNCTION, "tan", node->leftNode));
        if (node->value == "csc")
            newNode = fn.CreateNode(OPERATOR, "*", fn.CreateNode(CONSTANT, "-1"), newNode = fn.CreateNode(OPERATOR, "*", fn.CreateNode(FUNCTION, "sec", node->leftNode), fn.CreateNode(FUNCTION, "tan", node->leftNode)));
        if(node->value == "exp")
            newNode = fn.CreateNode(FUNCTION, "exp", node->leftNode);
        if(node->value == "log")
            newNode = fn.CreateNode(OPERATOR, "/", fn.CreateNode(CONSTANT, "1"), node->leftNode);
        return newNode;
    }

private:
    Function fn; // Instance of the Function class for function creation.
};

class Derivation
{
public:
    struct Node *OperatorNode(struct Node *node)
    {
        /*
            This function describes how different operators behave with respect to differentiation.
        */
        struct Node *newNode;
        if (node->value == "*")
        {
            // Derivative of product of two functions.
            struct Node *leftDer = Find_Derivative(node->leftNode);
            struct Node *rightDer = Find_Derivative(node->rightNode);
            if (leftDer->value != "0")
                leftDer = hf.OptimizeFunction(leftDer, node->rightNode);
            else
                leftDer = nullptr;
            if (rightDer->value != "0")
                rightDer = hf.OptimizeFunction(rightDer, node->leftNode);
            else
                rightDer = nullptr;
            if (rightDer && leftDer)
                newNode = fn.CreateNode(OPERATOR, "+", leftDer, rightDer);
            else if (rightDer)
                newNode = rightDer;
            else if (leftDer)
                newNode = leftDer;
            else
                newNode = fn.CreateNode(CONSTANT, "0");
        }

        if (node->value == "^")
        {
            // Derivative of power function.
            struct Node *tempNode = Find_Derivative(node->leftNode);
            struct Node *tempRightNode = node->rightNode;
            if (tempNode->type == OPERATOR)
            {
                if (tempNode->value == "*" && tempNode->leftNode->type == CONSTANT)
                {
                    tempNode->leftNode->value = std::to_string(std::stod(tempNode->leftNode->value) * std::stod(node->rightNode->value));
                    tempRightNode = tempNode;
                }
                else
                {
                    tempRightNode = fn.CreateNode(OPERATOR, "*", node->rightNode, tempNode);
                }
            }
            if (tempNode->type == CONSTANT)
            {
                if (tempNode->value != "1")
                {
                    tempNode->value = std::to_string(std::stod(tempNode->value) * std::stod(node->rightNode->value));
                    tempRightNode = tempNode;
                }
            }
            if (std::stod(node->rightNode->value) - 1 == 1)
                newNode = fn.CreateNode(OPERATOR, "*", tempRightNode, node->leftNode);
            else
                newNode = fn.CreateNode(OPERATOR, "*", tempRightNode, fn.CreateNode(OPERATOR, "^", node->leftNode, fn.CreateNode(CONSTANT, std::to_string(std::stod(node->rightNode->value) - 1))));
        }

        if (node->value == "+" || node->value == "-")
        {
            // Derivative of addition or subtraction.
            struct Node *leftDer = Find_Derivative(node->leftNode);
            struct Node *rightDer = Find_Derivative(node->rightNode);
            if (leftDer->type == CONSTANT && leftDer->value == "0")
                newNode = rightDer;
            else if (rightDer->type == CONSTANT && rightDer->value == "0")
                newNode = leftDer;
            else if (leftDer->type == CONSTANT && rightDer->type == CONSTANT)
            {
                if (node->value == "+")
                    rightDer->value = std::to_string(std::stod(leftDer->value) + std::stod(rightDer->value));
                else
                    rightDer->value = std::to_string(std::stod(leftDer->value) - std::stod(rightDer->value));
                newNode = rightDer;
            }
            else
                newNode = fn.CreateNode(OPERATOR, node->value, leftDer, rightDer);
        }

        else if (node->value == "/")
        {
            // Derivative of division.
            if (node->leftNode->type == CONSTANT && node->rightNode->type == CONSTANT)
                return fn.CreateNode(CONSTANT, "0");
            struct Node *leftNode = Find_Derivative(node->leftNode);
            if (node->rightNode->type == CONSTANT)
                return fn.CreateNode(OPERATOR, "/", leftNode, node->rightNode);
            struct Node *rightNode = Find_Derivative(node->rightNode);
            leftNode = hf.OptimizeFunction(leftNode, node->rightNode);
            if (node->leftNode->type == CONSTANT)
                rightNode = hf.OptimizeFunction(node->leftNode, rightNode);
            else
                rightNode = hf.OptimizeFunction(rightNode, node->leftNode);
            struct Node *power;
            if (node->rightNode->type == OPERATOR && node->rightNode->value == "^")
                node->rightNode = fn.CreateNode(OPERATOR, "^", node->rightNode->leftNode, hf.OptimizeFunction(fn.CreateNode(CONSTANT, "2"), node->rightNode->rightNode));
            else
                power = fn.CreateNode(CONSTANT, "2");
            if (leftNode->value == "0")
            {
                leftNode = hf.OptimizeFunction(fn.CreateNode(CONSTANT, "-1"), rightNode);

                newNode = fn.CreateNode(OPERATOR, "/", leftNode, node->rightNode);
            }
            else
            {
                newNode = fn.CreateNode(OPERATOR, "/", fn.CreateNode(OPERATOR, "-", leftNode, rightNode), node->rightNode);
            }
        }
        return newNode;
    }

    // Derivative of constant nodes.
    struct Node *ConstantNode(struct Node *node)
    {
        /*
            The derivative of a constant is always zero.
        */
        return fn.CreateNode(CONSTANT, "0");
    }

    // Derivative of variable nodes.
    struct Node *VariableNode(struct Node *node)
    {
        /*
            The derivative of any variable with power one is 1.
        */
        return fn.CreateNode(CONSTANT, "1");
    }
    // Derivative of function nodes.
    struct Node *FunctionNode(struct Node *node)
    {
        struct Node *trigDer = hf.DerivativeTrigonometryFunction(node);
        struct Node *valueDer = Find_Derivative(node->leftNode);
        if (valueDer->value == "0")
            return fn.CreateNode(CONSTANT, "0");
        if (valueDer->value == "1")
            return trigDer;
        return fn.CreateNode(OPERATOR, "*", valueDer, trigDer);
    }

    // Find the derivative of a function node.
    struct Node *Find_Derivative(struct Node *node)
    {
        /*
            This function calculates the derivative of a given function node.
            It is used both directly by the user and internally by other derivative functions.
            It handles cases based on the type of node (constant, variable, operator, or function).
        */
        struct Node *newnode = hf.CopyFunction(node);
        if (node->type == CONSTANT)
            return ConstantNode(newnode);
        if (node->type == VARIABLE)
            return VariableNode(newnode);
        if (node->type == OPERATOR)
            return OperatorNode(newnode);
        return FunctionNode(newnode);
    }

private:
    Function fn;        // Instance of the Function class for function creation.
    HelpingFunction hf; // Instance of the HelpingFunction class for auxiliary functions.
};
