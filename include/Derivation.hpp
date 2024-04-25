#pragma once

#include <unordered_map>
#include "Function.hpp"

class HelpingFunction
{
public:
    struct Node *CopyFunction(struct Node *node)
    {
        /*
            used to copy node, very usefull in derivation because it allow us to not change actual function value
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

    struct Node *OptimizeFunction(struct Node *left, struct Node *right)
    {
        /*
            used in derivation Function where case is operator node *
            this function used when two function are multiplied, y = F(x) * G(x)
            there are four cases can be encounter
            when
            f(x) = 2(constant) and g(x) = 3(constant) => y = 6
            f(x) = 2(constant) and g(x) = 3 * x^2 (example) => y = 6 * x^2
            f(x) = 2(x+2) and g(x) = 3(constant) => y = 6(x+2)
            f(x) = 2(x+2) and g(x) = 3 * x^2 => y = 6 * (x+2) * x^2
        */
        if (left->value == "0" || right->value == "0")
            return fn.CreateNode(CONSTANT, "0");
        if (right->type == CONSTANT)
        {
            if (left->type == CONSTANT)
                left->value = std::to_string(std::stoi(left->value) * std::stoi(right->value));
            else if (left->type == OPERATOR && left->value == "*" && left->leftNode->type == CONSTANT)
                left->leftNode->value = std::to_string(std::stoi(right->value) * std::stoi(left->leftNode->value));
            else
                left = fn.CreateNode(OPERATOR, "*", right, left);
        }
        else if (right->type == OPERATOR && right->value == "*" && right->leftNode->type == CONSTANT)
        {
            if (left->type == CONSTANT)
                right->leftNode->value = std::to_string(std::stoi(left->value) * std::stoi(right->leftNode->value));
            else if (left->type == OPERATOR && left->value == "*" && left->leftNode->type == CONSTANT)
                right = fn.CreateNode(OPERATOR, "*", fn.CreateNode(CONSTANT, std::to_string(std::stoi(left->leftNode->value) * std::stoi(right->leftNode->value))), fn.CreateNode(OPERATOR, "*", left->rightNode, right->rightNode));
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
        return newNode;
    }

private:
    Function fn;
};

class Derivation
{
public:
    struct Node *OperatorNode(struct Node *node)
    {
        /*
            function describe how different operator behave with derivative
        */
        struct Node *newNode;
        if (node->value == "*")
        {
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
            struct Node *tempNode = Find_Derivative(node->leftNode);
            struct Node *tempRightNode = node->rightNode;
            if (tempNode->type == OPERATOR)
            {
                if (tempNode->value == "*" && tempNode->leftNode->type == CONSTANT)
                {
                    tempNode->leftNode->value = std::to_string(std::stoi(tempNode->leftNode->value) * std::stoi(node->rightNode->value));
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
                    tempNode->value = std::to_string(std::stoi(tempNode->value) * std::stoi(node->rightNode->value));
                    tempRightNode = tempNode;
                }
            }
            if (std::stoi(node->rightNode->value) - 1 == 1)
                newNode = fn.CreateNode(OPERATOR, "*", tempRightNode, node->leftNode);
            else
                newNode = fn.CreateNode(OPERATOR, "*", tempRightNode, fn.CreateNode(OPERATOR, "^", node->leftNode, fn.CreateNode(CONSTANT, std::to_string(std::stoi(node->rightNode->value) - 1))));
        }

        if (node->value == "+" || node->value == "-")
        {
            struct Node *leftDer = Find_Derivative(node->leftNode);
            struct Node *rightDer = Find_Derivative(node->rightNode);
            if (leftDer->type == CONSTANT && leftDer->value == "0")
                newNode = rightDer;
            else if (rightDer->type == CONSTANT && rightDer->value == "0")
                newNode = leftDer;
            else if (leftDer->type == CONSTANT && rightDer->type == CONSTANT)
            {
                if (node->value == "+")
                    rightDer->value = std::to_string(std::stoi(leftDer->value) + std::stoi(rightDer->value));
                else
                    rightDer->value = std::to_string(std::stoi(leftDer->value) - std::stoi(rightDer->value));
                newNode = rightDer;
            }
            else
                newNode = fn.CreateNode(OPERATOR, node->value, leftDer, rightDer);
        }

        else if (node->value == "/")
        {
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

    struct Node *ConstantNode(struct Node *node)
    {
        /*
            constant derivative always zero
        */
        return fn.CreateNode(CONSTANT, "0");
    }

    struct Node *VariableNode(struct Node *node)
    {
        /*
            Any variable with power one give derivative 1
        */
        return fn.CreateNode(CONSTANT, "1");
    }

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

    struct Node *Find_Derivative(struct Node *node)
    {
        /*
            used by user to find derivative, apart from user it also used by different derivative function
            like the OperatorNode to find derivative if they encounter function which does not use operator
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
    Function fn;
    HelpingFunction hf;
};
