cmake_minimum_required(VERSION 3.11.3)

project(cli_chat_app)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(cli_chat_app ${project_SRCS})
target_link_libraries(cli_chat_app ${CURSES_LIBRARIES})
target_compile_options(cli_chat_app PRIVATE -Wall -Wextra -pedantic)