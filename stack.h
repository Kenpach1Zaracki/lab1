#ifndef STACK_H
#define STACK_H

#include <string>

struct StackNode {
    std::string data;
    StackNode* next;
};

struct Stack {
    std::string name;
    StackNode* top;
};

Stack* create_stack(const std::string& name);
void stack_push(Stack* stack, const std::string& value);
std::string stack_pop(Stack* stack);
std::string stack_peek(const Stack* stack);
std::string stack_read(const Stack* stack);
void destroy_stack(Stack* stack);

#endif
