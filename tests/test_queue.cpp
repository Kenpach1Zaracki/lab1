#include <gtest/gtest.h>
#include "../queue.h"

class QueueTest : public ::testing::Test {
protected:
    Queue* queue;
    void SetUp() override {
        queue = create_queue("test_queue");
    }
    void TearDown() override {
        destroy_queue(queue);
    }
};

TEST_F(QueueTest, PushPopFront) {
    queue_push(queue, "a");
    queue_push(queue, "b");
    EXPECT_EQ(queue_front(queue), "a");
    EXPECT_FALSE(queue_is_empty(queue));
    queue_pop(queue);
    EXPECT_EQ(queue_front(queue), "b");
    queue_pop(queue);
    EXPECT_TRUE(queue_is_empty(queue));
}

TEST_F(QueueTest, IsEmptySize) {
    EXPECT_TRUE(queue_is_empty(queue));
    EXPECT_EQ(queue_size(queue), 0);
    queue_push(queue, "x");
    EXPECT_EQ(queue_size(queue), 1);
}

TEST_F(QueueTest, Find) {
    queue_push(queue, "m");
    queue_push(queue, "n");
    EXPECT_TRUE(queue_find(queue, "m"));
    EXPECT_FALSE(queue_find(queue, "notfound"));
}

TEST_F(QueueTest, Read) {
    queue_push(queue, "r");
    queue_push(queue, "z");
    EXPECT_EQ(queue_read(queue), "r z");
}

TEST_F(QueueTest, PopEmpty) {
    queue_pop(queue); // безопасно
    EXPECT_TRUE(queue_is_empty(queue));
}

TEST_F(QueueTest, BenchmarkPushPop) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        queue_push(queue, std::to_string(i));
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        queue_pop(queue);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur_push = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);
    auto dur_pop = std::chrono::duration_cast<std::chrono::microseconds>(end - mid);
    std::cout << "Push 1000: " << dur_push.count() << " us, Pop 1000: " << dur_pop.count() << " us\n";
}
