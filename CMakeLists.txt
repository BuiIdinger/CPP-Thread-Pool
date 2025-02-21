# Set minimum version
cmake_minimum_required(VERSION 3.10)

# Set project
project(ThreadPool)

# Set C++ standard and configs
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set library version
set(THREADPOOL_VERSION_MAJOR 1)
set(THREADPOOL_VERSION_MINOR 0)

# Add the library target and specify include directories
add_library(ThreadPool STATIC src/ThreadPool.cpp)
target_include_directories(ThreadPool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Install the library and headers
install(TARGETS ThreadPool ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Make example executable and link the executable
add_executable(Example src/Example.cpp)
target_link_libraries(Example PRIVATE ThreadPool)

# Create and install the ThreadPoolConfig.cmake file
set(TARGET_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_LIBRARIES ThreadPool)

# Create the config file and install the config file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThreadPoolConfig.cmake.in" "${CMAKE_BINARY_DIR}/ThreadPoolConfig.cmake")
install(FILES "${CMAKE_BINARY_DIR}/ThreadPoolConfig.cmake" DESTINATION lib/cmake/ThreadPool)

# Create and install ThreadPoolConfigVersion.cmake
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ThreadPoolConfigVersion.cmake.in" "${CMAKE_BINARY_DIR}/ThreadPoolConfigVersion.cmake")
install(FILES "${CMAKE_BINARY_DIR}/ThreadPoolConfigVersion.cmake" DESTINATION lib/cmake/ThreadPool)

# Export the CMake target and install the target
export(TARGETS ThreadPool FILE "${CMAKE_BINARY_DIR}/ThreadPoolTargets.cmake")
install(EXPORT ThreadPoolTargets FILE ThreadPoolTargets.cmake DESTINATION lib/cmake/ThreadPool)