#pragma once

#include<string>
#include "NodeType.hpp"

// Structure representing a node in a function expression tree.
struct Node
{
    NodeType type;          // Type of the node (e.g., OPERATOR, FUNCTION, CONSTANT).
    std::string value;      // Value associated with the node (e.g., operator symbol, function name, constant value).
    struct Node *leftNode;  // Pointer to the left child node.
    struct Node *rightNode; // Pointer to the right child node.

    // Constructor to initialize the node with default values.
    Node(): type(CONSTANT), value("1"), leftNode(nullptr), rightNode(nullptr){}
};
