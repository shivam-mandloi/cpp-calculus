#pragma once

#include "Node.hpp"

class Function
{
public:
    struct Node* CreateNode(NodeType nodeType, std::string value, struct Node *leftNode = nullptr, struct Node *rightNode = nullptr)
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
};