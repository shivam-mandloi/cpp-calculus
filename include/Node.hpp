#pragma once

#include<string>
#include "NodeType.hpp"

struct Node
{
    NodeType type;
    std::string value;
    struct Node *leftNode;
    struct Node *rightNode;
    Node(): type(CONSTANT), value("1"), leftNode(nullptr), rightNode(nullptr){}
};


