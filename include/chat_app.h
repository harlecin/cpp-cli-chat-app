#pragma once
#include <string>
#include <vector>
#include <memory>
#include "chat.h"

class ChatApp {
    public:
        ChatApp(std::string user_name);
        ~ChatApp() {};
        void welcome();
        void get_menue_options();
        void create_chat();
        void list_chats();
        void open_chat();
        /*
        void close_chat(std::string chat_name);
        void close_chat(); //leave currently active chat
        */
    private:
        std::string _user_name;
        std::vector<std::unique_ptr<Chat>> _chats;
    
};

// TODO: Copy/Move constructor?
// TODO: enforce unique chat ids?
// TODO: enforce unique user names? -> probably not
// TODO: subclass ChatApp -> make methods virtual that are always required. Attention: MS teams does not support create_chat() yet!