#include <iostream>
#include "Derivation.hpp"

int main()
{
    Function fn;
    Derivation dr;
    // 2(x^3 + 2x + 3)^4
    struct Node *node = fn.CreateNode(FUNCTION, "log", fn.CreateNode(FUNCTION , "cos", fn.CreateNode(VARIABLE, "x")));
    fn.PrintFunction(node);
    std::cout << std::endl;
    struct Node *der = dr.Find_Derivative(node);
    fn.PrintFunction(der);
    std::cout << std::endl;
    return 0;
}