#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue {
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        cv_.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [&] {
            return !queue_.empty();
        });

        value = queue_.front();
        queue_.pop();
        return true;
    }
};