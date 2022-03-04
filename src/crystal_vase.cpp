#include <array>
#include <chrono>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

#define NUM_GUESTS 10

std::deque<std::thread::id> guests{};
std::mutex mutex;

void admireVase(int threadIndex) {
    while (!guests.empty()) {
        mutex.lock();

        if (std::this_thread::get_id() == guests.front()) {
            std::cout << "Guest #" << threadIndex << " is admiring the vase!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            guests.pop_front();
        }

        mutex.unlock();
    }
}

int main() {
    std::array<std::thread, NUM_GUESTS> threads{};

    for (size_t i = 0; i < threads.size(); i++) {
        threads[i] = std::thread(admireVase, i);
        guests.push_back(threads[i].get_id());
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "All guests have viewed the vase." << std::endl;
}
