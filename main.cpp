#include <iostream>
#include "Derivation.hpp"
#include "ExpressionTree.hpp" // for testing will be removed

int main()
{
    std::string func;
    std::cout << "Start Derivative :)" << std::endl;
    while(func != "q")
    {
        std::string func;
        ConvertToExpression ctf;
        Derivation dr;
        Function fn;
        std::cout << "Enter Function: ";
        std::getline(std::cin, func);
        struct Node *fun = ctf.Convert(func);
        struct Node *der = dr.Find_Derivative(fun);
        std::cout << "Derivative of Function: ";
        fn.PrintFunction(der);
        std::cout << std::endl;
    }
    return 0;
}