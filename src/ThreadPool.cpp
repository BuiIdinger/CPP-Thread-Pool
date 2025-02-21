#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(const size_t& numOfThread) : m_stop(false) {
  for (size_t i = 0; i < numOfThread; i++) {
    m_workers.emplace_back([this] { 
      while (true) {
        std::function<void()> task;

        {
          std::unique_lock<std::mutex> guard(m_tasksMutex);
          m_condition.wait(guard, [this] {
            return m_stop || !m_tasks.empty();
          });

          if (m_stop && m_tasks.empty()) {
            return;
          }
          task = std::move(m_tasks.front());
          m_tasks.pop();
        }

        task();
      }
    });
  }
}

ThreadPool::~ThreadPool() {
  {
    std::scoped_lock<std::mutex> guard(m_tasksMutex);
    m_stop = true;
  }

  m_condition.notify_all();
  for (std::thread& worker : m_workers) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

void ThreadPool::enqueueTask(std::function<void()> task) noexcept {
  {
    std::scoped_lock<std::mutex> guard(m_tasksMutex);
    m_tasks.emplace(std::move(task));
  }
  
  m_condition.notify_one();
}