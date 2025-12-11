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
        threadResults = std::thread(&ThreadingBase::doResultsWork, this);
        threadActions = std::thread(&ThreadingBase::doActionsWork, this);
        running = true;
    }

    void stop()
    {
        if (!running)
            return;

        stopRequested.store(true);
        if (threadResults.joinable())
            threadResults.join();

        if (threadActions.joinable())
            threadActions.join();

        running = false;
    }

    std::atomic<bool> isThreadRunning() const { return stopRequested.load(); }

protected:
    virtual void doActionsWork() = 0; // to be implemented by derived class
    virtual void doResultsWork() = 0; // to be implemented by derived class
    std::atomic<bool> stopRequested{ false };

private:
    std::thread threadResults;
    std::thread threadActions;
    bool running{ false };
};

