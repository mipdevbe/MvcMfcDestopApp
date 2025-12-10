#pragma once
#include <vector>
#include <mutex>
#include <queue>

using namespace std;

template <typename T>
class MessagingQueue
{
public:
    void push(const T& buf)
    {
        lock_guard<std::mutex> lock(mtx);
        messages.push(buf);

        cv.notify_one();
    }

    void push(const T&& buf)
    {
        lock_guard<std::mutex> lock(mtx);
        messages.push(buf);

        cv.notify_one();
    }

    bool pop(T& buf)
    {

        std::lock_guard<std::mutex> lock(mtx);
        if (messages.empty())
            return false;

        buf = std::move(messages.front());
        messages.pop();

        return true;
    }

private:
    std::queue<T> messages;
    mutex mtx;
    condition_variable cv;
};