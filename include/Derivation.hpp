#pragma once

#include <unordered_map>
#include "Function.hpp"

class HelpingFunction
{
public:
    struct Node *CopyFunction(struct Node *node)
    {
        if (!node)
            return nullptr;
        struct Node *newNode = new Node();
        newNode->type = node->type;
        newNode->value = node->value;
        newNode->leftNode = CopyFunction(node->leftNode);
        newNode->rightNode = CopyFunction(node->rightNode);
        return newNode;
    }
};

class Derivation
{
public:
    struct Node *OperatorNode(struct Node *node)
    {
        struct Node *newNode;
        if (node->value == "*")
        {
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
        }
        return newNode;
    }

    struct Node *ConstantNode(struct Node *node)
    {
        return fn.CreateNode(CONSTANT, "0");
    }

    struct Node *VariableNode(struct Node *node)
    {
        return fn.CreateNode(CONSTANT, "1");
    }

    struct Node *FunctionNode(struct Node *node)
    {
        return node;
    }

    struct Node *Find_Derivative(struct Node *node)
    {
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
