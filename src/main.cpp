/*
    * multitool++
    * main.cpp
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include "discord.hpp"
#include "telegram.hpp"
#include "console.hpp"
#include "char.hpp"
#include "calculator_shell.hpp"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <termios.h>
#endif

/* DOCUMENTATION
    * exit(0) - EXIT SUCCESS
    * exit(1) - EXIT FAILURE
    * exit(10) - UNSUPPORTED OPERATING SYSTEM
    * std::cout << string; - CHARACTER OUTPUT
    * std::getline(...) - READ LINE FROM USER
    * std::stoi(string) - CONVERT STRING TO INTEGER
    * system(...) - RUN A SYSTEM COMMAND
    * console::clear() - CLEAR THE CONSOLE
    * discord::send_webhook(...) - SEND MESSAGE TO DISCORD WEBHOOK
    * telegram::send_message(...) - SEND MESSAGE TO TELEGRAM BOT
    * ansi::[...] - ANSI ESCAPE CODES FOR COLORING
    * If you're reading this section, you may want to make a pull request to expand it
*/

std::string checked1 = "[x]";
std::string checked2 = "[ ]";
std::string checked3 = "[ ]";
std::string checked4 = "[ ]";
std::string checked5 = "[ ]";
std::string checked6 = "[ ]";

void initialize();

void banner() {
    const char* banner = R"(
              .__   __  .__  __                .__                           
  _____  __ __|  |_/  |_|__|/  |_  ____   ____ |  |      .__         .__     )";

    const char* banner2 = R"(
 /     \|  |  \  |\   __\  \   __\/  _ \ /  _ \|  |    __|  |___   __|  |___ 
|  Y Y  \  |  /  |_|  | |  ||  | (  <_> |  <_> )  |__ /__    __/  /__    __/ )";

    const char* banner3 = R"(
|__|_|  /____/|____/__| |__||__|  \____/ \____/|____/    |__|        |__|    
      \/                                                                     )";
    
    std::cout << ansi::BG_BLACK;
    std::cout << ansi::BOLD << ansi::WHITE << banner << ansi::RESET;
    std::cout << ansi::BG_BLACK;
    std::cout << ansi::BOLD << ansi::CYAN << banner2 << ansi::RESET;
    std::cout << ansi::BG_BLACK;
    std::cout << ansi::BOLD << ansi::BLUE << banner3 << ansi::RESET << "\n" <<  "\n";
}

void option_exit() {
    std::cout << ansi::GREEN << "Valid choice!" << ansi::RESET << "\n";
    exit(0);
}

void option_timer() {
    std::cout << ansi::GREEN << "Valid choice!" << ansi::RESET << "\n";
    std::cout << ansi::CYAN << "Enter a number of seconds: " << ansi::RESET;
    std::string seconds;
    std::getline(std::cin, seconds);
    int seconds_int;
    try {
        seconds_int = std::stoi(seconds);
    }
    catch (std::invalid_argument& e) {
        std::cout << ansi::RED << e.what() << ansi::RESET << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        initialize();
    }
    catch (std::out_of_range& e) {
        std::cout << ansi::RED << e.what() << ansi::RESET << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        initialize();
    }
    int timer = seconds_int;
    while (timer > 0) {
        std::cout << ansi::WHITE << timer << ansi::RESET << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        timer--;
    }
    initialize();
}

void option_discord() {
    std::cout << ansi::GREEN << "Valid choice!" << ansi::RESET << "\n";
    std::cout << ansi::CYAN << "Enter Discord webhook URL: " << ansi::RESET;
    std::string webhook_url;
    std::getline(std::cin, webhook_url);
            
    std::cout << ansi::CYAN << "Enter message to send: " << ansi::RESET;
    std::string message;
    std::getline(std::cin, message);
            
    discord::send_webhook(webhook_url, message);
    initialize();
}

void option_telegram() {
    std::cout << ansi::GREEN << "Valid choice!" << ansi::RESET << "\n";
    std::cout << ansi::CYAN << "Enter Telegram bot token: " << ansi::RESET;
    std::string bot_token;
    std::getline(std::cin, bot_token);

    std::cout << ansi::CYAN << "Enter Telegram chat ID: " << ansi::RESET;
    std::string chat_id;
    std::getline(std::cin, chat_id);

    std::cout << ansi::CYAN << "Enter message to send: " << ansi::RESET;
    std::string message;
    std::getline(std::cin, message);

    telegram::send_message(bot_token, chat_id, message);
    initialize();
}

void option_password() {
    std::cout << ansi::GREEN << "Valid choice!" << ansi::RESET << "\n";
    std::cout << ansi::CYAN << "Enter password length: " << ansi::RESET;
    std::string length;
    std::getline(std::cin, length);
    int length_int;
    try {
        length_int = std::stoi(length);
    }
    catch (std::invalid_argument& e) {
        std::cout << ansi::RED << e.what() << ansi::RESET << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        initialize();
    }
    catch (std::out_of_range& e) {
        std::cout << ansi::RED << e.what() << ansi::RESET << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        initialize();
    }
    std::string password = "";
    for (int i = 0; i < length_int; i++) {
        const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()_+-=[]{}|;:,.<>?";
        password += charset[rand() % charset.length()];
    }
    std::cout << ansi::GREEN << "Generated password: " << ansi::RESET << password << "\n";
    std::cout << ansi::CYAN << "Press any key to continue...\n" << ansi::RESET;
    char_utils::get_char();
    initialize();
}

void menu() {
    console::clear();
    banner();
    std::cout << ansi::BOLD << ansi::ITALIC << ansi::UNDERLINE << ansi::BG_BLUE << ansi::CYAN;
    std::cout << "OPTIONS:                    \n";
    std::cout << ansi::RESET;
    std::cout << ansi::UNDERLINE << ansi::BG_BLUE << ansi::CYAN;
    std::cout << checked1 << " exit                    \n";
    std::cout << checked2 << " timer                   \n";
    std::cout << checked3 << " send Discord message    \n";
    std::cout << checked4 << " send Telegram message   \n"; 
    std::cout << checked5 << " generate secure password\n";
    std::cout << checked6 << " calculator shell        \n";
    std::cout << "\n";
    std::cout << ansi::RESET;
    std::cout << ansi::CYAN << "Use W/S to navigate, E to select.\n" << ansi::RESET;
}

void read() {
    char check = char_utils::get_char();
    //std::cout << ansi::CYAN << "Validating choice... " << ansi::RESET;

    if (check == 'w' || check == 'W') {
        if (checked2 == "[x]") {
            checked2 = "[ ]";
            checked1 = "[x]";
        }
        else if (checked3 == "[x]") {
            checked3 = "[ ]";
            checked2 = "[x]";
        }
        else if (checked4 == "[x]") {
            checked4 = "[ ]";
            checked3 = "[x]";
        }
        else if (checked5 == "[x]") {
            checked5 = "[ ]";
            checked4 = "[x]";
        }
        else if (checked6 == "[x]") {
            checked6 = "[ ]";
            checked5 = "[x]";
        }
        initialize();
    }
    else if (check == 's' || check == 'S') {
        if (checked1 == "[x]") {
            checked1 = "[ ]";
            checked2 = "[x]";
        }
        else if (checked2 == "[x]") {
            checked2 = "[ ]";
            checked3 = "[x]";
        }
        else if (checked3 == "[x]") {
            checked3 = "[ ]";
            checked4 = "[x]";
        }
        else if (checked4 == "[x]") {
            checked4 = "[ ]";
            checked5 = "[x]";
        }
        else if (checked5 == "[x]") {
            checked5 = "[ ]";
            checked6 = "[x]";
        }
        initialize();
    }
    else if (check == 'e' || check == 'E') {
        if (checked1 == "[x]") {
            option_exit();
        }
        else if (checked2 == "[x]") {
            option_timer();
        }
        else if (checked3 == "[x]") {
            option_discord();
        }
        else if (checked4 == "[x]") {
            option_telegram();
        }
        else if (checked5 == "[x]") {
            option_password();
        }
        else if (checked6 == "[x]") {
            std::cout << ansi::GREEN << "Valid choice!" << ansi::RESET << "\n";
            std::cout << ansi::BOLD << ansi::ITALIC << ansi::CYAN << "Welcome to the calculator shell, type 'help' for commands.\n" << ansi::RESET;
            option_shell();
        }
    }
    else {
        std::cout << ansi::RED << "Invalid choice." << ansi::RESET << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        initialize();
    }
}

void initialize() {
    console::clear();
    menu();
    read();
}

void checkCurlIsInstalled() {
#ifdef _WIN32
    int curl = system("curl --version >nul 2>&1");
    if (curl != 0) {
        std::cout << "Curl not installed. Install it by running: winget install cURL.cURL\n";
        exit(1);
    }
#elif defined(__linux__)
    int curl = system("curl --version >/dev/null 2>&1");
    if (curl != 0) {
        std::cout << "Curl not installed. Install it by running: sudo <your package manager> install curl\n";
        exit(1);
    }
#else
    std::cout << "Unsupported OS. Please make sure you have modified the source code before compiling for another OS.";
    exit(10);
#endif
}

int main() {
    checkCurlIsInstalled();
    initialize();
}
