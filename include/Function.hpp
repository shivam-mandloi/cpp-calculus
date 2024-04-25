#pragma once

#include <iostream>
#include "Node.hpp"

class Function
{
public:
    // Create a new function node.
    struct Node *CreateNode(NodeType nodeType, std::string value, struct Node *leftNode = nullptr, struct Node *rightNode = nullptr)
    {
        /*
            Creates a new function node with the specified type, value, left and right child nodes.
            Params:
                - nodeType: The type of the node (e.g., OPERATOR, FUNCTION, CONSTANT).
                - value: The value associated with the node.
                - leftNode: Pointer to the left child node.
                - rightNode: Pointer to the right child node.
            Returns:
                A pointer to the newly created node.
        */
        Node *node = new Node();
        node->type = nodeType;
        node->value = value;
        node->leftNode = leftNode;
        node->rightNode = rightNode;
        return node;
    }

    // Determine the priority of an operator node.
    int Priority(struct Node *node)
    {
        /*
            Determines the priority of an operator node based on its value.
            Params:
                - node: Pointer to the node.
            Returns:
                The priority value:
                    - 1 for addition, subtraction, or function nodes.
                    - 2 for multiplication or division nodes.
                    - 3 for other nodes.
        */
        if (node->value == "+" || node->value == "-" || node->type == FUNCTION)
            return 1;
        if (node->value == "*" || node->value == "/")
            return 2;
        return 3;
    }

    // Print a function expression with proper operator priority.
    void PrintWithPriority(struct Node *node, int priority)
    {
        /*
            Recursively prints a function expression with proper operator priority.
            Params:
                - node: Pointer to the current node being processed.
                - priority: The priority level of the operator that surrounds the current node.
        */
        if (node == nullptr)
            return;
        else if (node->type == OPERATOR)
        {
            if (priority > Priority(node))
                std::cout << "(";
            PrintWithPriority(node->leftNode, Priority(node));
            std::cout << node->value;
            PrintWithPriority(node->rightNode, Priority(node));
            if (priority > Priority(node))
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

    // Print a function expression.
    void PrintFunction(struct Node *node)
    {
        /*
            Prints a function expression using PrintWithPriority function.
            Params:
                - node: Pointer to the root node of the function expression.
        */
        PrintWithPriority(node, Priority(node));
    }
};