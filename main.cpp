#include<iostream>
#include"Function.hpp"
int main()
{
    Function fn = Function();
    struct Node* node = fn.CreateNode(OPERATOR, "+", fn.CreateNode(VARIABLE, "x"), fn.CreateNode(CONSTANT, "2"));
    return 0;
}