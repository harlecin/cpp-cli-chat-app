# Terminal Chat App written in C++

Terminal chat app prototype for Udacity C++ Nanodegree Capstone project.

# Setup
To install the project simply run the following in your terminal.

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=debug .. && make
```

Make sure you have cmake>3.11.3 installed.

To run the project, execute:
```
./cli_chat_app
```
in build directory.

# Project Overview
The project is structured as follows:
```
include/
    chat_app.h
    chat.h
src/
    chat_app.cpp
    chat.cpp
    main.cpp
```
When you execute the program, a chat_app instance is created.

The chat app is responsible for managing unique pointers to different chat instances and to provide a launchpad to:

- create a new chat
- open an existing chat
- list all available chats
- close an existing chat

When you create a chat, a new chat is pushed in a vector in the chat app. Each chat has a message queue that is responsible for managing chat messages. To simulate a chat partner a chat bot is spawned in a new thread to send random messages to the chat queue. You can send messages to the chat queue from your terminal. The queue is polled in a separat thread for new chat messages and prints them to stout. To kill the queue/bot thread when quitting the chat both threads check a common run-flag (an alternative would be to use `std::jthread` from c++20).

I wanted to add an ncurses tui to get a prettier chat interface, but have not found the time yet. So stdin does not look nice, but works.

# Criteria fullfilled

[x] Project compiles and runs without errors (and warnings)
[x] Code compiles on every platform using cmake

See [Project Criteria](https://review.udacity.com/#!/rubrics/2533/view)
<Which items are covered by the project?>

