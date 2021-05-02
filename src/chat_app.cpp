#include "chat_app.h"
#include "chat.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <future>
//NICE: include jthread.h


ChatApp::ChatApp(std::string user_name): _user_name(user_name) {}

void ChatApp::get_menue_options() {
    std::string option;

    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1) Create new chat" << std::endl;
    std::cout << "2) Open existing chat" << std::endl;
    std::cout << "3) Close chat" << std::endl;
    std::cout << "4) List available chats" << std::endl;

    std::cin.clear();
    std::cin.ignore();
    std::cin >> option;
    
    int option_id;

    try
    {
        option_id = std::stoi(option);

    }
    catch(const std::exception& e)
    {
        std::cout << "Please select a valid option" << std::endl;
        return;  
    }
    
    //NICE: refactor to map/enum or similar for options?
    switch (option_id) {
        case 1:
            create_chat();
            break;
        case 2:
            open_chat();
            break;
        case 3:
            close_chat();
            break;
        case 4:
            list_chats();
            break;
        default:
            std::cout << "Please select a valid option" << std::endl;
            return;
    };
}

void ChatApp::create_chat() {
    std::string chat_name;
    std::cout << "Please input chat name:" << std::endl;
    std::cin >> chat_name;

    auto chat = std::make_unique<Chat>(chat_name, this->_user_name);
    _chats.push_back(std::move(chat));

    std::cout << "New chat " << chat_name <<" successfully created" << std::endl;
}

void ChatApp::list_chats() {
    int i = 0;
    if (!_chats.empty()) {
        for (auto& chat: _chats) {
            std::cout << "ID: " << i << " - Chat name: " << chat->_chat_name << std::endl;
            i++;
        }
    } else {
        std::cout << "There are no chats yet. You can create chats in the main menue" << std::endl;
    }
}

void ChatApp::open_chat() {
    std::cout << "Please enter chat id or 'q' to return to main menue" << std::endl;
    std::string input;
    int chat_id;


    std::cin >> input;

    try
    {
        chat_id = std::stoi(input);
    }
    catch(const std::exception& e)
    {
        std::cout << "Please enter an integer value" << std::endl;
        open_chat();
    }
    

    if(input == "q") {
        return;
    } else {
        try
        {   
            
            std::cout << "Chat: " << _chats.at(chat_id)->_chat_name << " selected" << std::endl;
            std::cout << "You can start chatting :)" << std::endl;
            
            bool run = true;

            //Attention: thread outlives stack, i.e. the thread is not destroyed in c++17, only the thread object!
            std::thread t(&Chat::receive_messages, _chats[chat_id].get(), &run);
            std::thread r(&Chat::send_random_message, _chats[chat_id].get(), &run);

            std::cin.ignore();

            while(run) {
                std::string msg;
                // Use cin.clear() so getline() stops on first loop
                std::cin.clear();
                std::getline(std::cin, msg);
                //Debug print: std::cout << "cin " + msg << std::endl;
                
                if (msg != "q") {
                    _chats[chat_id]->send_message(msg);
                } else {
                    //Signal threads to quite infinite while loop
                    run = false;
                }
            }
            t.join();
            r.join();
        }
        //TODO: catch block not working properly yet -> Why?
        catch(const std::exception& e)
        {
            std::cout << "Please enter a valid chat-id" << std::endl;
            std::cout << "The following chats are available:" << std::endl;
            list_chats();
            std:: cout << std::endl;;
            open_chat();
        }
    }
}

void ChatApp::welcome() {
    std::cout << "Hello " << this->_user_name << "!" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl << std::endl;
}


void ChatApp::close_chat() {
    std::string chat_id_str;

    try
    {
        std::cout << "Please enter chat-id of chat you want to delete:" << std::endl;
        std::cin >> chat_id_str;
        int chat_id = std::stoi(chat_id_str);
        _chats.at(chat_id);
        _chats.erase(_chats.begin() + chat_id);
    }
    catch(const std::exception& e)
    {
        std::cout << "Please select a valid chat id" << std::endl;
        return;
    }
    
}
