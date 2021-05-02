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
        Chat(std::string chat_name, std::string user_name);
        ~Chat();
        void send_message(std::string text);
        void receive_messages(bool* run);
        void send_random_message(bool* run);
    
        OnlineStatus _online_status;
        std::string _chat_name;
        std::string _user_name;
        std::vector<std::string> _messages;
        std::unique_ptr<MessageQueue<std::string>> _chat_queue;
        //std::unique_ptr<std::vector<std::string>> _chat_history;
        //TODO: on open_chat() -> load _chat_history last 10 messages
};

// TODO: implement Message class or overkill?