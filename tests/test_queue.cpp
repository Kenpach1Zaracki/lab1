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

TEST_F(QueueTest, PushPop) {
    queue_push(queue, "a");
    queue_push(queue, "b");
    EXPECT_EQ(queue_pop(queue), "a");
    EXPECT_EQ(queue_pop(queue), "b");
    EXPECT_THROW(queue_pop(queue), std::runtime_error);
}

TEST_F(QueueTest, IsEmptyManual) {
    EXPECT_THROW(queue_pop(queue), std::runtime_error);
    queue_push(queue, "x");
    EXPECT_EQ(queue_pop(queue), "x");
    EXPECT_THROW(queue_pop(queue), std::runtime_error);
}

TEST_F(QueueTest, Read) {
    queue_push(queue, "m");
    queue_push(queue, "n");
    EXPECT_EQ(queue_read(queue), "m n");
}

TEST_F(QueueTest, BenchmarkPushPop) {
    for (int i = 0; i < 1000; ++i) {
        queue_push(queue, std::to_string(i));
    }
    int count = 0;
    try {
        while (true) {
            queue_pop(queue);
            count++;
        }
    } catch (const std::runtime_error&) {}
    EXPECT_EQ(count, 1000);
}
