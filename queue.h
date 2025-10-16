#ifndef QUEUE_H
#define QUEUE_H

#include <string>

struct QueueNode {
    std::string data;
    QueueNode* next;
};

struct Queue {
    std::string name;
    QueueNode* front;
    QueueNode* rear;
};
bool queue_empty(const Queue* queue);
Queue* create_queue(const std::string& name);
void queue_push(Queue* queue, const std::string& value);
std::string queue_pop(Queue* queue);
std::string queue_peek(const Queue* queue);
std::string queue_read(const Queue* queue);
void destroy_queue(Queue* queue);

#endif
