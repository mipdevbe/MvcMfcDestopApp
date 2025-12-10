#pragma once
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

class ThreadingBase
{

public:
    ThreadingBase()
    {
    }

    virtual ~ThreadingBase()
    {
        if (running)
            stop();
    }

    void start()
    {
        if (running)
            return;

        stopRequested.store(false);
        thread = std::thread(&ThreadingBase::doWork, this);
        running = true;
    }

    void stop()
    {
        if (!running)
            return;

        stopRequested.store(true);
        if (thread.joinable())
            thread.join();

        running = false;
    }

    bool isRunning() const { return running; }


    std::atomic<bool> isStopRequested() const { return stopRequested.load(); }

protected:
    virtual void doWork() = 0; // to be implemented by derived class
    std::atomic<bool> stopRequested{ false };

private:
    std::thread thread;
    bool running{ false };
};

