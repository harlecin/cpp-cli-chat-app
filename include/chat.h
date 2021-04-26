#pragma once
#include <string>
#include <vector>

enum class OnlineStatus {
    Online,
    Busy,
    AFK,
    Offline,
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
};