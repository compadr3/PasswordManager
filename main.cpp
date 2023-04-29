#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <fmt/ranges.h>

using std::cout, std::cin, std::vector, std::endl, std::string, fmt::print;

class Password {
public:
    string name, password, category, website, login;

    Password(string name, string password, string category, string website, string login) {
        this->name = name;
        this->password = password;
        this->category = category;
        this->website = website;
        this->login = login;
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

void encryptString(string &str, string password) {

    for (int i = 0; i < str.size(); i++) {
        str[i] = str[i] ^ password[i % password.size()];
    }
    print("Encrypted string: {}\n", str);
}

void decryptString(string &str, string password) {
    for (int i = 0; i < str.size(); i++) {
        str[i] = str[i] ^ password[i % password.size()];
    }
    print("Decrypted string: {}\n", str);
}

void executeCommand(const string &command, const vector<string> &commands, const string &filePath, const string& passwordInput) {
    if (command == "find") {
        std::ifstream file(filePath);
        string line;
        vector<Password> passwords;
        while (std::getline(file, line)) {
            print("{}\n", line);
        }

    } else if (command == "sort") {

    } else if (command == "add") {
        string name, password, category, website, login;
        print("Name:");
        cin >> name;
        print("Password:");
        cin >> password;
        print("Category:");
        cin >> category;
        print("[Optional] Website:");
        cin >> website;
        print("[Optional] Login:");
        cin >> login;

        std::ofstream file;
        file.open(filePath, std::ios_base::app);
        file << name << ";" << password << ";" << category << ";" << website << ";" << login << "\n";

        print("Password added successfully!\n");
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

    string password;

    auto sourceFile = std::filesystem::path(s);

    vector<string> commands = {"find", "sort", "add", "edit", "delete", "add category", "delete category", "commands",
                               "exit"};
    print("===============================\nHi! Welcome to Password Manager!\n");
    printStartMessage();
    printAvailableTextFiles();
    printAvailableCommands(commands);

    string command;
    string filePath;

    encryptString(s, "password");
    decryptString(s, "password");
    bool first = true;
    while (filePath != "exit" || first) {
        first = false;
        print("Please, provide me with a file path.\n");
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
        print("Enter password:");
        cin >> password;
        print("Password is in.\n");
        printAvailableCommands(commands);
        cin >> command;
        while (command != "exit" && filePath != "exit") {
            if(checkCommand(command, commands)){
                executeCommand(command, commands, filePath, password);
                cin >> command;
            } else {
                cin >> command;
            }
        }
    }

    return 0;
}
