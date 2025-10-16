#include "queue.h"
#include <stdexcept>

// Создание пустой очереди
Queue* create_queue(const std::string& name) {
    Queue* queue = new Queue;
    queue->name = name;
    queue->front = queue->rear = nullptr;
    return queue;
}
// Добавление в конец очереди
void queue_push(Queue* queue, const std::string& value) {
    QueueNode* newNode = new QueueNode{value, nullptr};
    if (queue->rear) queue->rear->next = newNode; // Старый конец указывает на новый
    else queue->front = newNode;
    queue->rear = newNode;  // Новый узел становится концом
}
// Удаление из начала очереди
std::string queue_pop(Queue* queue) {
    if (!queue->front) throw std::runtime_error("Queue is empty");
    QueueNode* temp = queue->front;
    std::string value = temp->data;
    queue->front = queue->front->next;
    if (!queue->front) queue->rear = nullptr;
    delete temp;
    return value;
}
// Просмотр первого элемента
std::string queue_peek(const Queue* queue) {
    if (!queue->front) throw std::runtime_error("Queue is empty");
    return queue->front->data;
}
// Чтение всех элементов
std::string queue_read(const Queue* queue) {
    std::string result;
    QueueNode* current = queue->front;
    while (current) {
        if (!result.empty()) result += " ";
        result += current->data;
        current = current->next;
    }
    return result;
}

bool queue_empty(const Queue* queue) {
    return queue->front == nullptr;
}

void destroy_queue(Queue* queue) {
    while (queue->front) {
        queue_pop(queue);
    }
    delete queue;
}
