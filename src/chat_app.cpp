#include "chat_app.h"
#include "chat.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>


ChatApp::ChatApp(std::string user_name) {
    this->_user_name = user_name;
}

void ChatApp::get_menue_options() {
    int option;

    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1) Create new chat" << std::endl;
    std::cout << "2) Open existing chat" << std::endl;
    std::cout << "3) Close chat" << std::endl;
    std::cout << "4) List available chats" << std::endl;

    std::cin >> option;
    // TODO: cin with string does open input, but loops until segfault?
    if (!std::cin) {
        
        std::cout << "Please select a valid option" << std::endl;
        ChatApp::get_menue_options();  

    }

    // TODO: refactor to map/enum or similar for options?

    switch (option) {
        case 1:
            create_chat();
            break;
        case 2:
            std::cout << "Chat opened" << std::endl;
            break;
        case 3:
            std::cout << "Chat closed" << std::endl;
            break;
        case 4:
            list_chats();
            break;
        default:
            std::cout << "Please select a valid option" << std::endl;
            ChatApp::get_menue_options();
    };
}

void ChatApp::create_chat() {
    std::string chat_name;
    std::cout << "Please input chat name:" << std::endl;
    std::cin >> chat_name;
    //std::unique_ptr<Chat> chat = std::unique_ptr<Chat>(new Chat(chat_name));
    auto chat = std::make_unique<Chat>(chat_name);
    _chats.push_back(std::move(chat));

    std::cout << "New chat " << chat_name <<" successfully created" << std::endl;
}

void ChatApp::list_chats() {
    int i = 1;
    if (!_chats.empty()) {
        for (auto& chat: _chats) {
            std::cout << i << ".) Chat: " << chat->_chat_name << std::endl;
            i++;
        }
    } else {
        std::cout << "There are no chats yet. You can create chats in the main menue" << std::endl;
    }
}
