#pragma once
#include <thread>
#include <vector>

class Counter {
public:
    void increment() {
        ++count_;
    }

    int get() const {
        return count_;
    }

private:
    int count_ = 0;
};

void incrementInThreads(Counter& counter, int numThreads, int incrementsPerThread) {
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread([&counter, incrementsPerThread]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter.increment();
            }
            }));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}
