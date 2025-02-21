#include "ThreadPool.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
  ThreadPool threadPool(std::thread::hardware_concurrency());

  threadPool.enqueueTask([]() {
    while (true) {
      std::cout << "Hello first" << "\n";
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });

  threadPool.enqueueTask([]() {
    while (true) {
      std::cout << "Hello second" << "\n";
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });

  threadPool.enqueueTask([]() {
    while (true) {
      std::cout << "Hello third" << "\n";
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });

  return 0;
}

