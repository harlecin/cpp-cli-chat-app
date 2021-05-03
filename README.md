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

Expected behavior: Start a simple chat app that writes to stout and accepts input on stin.

# Criteria fullfilled

- Project compiles and runs without errors (and warnings)
- Code compiles on every platform using cmake
- A variety of control structures are used in the project (e.g. `Chat::receive_messages`(chat.cpp/l49): `while`, `if-else`, `ChatApp::list_chats`(chat_app.cpp/l73): range-based-for-loop, lots of `try-catch` and `if-else`)
- The project code is clearly organized into functions (see header files)
- The project accepts input from a user as part of the necessary operation of the program (`ChatApp::get_menue_options`: chat_app.cpp/l35: `cin` and `getline` on l122)
- The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks (see header files)
- All class data members are explicitly specified as public, protected, or private. (see header files)
- All class members that are set to argument values are initialized through member initialization lists (`ChatApp::ChatApp`: chat_app.cpp/l11)
- All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways (see header files)
- One function is declared with a template that allows it to accept a generic parameter (`T MessageQueue`: chat.cpp/l10)
- At least two variables are defined as references, or two functions use pass-by-reference in the project code (chat_app.cpp/l73 and l94 and l113 among others)
- The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers (see header files: only `unique_ptrs` are used to allocate memory)
- The project uses multiple threads in the execution (chat_app.cpp/l113+114)
- A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code (chat.cpp/l20)
- A std::condition_variable is used in the project code to synchronize thread execution (chat.cpp/l14)

