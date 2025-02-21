#pragma once

#include <string>
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include <thread>
#include <condition_variable>

class ThreadPool {
private:
  std::vector<std::thread> m_workers;
  std::condition_variable m_condition;
  std::queue<std::function<void()>> m_tasks;
  std::mutex m_tasksMutex;
  bool m_stop = false;
public:
  void enqueueTask(std::function<void()> task) noexcept;
  explicit ThreadPool(const size_t& numOfThreads);
  ~ThreadPool();
};
