#include<iostream>
#include"Function.hpp"
int main()
{
    Function fn = Function();
    struct Node* node = fn.CreateNode(OPERATOR, "+", fn.CreateNode(VARIABLE, "x"), fn.CreateNode(FUNCTION, "sin", fn.CreateNode(OPERATOR , "+", fn.CreateNode(OPERATOR, "^", fn.CreateNode(VARIABLE, "x"), fn.CreateNode(CONSTANT, "3")), fn.CreateNode(CONSTANT, "4"))));
    fn.PrintFunction(node);
    std::cout << std::endl;
    return 0;
}