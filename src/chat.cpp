#include "chat_app.h"
#include "chat.h"
#include <string>
#include <iostream>

Chat::Chat(std::string chat_name) {
    this->_chat_name = chat_name;
    this->_online_status = OnlineStatus::Online;
}

Chat::~Chat() {
    
}

void Chat::send_message(std::string text) {
    std::cout << text << " sent" << std::endl;
}