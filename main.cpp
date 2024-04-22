#include<iostream>
#include"Derivation.hpp"

int main()
{
    Function fn;
    Derivation dr;
    // a * x**2 + b * x + c
    struct Node *node = fn.CreateNode(OPERATOR,"+",fn.CreateNode(OPERATOR, "+", fn.CreateNode(OPERATOR, "^", fn.CreateNode(VARIABLE, "x"), fn.CreateNode(CONSTANT, "15")), fn.CreateNode(VARIABLE, "x")),fn.CreateNode(CONSTANT, "1"));
    fn.PrintFunction(node);
    std::cout << std::endl;
    struct Node* der = dr.Find_Derivative(node);
    fn.PrintFunction(der);
    std::cout << std::endl;
    return 0;
}