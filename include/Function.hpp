#pragma once

#include <iostream>
#include "Node.hpp"

class Function
{
public:
    struct Node *CreateNode(NodeType nodeType, std::string value, struct Node *leftNode = nullptr, struct Node *rightNode = nullptr)
    {
        /*
            Page No. 6
            Heading: CreateNode Function
        */
        Node *node = new Node();
        node->type = nodeType;
        node->value = value;
        node->leftNode = leftNode;
        node->rightNode = rightNode;
        return node;
    }

    int Priority(struct Node *node)
    {
        if(node->value == "+" || node->value == "-" || node->type == FUNCTION)
            return 1;
        if(node->value == "*" || node->value == "/")
            return 2;
        return 3;
    }

    void PrintWithPriority(struct Node *node, int priority)
    {
        /*
            Page No. 8
            Heading: Print Function
        */
        if (node == nullptr)
            return;
        else if (node->type == OPERATOR)
        {
            if(priority > Priority(node))
                std::cout << "(";
            PrintWithPriority(node->leftNode, Priority(node));
            std::cout << node->value;
            PrintWithPriority(node->rightNode, Priority(node));
            if(priority > Priority(node))
                std::cout << ")";
        }
        else if (node->type == FUNCTION)
        {
            std::cout << node->value << "(";
            PrintWithPriority(node->leftNode, Priority(node));
            std::cout << ")";
        }
        else if (node->type == VARIABLE)
        {
            std::cout << node->value;
        }
        else if (node->type == CONSTANT)
        {
            std::cout << node->value;
        }
    }

    void PrintFunction(struct Node *node)
    {
        /*
            used to call the PrintWithPriority function
        */
        PrintWithPriority(node, Priority(node));
    }
};