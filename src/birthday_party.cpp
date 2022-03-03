#include <algorithm>
#include <array>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>

#define NUM_GUESTS 5

// Keeps track of which guests in the labyrinth have eaten the cupcake
std::vector<bool> guests(NUM_GUESTS);
std::mutex mutex;
bool isCupcakeAvailable = true;
int currentCount = 0;
int activeThreadIndex;

// Note: the bounds for min and max are both inclusive
int generateRandomNumber(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
    return static_cast<int>(dist6(rng));
}

void checkCupcake() {
    while (currentCount < NUM_GUESTS) {
        mutex.lock();

        if (activeThreadIndex == 0) {
            if (!isCupcakeAvailable) {
                currentCount++;
                isCupcakeAvailable = true;
            }
        }

        mutex.unlock();
    }
}

void navigateLabyrinth(int threadIndex) {
    while (currentCount < NUM_GUESTS) {
        mutex.lock();

        if (activeThreadIndex == threadIndex) {
            if (isCupcakeAvailable && !guests[threadIndex]) {
                isCupcakeAvailable = false;
                guests[threadIndex] = true;
            }
        }

        mutex.unlock();
    }
}

int main() {
    std::array<std::thread, NUM_GUESTS> threads{};

    threads[0] = std::thread(checkCupcake);

    for (size_t i = 1; i < threads.size(); i++) {
        threads[i] = std::thread(navigateLabyrinth, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Subtracting 1 here because we don't need to check if the first thread
    // (the thread that keeps count) eats the cupcake
    while (currentCount < NUM_GUESTS - 1) {
        activeThreadIndex = generateRandomNumber(0, NUM_GUESTS);
    }

    std::cout << "All guests have been accounted for." << std::endl;
}
