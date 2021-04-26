#include "chat_app.h"
#include <iostream>
#include <string>

int main() {
    std::string user_name;

    std::cout << "Please enter your user name: " << std::endl;
    std::cin >> user_name;

    ChatApp YourChatApp(user_name);

    while (true) {
       YourChatApp.get_menue_options();
    }

    return 0;
}

// TODO: add std::move() to Display