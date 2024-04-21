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

    void PrintFunction(struct Node *node)
    {
        /*
            Page No. 8
            Heading: Print Function
        */
        if (node == nullptr)
            return;
        else if (node->type == OPERATOR)
        {
            std::cout << "(";
            PrintFunction(node->leftNode);
            std::cout << node->value;
            PrintFunction(node->rightNode);
            std::cout << ")";
        }
        else if (node->type == FUNCTION)
        {
            std::cout << node->value << "(";
            PrintFunction(node->leftNode);
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
};