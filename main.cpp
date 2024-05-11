#include <iostream>
#include "Derivation.hpp"
#include "ExpressionTree.hpp" // for testing will be removed

int main()
{
    Function fn;
    Derivation dr;
    // 2(x^3 + 2x + 3)^4
    // struct Node *node = fn.CreateNode(OPERATOR, "-", fn.CreateNode(CONSTANT, "1"), fn.CreateNode(OPERATOR, "^", fn.CreateNode(VARIABLE, "x"), fn.CreateNode(CONSTANT, "0.11111")));
    // fn.PrintFunction(node);
    // std::cout << std::endl;
    // struct Node *der = dr.Find_Derivative(node);
    // fn.PrintFunction(der);
    std::string str = "sin(sin(a + log(x/2)) * 2 + 1) + log(x) * 2";
    ConvertToExpression ctf;
    ctf.Convert(str);
    // std::cout << std::endl;
    return 0;
}