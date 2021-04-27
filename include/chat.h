#pragma once
#include <string>
#include <memory>
#include <vector>
#include <deque>
#include <condition_variable>
#include <mutex>

enum class OnlineStatus {
    Online,
    Busy,
    AFK,
    Offline,
};

template<class T>
class MessageQueue {
    public:
        void send(T &&msg);
        T receive();
    private:
        std::deque<T> _messages;
        std::condition_variable _cond;
        std::mutex _mutex;
};


class Chat {
    public:
        Chat(std::string chat_name);
        ~Chat();
        void send_message(std::string text);
        //std::string receive_messages();

        OnlineStatus _online_status;
        std::string _chat_name;
        std::vector<std::string> _messages;
        std::unique_ptr<MessageQueue<std::string>> _chat_queue;
};