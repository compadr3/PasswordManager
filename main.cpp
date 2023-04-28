#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <fmt/ranges.h>
using std::cout,std::cin,std::vector,std::endl,std::string, fmt::print;

class Password {
    string name, password;
    Password(const string &name, const string &password) : name(name), password(password) {}
    Password(const Password & p) : name(p.name), password(p.password){}

    virtual auto info() const ->void{
        cout<<name<<" "<<password<<"\n";
    }
};

void checkCommand(const string &command, const vector<string> &commands){
    if (std::ranges::find(commands, command) == commands.end()){
        print("Wrong command. Please, try again.\nTo print available commands type \"commands\"\n");
    }
}

void printAvailableTextFiles() {
    print("-----------------\nAvailable files:\n");
    auto home = std::filesystem::current_path();
    home = home.parent_path();
    for (const auto &entry: std::filesystem::directory_iterator(home)){
        if (".txt" == entry.path().extension() && entry.path().filename() != "CMakeLists.txt") {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    print("-----------------\n");
}

void printAvailableCommands(const vector<string> &commands){
    print("-----------------\nAvailable commands:\n");
    for (const auto &command: commands){
        print("{}, ", command);
    }
    print("\n-----------------\n");
}

void printStartMessage(){
    print("Please, choose one of the files displayed below OR create your own and give me absolute path to it.\n"
          "Remember that I can only read .txt files.\n");
}

void executeCommand(const string &command, const vector<string> &commands) {
    if(command == "find") {
        print("Please, give me a name of the password you are looking for.\n");
        string name;
    } else if(command == "sort"){

    } else if(command == "add"){

    } else if(command == "edit"){

    } else if(command == "delete"){

    } else if(command == "add category"){

    } else if(command == "delete category"){

    } else if(command == "commands"){
        printAvailableCommands(commands);
    } else if(command == "exit"){
        print("Bye!\n");
    }
}

int main() {
    vector<string> commands = {"find", "sort", "add", "edit", "delete", "add category", "delete category", "commands", "exit"};
    print("===============================\nHi! Welcome to Password Manager!\n");
    printStartMessage();
    printAvailableTextFiles();
    printAvailableCommands(commands);
    string command;
    while (command != "exit"){
        cin >> command;
        checkCommand(command, commands);
        executeCommand(command, commands);
    }
    return 0;
}
