# C++ Thread Pool
A simple C++ thread pool class.

# Example

```cpp
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
```

# Build

To build the library, you need CMake.

Build:
- mkdir build && cd build
- cmake .. && make

Install the library:
- sudo make install

# Example of linking with a CMakeLists.txt

```
cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Set C++ configs
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(MyProject main.cpp)

# Find ThreadPool package
find_package(ThreadPool REQUIRED)
target_include_directories(MyProject PRIVATE /usr/local/include)
target_link_libraries(MyProject PRIVATE ThreadPool)
target_link_directories(MyProject PRIVATE /usr/local/lib)
```