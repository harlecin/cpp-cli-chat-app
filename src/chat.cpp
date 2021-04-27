#include "chat_app.h"
#include "chat.h"
#include <string>
#include <iostream>
#include <mutex>
#include <memory>

template<typename T>
void MessageQueue<T>::send(T &&msg) {
    std::lock_guard<std::mutex> uLock(_mutex);
    _messages.push_back(std::move(msg));
    _cond.notify_one();
}

template <typename T>
T MessageQueue<T>::receive()
{ 
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_messages.empty();});
    T msg = std::move(_messages.back());
    _messages.pop_back();

    return msg;
}


Chat::Chat(std::string chat_name) {
    this->_chat_name = chat_name;
    this->_online_status = OnlineStatus::Online;
    
    _chat_queue = std::make_unique<MessageQueue<std::string>>();

}

Chat::~Chat() {
    
}

void Chat::send_message(std::string text) {
    std::cout << text << " sent" << std::endl;
    //TODO: Send text to queue
    _chat_queue->send(std::move(text));

}