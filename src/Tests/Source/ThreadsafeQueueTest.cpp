#include <gtest/gtest.h>

#include "Precompile.h"

#include "Data/ThreadsafeQueue.h"


namespace Tetris::Tests
{

    using namespace Common;

    TEST(ThreadSafeQueueTest, PushPopSingleElement)
    {
        Data::ThreadsafeQueue<int> queue_;

        queue_.push(42);
        std::shared_ptr<int> value = queue_.try_pop();
        bool isEmpty(value);

        ASSERT_TRUE(isEmpty);
        EXPECT_EQ(*value, 42);
    }

    TEST(ThreadSafeQueueTest, PopEmptyQueue)
    {
        Data::ThreadsafeQueue<int> queue_;

        std::shared_ptr<int> value = queue_.try_pop();
        bool isEmpty(value);

        ASSERT_FALSE(isEmpty);
    }

    TEST(ThreadSafeQueueTest, PopMultipleElements)
    {
        Data::ThreadsafeQueue<int> queue_;

        for (int i = 0; i < 10; ++i) {
            queue_.push(i);
        }
        
        for (int i = 0; i < 10; ++i) {
            std::shared_ptr<int> value = queue_.try_pop();
            bool isEmpty(value);

            ASSERT_TRUE(isEmpty);
            EXPECT_EQ(*value, i);
        }
    }

    TEST(ThreadSafeQueueTest, ConcurrentPushPop)
    {
        Data::ThreadsafeQueue<int> queue_;
        const int num_threads = 10;
        const int num_elements_per_thread = 100;
        std::atomic<int> total_enqueued(0);
        std::atomic<int> total_dequeued(0);
    
        auto enqueue_task = [&queue_, &total_enqueued](int start)
        {
            for (int i = 0; i < num_elements_per_thread; ++i)
            {
                queue_.push(start + i);
                total_enqueued++;
            }
        };

        auto dequeue_task = [&queue_, &total_dequeued]()
        {
            for (int i = 0; i < num_threads * num_elements_per_thread; ++i) 
            {
                auto value = queue_.try_pop();
                total_dequeued++;
            }
        };

        std::vector<std::thread> threads;
        
        for (int i = 0; i < num_threads; ++i)
            threads.emplace_back(enqueue_task, i * num_elements_per_thread);

        threads.emplace_back(dequeue_task);

        for (auto& thread : threads)
            thread.join();

        EXPECT_EQ(total_enqueued.load(), total_dequeued.load());
    }

    TEST(ThreadSafeQueueTest, PopFromEmptyQueueInThread)
    {
        Data::ThreadsafeQueue<int> queue_;
        std::thread t([&queue_](){
            std::shared_ptr<int> value = queue_.try_pop();
            bool isEmpty(value);

            ASSERT_FALSE(isEmpty);
        });
        
        t.join();
    }

} // namespace