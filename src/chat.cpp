#include "chat_app.h"
#include "chat.h"
#include <string>
#include <iostream>
#include <mutex>
#include <memory>
#include <random>
#include <future>

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


Chat::Chat(std::string chat_name, std::string user_name) {
    this->_chat_name = chat_name;
    this->_online_status = OnlineStatus::Online;
    this->_user_name = user_name;
    
    _chat_queue = std::make_unique<MessageQueue<std::string>>();

}

Chat::~Chat() {
    
}

void Chat::send_message(std::string text) {
    //std::cout << text << " sent" << std::endl;
    //TODO: Send text to queue
    //TODO: add sender name and timestamp infront of text:
    auto msg = _user_name + " said: " + text;
    _chat_queue->send(std::move(msg));

}

std::string Chat::receive_messages(){
    //TODO: change to void?
    auto msg = _chat_queue->receive();
    std::cout << msg << std::endl;

    return msg;
}

void Chat::send_random_message() {
    std::vector<std::string> responses{"Hmm", "Can you repeat that?", ":)"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_response(0,2);
    std::uniform_int_distribution<> distr_wait_time(1, 3);
    auto response_id = distr_response(gen);
    auto wait_time = distr_wait_time(gen);

    auto msg = "Bot said: " + responses[response_id];

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * wait_time));
    _chat_queue->send(std::move(msg));
}