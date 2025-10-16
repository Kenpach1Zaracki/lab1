#include "stack.h"
#include <stdexcept>

// Создание пустого стека
Stack* create_stack(const std::string& name) {
    Stack* stack = new Stack;
    stack->name = name;
    stack->top = nullptr;
    return stack;
}
// Добавление элемента
void stack_push(Stack* stack, const std::string& value) {
    StackNode* newNode = new StackNode{value, stack->top};
    stack->top = newNode;
}
// Удаление и возврат верхнего элемента
std::string stack_pop(Stack* stack) {
    if (!stack->top) throw std::runtime_error("Stack is empty");
    StackNode* temp = stack->top;
    std::string value = temp->data;
    stack->top = stack->top->next;
    delete temp;
    return value;
}
// Просмотр верхнего элемента без удаления
std::string stack_peek(const Stack* stack) {
    if (!stack->top) throw std::runtime_error("Stack is empty");
    return stack->top->data;
}
// Чтение всех элементов
std::string stack_read(const Stack* stack) {
    std::string result;
    StackNode* current = stack->top;
    while (current) {
        if (!result.empty()) result += " ";
        result += current->data;
        current = current->next;
    }
    return result;
}

void destroy_stack(Stack* stack) {
    while (stack->top) {
        stack_pop(stack);
    }
    delete stack;
}
