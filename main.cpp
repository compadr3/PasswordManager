#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <fmt/ranges.h>

using std::cout, std::cin, std::vector, std::endl, std::string, fmt::print;

class Password {
    string name, password;

    Password(const string &name, const string &password) : name(name), password(password) {}

    Password(const Password &p) : name(p.name), password(p.password) {}

    virtual auto info() const -> void {
        cout << name << " " << password << "\n";
    }
};

bool checkCommand(const string &command, const vector<string> &commands) {
    if (std::ranges::find(commands, command) == commands.end()) {
        print("Wrong command. Please, try again.\nTo print available commands type \"commands\"\n");
        return false;
    }
    return true;
}

void printAvailableTextFiles() {
    print("-----------------\nAvailable files:\n");
    auto home = std::filesystem::current_path();
    home = home.parent_path();
    for (const auto &entry: std::filesystem::directory_iterator(home)) {
        if (".txt" == entry.path().extension() && entry.path().filename() != "CMakeLists.txt") {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    print("-----------------\n");
}

void printAvailableCommands(const vector<string> &commands) {
    print("-----------------\nAvailable commands:\n");
    for (const auto &command: commands) {
        print("{}, ", command);
    }
    print("\n-----------------\n");
}

void printStartMessage() {
    print("Please, choose one of the files displayed below OR create your own and give me absolute path to it.\n"
          "Remember that I can only read .txt files.\n");
}

void executeCommand(const string &command, const vector<string> &commands) {
    if (command == "find") {

        string name;
    } else if (command == "sort") {

    } else if (command == "add") {

    } else if (command == "edit") {

    } else if (command == "delete") {

    } else if (command == "add category") {

    } else if (command == "delete category") {

    } else if (command == "commands") {
        printAvailableCommands(commands);
    } else if (command == "exit") {
        print("Bye!\n");
    }
}

bool checkFile(std::string filePath) {
    if (std::filesystem::exists(filePath)) {
        return true;
    }
    return false;
}


int main() {
    
    string s = "/home/krzysztof/CLionProjects/PasswordManager/Passwords.txt";

    auto sourceFile = std::filesystem::path(s);

    vector<string> commands = {"find", "sort", "add", "edit", "delete", "add category", "delete category", "commands",
                               "exit"};
    print("===============================\nHi! Welcome to Password Manager!\n");
    printStartMessage();
    printAvailableTextFiles();
    printAvailableCommands(commands);

    string command;
    string filePath;

    bool first = true;
    while (filePath != "exit" || first) {
        first = false;
        print("Please, provide me a file path.\n");
        cin >> filePath;
        if (filePath == "exit") {
            print("Turning off...\n");
            break;
        }
        while (!checkFile(filePath) && filePath != "exit") {
            print("File does not exist. Please, try again.\n");
            cin >> filePath;
        }
        print("Success.\nNow you are in {} !\n", filePath);
        printAvailableCommands(commands);
        cin >> command;
        while (command != "exit" && filePath != "exit") {
            if(checkCommand(command, commands)){
                executeCommand(command, commands);
                cin >> command;
            } else {
                cin >> command;
            }
        }
    }

    return 0;
}
