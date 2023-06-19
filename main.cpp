#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <fmt/ranges.h>
#include <map>

using std::cout, std::cin, std::vector, std::endl, std::string, fmt::print;

<<<<<<< HEAD
/**
 * Checks whether given string is a command.
 * @param command - string to be checked.
 * @param commands - string vector of supported commands.
 * @return true if command is in vector commands, if its not returns false;
 */
=======
class Password {
    string name, password;

    Password(const string &name, const string &password) : name(name), password(password) {}

    Password(const Password &p) : name(p.name), password(p.password) {}

    virtual auto info() const -> void {
        cout << name << " " << password << "\n";
    }
};

>>>>>>> parent of 4088f88 (minor changes)
bool checkCommand(const string &command, const vector<string> &commands) {
    if (std::ranges::find(commands, command) == commands.end() && command != "commands") {
        print("Wrong command. Please, try again.\nTo print available commands type \"commands\"\n");
        return false;
    }
    return true;
}

/**
 * shows available commands.
 */
void printAvailableCommands(const vector<string> &commands) {
    print("-------------------------------------------------------------------------------------\nAvailable commands:\n");
    for (const auto &command: commands) {
        print("{}, ", command);
    }
    print("\n-------------------------------------------------------------------------------------\n");
}

<<<<<<< HEAD
/**
 * Encrypts string with password. It is done with XOR logical operator. "i % password.size()" is used to make sure that algorithm will not go out of bounds.
 * To ensure that a all "password" lines are in the same format and in one line - encrypted character cant be newline.
 * @param str - string that will be encrypted.
 * @param password - password that was given by user.
 * @return encrypted string.
 */
std::string encrypt(const std::string &str, const std::string &password) {
    //print("ENNNNCRYPT\n");
    std::string encryptedStr;
    for (int i = 0; i < str.size(); i++) {
        char c = str[i] ^ password[i % password.size()];
        //print("c = {} ^ {} = {}\n", str[i], password[i % password.size()], c);
        if (c == '\n') {
            c = str[i];
        }
        encryptedStr.push_back(c);
    }
    return encryptedStr;
}

/**
 * The same function as above. I know that I could have made one function instead, but I wanted to make it more readable and easier to work with.
 * Mental sanity is important :). At least in this case its more important than performance.
 */
std::string decrypt(const std::string &encryptedStr, const std::string &password) {
    std::string decryptedStr;
    //print("DECRYPT\n");
    for (int i = 0; i < encryptedStr.size(); i++) {
        char c = encryptedStr[i] ^ password[i % password.size()];
        //print("c = {} ^ {} = {}\n", encryptedStr[i], password[i % password.size()], c);
        if (c == '\n') {
            c = encryptedStr[i];
        }
        decryptedStr.push_back(c);
    }
    return decryptedStr;
}


/**
 * Splits string by delimiter into vector of strings.
 * It uses while loop to find delimiter and then push_back substrings into vector. It loops until it reaches end of string.
 * "pos" in while loop is used to find string from "prev" position to the first occurrence of delimiter.
 * @param line - string in format "name;password;category;website;login;".
 * @param delimiter - character that will be used to split string.
 * @return vector of strings that were split by delimiter.
 */
std::vector<std::string> split(const std::string &line, char delimiter) {
    std::vector<std::string> split_line;
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = line.find(delimiter, prev)) != std::string::npos) {
        split_line.push_back(line.substr(prev, pos - prev));
        prev = pos + 1;
    }
    split_line.push_back(line.substr(prev));
    return split_line;
}

/**
 * Gets current time and returns it as vector of integers.
 * @return vector of integers that represent hour, minute and second.
 */

std::vector<int> get_timestamp() {
    std::vector<int> timeStamp;

    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);

    auto time_info = localtime(&now_time);
    int hour = time_info->tm_hour;
    int minute = time_info->tm_min;
    int second = time_info->tm_sec;

    timeStamp.push_back(second);
    timeStamp.push_back(minute);
    timeStamp.push_back(hour);
    /*timeStamp.push_back(hour);
    timeStamp.push_back(minute);
    timeStamp.push_back(second);*/

    return timeStamp;
}

/**
 * Initializes encrypted information from file into vector of passwords (maps of strings).
 * @param filePath - string that represents path to file.
 * @return vector of maps of strings. In other words it returns vector of maps that contain information about passwords.
 */
std::vector<std::map<string, string>> initializeEncryptedPasswords(const string &filePath) {

    std::vector<std::map<string, string>> passwords;

    int counter = 0;
    std::ifstream fileRead(filePath);
    if (!fileRead.is_open()) {
        cout << "Could not open file: " << filePath << std::endl;
        return passwords;
    }

    string line;
    vector<string> split_line;

    while (std::getline(fileRead, line)) {
        if (counter >= 3) {
            split_line = split(line, ';');

            passwords.push_back({
                                        {"name",     split_line[0]},
                                        {"password", split_line[1]},
                                        {"category", split_line[2]},
                                        {"website",  split_line[3]},
                                        {"login",    split_line[4]}
                                });

            split_line.clear();
            split_line.shrink_to_fit();
        }
        counter++;
    }
    fileRead.close();
    return passwords;
}

/**
 * Gets all content from file and returns it as vector of strings (lines).
 * @param filePath - string that represents path to file.
 * @return vector of maps of strings. In other words it returns vector of maps that contain information about passwords.
 */
vector<string> getFileContentCopy(const string &filePath) {
    std::ifstream fileRead(filePath);
    string line;
    vector<string> lines;
    while (std::getline(fileRead, line)) {
        lines.push_back(line);
    }
    fileRead.close();
    return lines;
}

/**
 * Writes new content to file.
 * @param lines - vector of strings that represent lines from file.
 * @param filePath - string that represents path to file.
 * @return vector of maps of strings. In other words it returns vector of maps that contain information about passwords.
 */
void write_to_file(const vector<string> &lines, const string &filePath) {
    std::ofstream fileWrite(filePath);
    for (auto &line: lines) {
        fileWrite << line << "\n";
    }
    fileWrite.close();
}

/**
 * Prints password information represented by map of strings in easy to read format.
 * I use additional variable "decrypted" because it crashes when I try to use decrypt function directly in print function.
 * @param password - vector of maps of strings that contain information about passwords.
 * @param passwordInput - string that represents password that will be used to decrypt passwords.
 */
void print_password(const std::map<string, string> &password, const string &passwordInput) {
    string decrypted;
    print("--------------------\n");
    decrypted = decrypt(password.at("name"), passwordInput);
    print("Name: {}\n", decrypted);
    decrypted = decrypt(password.at("password"), passwordInput);
    print("Password: {}\n", decrypted);
    decrypted = decrypt(password.at("category"), passwordInput);
    print("Category: {}\n", decrypted);
    decrypted = decrypt(password.at("website"), passwordInput);
    print("Website: {}\n", decrypted);
    decrypted = decrypt(password.at("login"), passwordInput);
    print("Login: {}\n", decrypted);
    print("--------------------\n");
}

/**
 * Prints "passwords" (lines) that has string that user is looking for in "name", "category", "website" or "login".
 * @param passwords - vector of maps of strings that contain information about passwords.
 * @param passwordInput - string that represents password that will be used to decrypt passwords.
 * @param search - string that represents what we are searching for.
 * @param searchBy - string that represents by what we are searching.
 */
void search_and_print(const std::vector<std::map<string, string>> &passwords, const string &passwordInput,
                      const string &search, const string &searchBy) {
    string decrypted;
    for (const auto &password: passwords) {
        if (password.at(searchBy) == search) {
            print_password(password, passwordInput);
        }
    }
}

/**
 * Sorts passwords by keys that are in "sortKeys" vector.
 * @param passwords - vector of maps of strings that contain information about passwords.
 * @param sortKeys - vector of strings that represent keys by which we want to sort passwords.
 */
void sort_passwords(std::vector<std::map<string, string>> &passwords, const std::vector<std::string> &sortKeys) {

    std::sort(passwords.begin(), passwords.end(),
              [&](const std::map<string, string> &a, const std::map<string, string> &b) {
                  for (const auto &key: sortKeys) {
                      if (a.at(key) != b.at(key)) {
                          return a.at(key) < b.at(key);
                      }
                  }
                  return false;
              });
}

/**
 * Prints password information represented by map of strings in easy to read format.
 * I use additional variable "decrypted" because it crashes when I try to use decrypt function directly in print function.
 * @param passwordInput - string that represents password that will be used to decrypt passwords I.e given by user.
 */
std::vector<string> get_new_password_data(const string &passwordInput) {
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

    name = encrypt(name, passwordInput);
    password = encrypt(password, passwordInput);
    category = encrypt(category, passwordInput);
    website = encrypt(website, passwordInput);
    login = encrypt(login, passwordInput);

    return {name, password, category, website, login};
}

/**
 * Prints password information represented by map of strings in easy to read format.
 * I use additional variable "decrypted" because it crashes when I try to use decrypt function directly in print function.
 * @param passwordInput - string that represents password that will be used to decrypt passwords I.e given by user.
 */
bool checkId(short id) {
    bool isIdValid = false;
    if (cin.fail() || id == -1) {
        cin.clear();
        cin.ignore(1000, '\n');
        print("Invalid input!\n");
        return isIdValid;
    } else {
        isIdValid = true;
    }
    return isIdValid;
}

/**
 * Executes command given by user.
 * @param command - command given by user.
 * @param commands - all supported commands. vector of strings
 * @param filePath - path to file.
 * @param passwordInput - password given by user.
 */
void executeCommand(const string &command, const vector<string> &commands, const string &filePath,
                    const string &passwordInput) {


    std::vector<int> timeStamp = get_timestamp();

    std::vector<string> password_new;

    if (command == "find") {
        std::vector<std::map<string, string>> passwords = initializeEncryptedPasswords(filePath);
        std::vector<std::map<string, string>> results;
        print("Search by: \n1. name\n2. category\n3. website\n4. login\n5. password\n6. Keyword\n");
        short choice;
        cin >> choice;
        string search;
        print("Search for: ");
        cin >> search;
        string encrypted_search;
        encrypted_search = encrypt(search, passwordInput);

        if (choice == 1) {
            search_and_print(passwords, passwordInput, encrypted_search, "name");
        } else if (choice == 2) {
            search_and_print(passwords, passwordInput, encrypted_search, "category");
        } else if (choice == 3) {
            search_and_print(passwords, passwordInput, encrypted_search, "website");
        } else if (choice == 4) {
            search_and_print(passwords, passwordInput, encrypted_search, "login");
        } else if (choice == 5) {
            search_and_print(passwords, passwordInput, encrypted_search, "password");
        } else if (choice == 6) {

            for (auto &password: passwords) {
                //print("Szukam: {}\nW pliku jest:{}\n", encrypted_search, password.at("login"));
                if (password.at("name").find(encrypted_search) != std::string::npos) {
                    print_password(password, passwordInput);
                } else if (password.at("category").find(encrypted_search) != std::string::npos) {
                    print_password(password, passwordInput);
                } else if (password.at("website").find(encrypted_search) != std::string::npos) {
                    print_password(password, passwordInput);
                } else if (password.at("login").find(encrypted_search) != std::string::npos) {
                    print_password(password, passwordInput);
                } else if (password.at("password").find(encrypted_search) != std::string::npos) {
                    print_password(password, passwordInput);
                }
            }
        }
        passwords.clear();
        passwords.shrink_to_fit();
    } else if (command == "sort") {
        std::vector<std::map<string, string>> passwords = initializeEncryptedPasswords(filePath);
        for (auto &password: passwords) {
            password.at("name") = decrypt(password.at("name"), passwordInput);
            password.at("password") = decrypt(password.at("password"), passwordInput);
            password.at("category") = decrypt(password.at("category"), passwordInput);
            password.at("website") = decrypt(password.at("website"), passwordInput);
            password.at("login") = decrypt(password.at("login"), passwordInput);
        }

        print("Sort by: \n1. name\n2. category\n3. website\n4. login\n5. password\n");
        short choice;
        cin >> choice;
        if (choice == 1) {
            sort_passwords(passwords, {"name"});
        } else if (choice == 2) {
            sort_passwords(passwords, {"category"});
        } else if (choice == 3) {
            sort_passwords(passwords, {"website"});
        } else if (choice == 4) {
            sort_passwords(passwords, {"login"});
        } else if (choice == 5) {
            sort_passwords(passwords, {"password"});
        } else {
            print("Invalid choice. Next time enter a number from 1 to 5.\n");
        }
=======
void printStartMessage() {
    print("Please, choose one of the files displayed below OR create your own and give me absolute path to it.\n"
          "Remember that I can only read .txt files.\n");
}

void executeCommand(const string &command, const vector<string> &commands) {
    if (command == "find") {

        string name;
    } else if (command == "sort") {
>>>>>>> parent of 4088f88 (minor changes)

        std::for_each(passwords.begin(), passwords.end(), [&](const std::map<string, string> &password) {
            print("--------------------\n");
            print("Name: {}\n", password.at("name"));
            print("Password: {}\n", password.at("password"));
            print("Category: {}\n", password.at("category"));
            print("Website: {}\n", password.at("website"));
            print("Login: {}\n", password.at("login"));
            print("--------------------\n");
        });

        passwords.clear();
        passwords.shrink_to_fit();
    } else if (command == "add") {

<<<<<<< HEAD
        password_new = get_new_password_data(passwordInput);

        vector<string> lines = getFileContentCopy(filePath);

        lines[2] =
                std::to_string(timeStamp[0]) + ";" + std::to_string(timeStamp[1]) + ";" + std::to_string(timeStamp[2]) +
                ";";

        string neoLine = password_new[0] + ";" + password_new[1] + ";" + password_new[2] + ";" + password_new[3] + ";" +
                         password_new[4] + ";";
        lines.push_back(neoLine);

        /*for (int i = 0; i < lines.size(); i++) {
            print("Line {}: {}\n", i, lines[i]);
        }*/

        write_to_file(lines, filePath);
        lines.clear();
        lines.shrink_to_fit();
        password_new.clear();
        password_new.shrink_to_fit();
        print("Password added successfully!\n");
=======
>>>>>>> parent of 4088f88 (minor changes)
    } else if (command == "edit") {
        std::vector<std::map<string, string>> passwords = initializeEncryptedPasswords(filePath);
        short id = -1;
        bool isIdValid = false;
        while (id < 0 || id > passwords.size()) {
            print("To view ID`s, write any char that is not a number and then use \"print\" command\nID: ");
            cin >> id;
            isIdValid = checkId(id);
        }
        if (isIdValid) {

            print("Chosen password:\n");
            print_password(passwords[id], passwordInput);

            print("Edit: \n1. name\n2. password\n3. category\n4. website\n5. login\n6. all\n");
            short choice;
            cin >> choice;
            vector<string> lines = getFileContentCopy(filePath);
            vector<string> password_split = split(lines[id + 3], ';');
            string new_value;
            string encrypted_value;
            if (choice == 1) {
                print("Name:");
                cin >> new_value;
                encrypted_value = encrypt(new_value, passwordInput);
                lines[id + 3] =
                        encrypted_value + ";" + password_split[1] + ";" + password_split[2] + ";" + password_split[3] +
                        ";" + password_split[4] + ";";
            } else if (choice == 2) {
                print("Password:");
                cin >> new_value;
                encrypted_value = encrypt(new_value, passwordInput);
                lines[id + 3] =
                        password_split[0] + ";" + encrypted_value + ";" + password_split[2] + ";" + password_split[3] +
                        ";" + password_split[4] + ";";
            } else if (choice == 3) {
                print("Category:");
                cin >> new_value;
                encrypted_value = encrypt(new_value, passwordInput);
                lines[id + 3] =
                        password_split[0] + ";" + password_split[1] + ";" + encrypted_value + ";" + password_split[3] +
                        ";" + password_split[4] + ";";
            } else if (choice == 4) {
                print("Website:");
                cin >> new_value;
                encrypted_value = encrypt(new_value, passwordInput);
                lines[id + 3] =
                        password_split[0] + ";" + password_split[1] + ";" + password_split[2] + ";" + encrypted_value +
                        ";" + password_split[4] + ";";
            } else if (choice == 5) {
                print("Login:");
                cin >> new_value;
                encrypted_value = encrypt(new_value, passwordInput);
                lines[id + 3] =
                        password_split[0] + ";" + password_split[1] + ";" + password_split[2] + ";" +
                        password_split[3] + ";" + encrypted_value + ";";
            } else if (choice == 6) {
                password_new = get_new_password_data(passwordInput);
                lines[id + 3] =
                        password_new[0] + ";" + password_new[1] + ";" + password_new[2] + ";" + password_new[3] + ";" +
                        password_new[4] + ";";
            } else {
                print("Invalid choice. Next time enter a number from 1 to 5.\n");
            }


            lines[2] =
                    std::to_string(timeStamp[0]) + ";" + std::to_string(timeStamp[1]) + ";" +
                    std::to_string(timeStamp[2]) +
                    ";";

            write_to_file(lines, filePath);

            password_new.clear();
            password_new.shrink_to_fit();
            password_split.clear();
            password_split.shrink_to_fit();
            passwords.clear();
            passwords.shrink_to_fit();
            lines.clear();
            lines.shrink_to_fit();
        }

    } else if (command == "delete") {
        std::vector<std::map<string, string>> passwords = initializeEncryptedPasswords(filePath);
        short id = -1;
        bool isIdValid = false;

        while (id < 0 || id > passwords.size()) {
            print("To view ID`s, write any char that is not a number and then use \"print\" command\nID: ");
            cin >> id;
            isIdValid = checkId(id);
        }
        if (isIdValid) {
            vector<string> lines = getFileContentCopy(filePath);

            lines[2] =
                    std::to_string(timeStamp[0]) + ";" + std::to_string(timeStamp[1]) + ";" +
                    std::to_string(timeStamp[2]) +
                    ";";
            lines.erase(lines.begin() + id + 3);
            lines.shrink_to_fit();

            write_to_file(lines, filePath);
            passwords.clear();
            passwords.shrink_to_fit();
        }
    } else if (command == "add-category") {

    } else if (command == "del-category") {
        string category;
        print("Category:");

        cin >> category;
        vector<string> lines = getFileContentCopy(filePath);

        lines[2] =
                std::to_string(timeStamp[0]) + ";" + std::to_string(timeStamp[1]) + ";" + std::to_string(timeStamp[2]) +
                ";";
        string encryptedCategory = encrypt(category, passwordInput);

        for (int i = 0; i < lines.size(); i++) {
            if (lines[i].find(encryptedCategory) != string::npos) {
                lines.erase(lines.begin() + i);
            }
        }

        lines.shrink_to_fit();

        write_to_file(lines, filePath);
        lines.clear();
        lines.shrink_to_fit();
    } else if (command == "print") {
        std::vector<std::map<string, string>> passwords = initializeEncryptedPasswords(filePath);
        int counter = 0;
        std::for_each(passwords.begin(), passwords.end(), [&](const std::map<string, string> &password) {
            print("ID={}\n", counter);
            print_password(password, passwordInput);
            counter++;
        });
        passwords.clear();
        passwords.shrink_to_fit();
    } else if (command == "commands") {
        printAvailableCommands(commands);

    } else if (command == "exit") {
        print("Bye!\n");
    }
}

/**
 * Checks if file is a password manager file. I.e. if it has a header "Password Manager File by s21284."
 * @param filePath - path to file.
 */
bool isPasswordManagerFile(std::string filePath) {
    std::ifstream fileRead(filePath);
    string line;
    std::getline(fileRead, line);
    fileRead.close();
    if (line == "Password Manager File by s21284.") {
        return true;
    }
    return false;
}

<<<<<<< HEAD
/**
 * Checks if password to the file is correct.
 * Second line in the file - "Welcome to Password Manager." - is encrypted with a password given by user during file creation.
 * @param input - inserted password by user.
 * @param filePath - path to file.
 * @return true if password is correct, false otherwise.
 */
bool checkPassword(const string &input, const string &filePath) {

    std::ifstream fileRead(filePath);
    string line;
    int counter = 0;
    string decryptedLine;
    while (std::getline(fileRead, line) && counter < 2) {
        if (counter == 1) {
            decryptedLine = decrypt(line, input);
        }
        counter++;
    }
    fileRead.close();
    if (decryptedLine == "Welcome to Password Manager.") {
        return true;
    }
    return false;
}

/**
 * Transforms regular .txt file into a password manager file, so it can be later identified as such and safely used.
 * First line of the file is a header - "Password Manager File by s21284." - that way program identifies the file as a password manager file.
 * Second line is encrypted with a password given by user during file creation - to later be able to check if password is correct.
 * @param filePath - path to file.
 * @param passwordInput - password given by user.
 */
void makePasswordManagerFile(const string &filePath, const string &passwordInput) {
    std::ofstream file;
    file.open(filePath, std::ios_base::app);
    std::vector<int> timeStamp = get_timestamp();
    file.seekp(0, std::ios::end);
    string secret = "Welcome to Password Manager.";
    string secretEnc = encrypt(secret, passwordInput);
    file << "Password Manager File by s21284.\n";
    file << secretEnc << "\n";
    file << timeStamp[0] << ";" << timeStamp[1] << ";" << timeStamp[2] << ";\n";
    file.close();
}

/**
 * Prints available password manager files in the directory and returns them.
 * @return vector of strings - available password manager files.
 */
std::vector<string> printAndGetAvailableTextFiles() {
    vector<string> availableFiles;
    print("-----------------\nAvailable files:\n");
    auto home = std::filesystem::current_path();
    home = home.parent_path();
    for (const auto &entry: std::filesystem::directory_iterator(home)) {
        if (".txt" == entry.path().extension() && entry.path().filename() != "CMakeLists.txt" && isPasswordManagerFile(
                entry.path().string())) {
            std::cout << entry.path().filename() << std::endl;
            availableFiles.push_back(entry.path().string());
        }
    }
    print("-----------------\n");
    return availableFiles;
}

int main() {
    //TODO: password is koperek

    string password;

    vector<string> commands = {"find", "sort", "add", "edit", "delete", "add-category", "del-category", "commands",
                               "exit", "print"};
=======

int main() {
    
    string s = "/home/krzysztof/CLionProjects/PasswordManager/Passwords.txt";

    auto sourceFile = std::filesystem::path(s);

    vector<string> commands = {"find", "sort", "add", "edit", "delete", "add category", "delete category", "commands",
                               "exit"};
    print("===============================\nHi! Welcome to Password Manager!\n");
    printStartMessage();
    printAvailableTextFiles();
    printAvailableCommands(commands);
>>>>>>> parent of 4088f88 (minor changes)

    string command;
    string filePath;

<<<<<<< HEAD
    print("=====================================================================================\nHi!\nWelcome to Password Manager!\n=====================================================================================\n");

    vector<string> availableFiles;
    printAvailableCommands(commands);

    string tester = "jablko";
    string entester = encrypt(tester, "koperek");
    print("TESTUJE JABLKO!!!!\n{}|{}\n", entester, decrypt(entester, "koperek"));


    bool correct_password = false;
    bool home_file = false;

    while (filePath != "exit") {
        command = "";
        print("Please, give me a file path OR one of the file names listed below:\n");
        availableFiles = printAndGetAvailableTextFiles();
=======
    bool first = true;
    while (filePath != "exit" || first) {
        first = false;
        print("Please, provide me a file path.\n");
>>>>>>> parent of 4088f88 (minor changes)
        cin >> filePath;
        if (filePath == "exit") {
            print("Turning off...\n");
            break;
        }
        for (int i = 0; i < availableFiles.size(); i++) {
            string path = R"(C:\Programowanie\CLionProjects\PasswordManager\)" + filePath;
            if (path == availableFiles[i]) {
                filePath = availableFiles[i];
                break;
            }
        }
        while (!std::filesystem::exists(filePath) && filePath != "exit") {
            print("File does not exist. Please, try again.\n");
            cin >> filePath;
            if (filePath == "exit") {
                break;
            }
        }
<<<<<<< HEAD

        if (!isPasswordManagerFile(filePath) && filePath != "exit") {
            print("Your file is not a Password Manager file. Please, create a password to this file.\n"
                  "Remember, that you will not be able to access this file without this password.\n"
                  "!!! You will not be able to change your password !!!\n");
            print("Enter password:");
            cin >> password;
            print("Password is in.\n");
            makePasswordManagerFile(filePath, password);
        } else {
            print("Enter password:");
            cin >> password;
            correct_password = checkPassword(password, filePath);
            while (!correct_password && password != "exit") {
                print("Wrong password. Please, try again.\nEnter password:");
                cin >> password;
                if (checkPassword(password, filePath)) {
                    correct_password = true;
                }
            }

            while (command != "exit" && filePath != "exit" && password != "exit" && correct_password) {
                print("=====================================================================================\n                                      SUCCESS!\nNow you are in {}!"
                      "\n=====================================================================================\n",
                      filePath);
                printAvailableCommands(commands);
                std::getline(cin, command);
                while (command != "exit" && filePath != "exit") {
                    if (checkCommand(command, commands)) {
                        executeCommand(command, commands, filePath, password);
                        cin >> command;
                    } else {
                        cin >> command;
                    }
                }
=======
        print("Success.\nNow you are in {} !\n", filePath);
        printAvailableCommands(commands);
        cin >> command;
        while (command != "exit" && filePath != "exit") {
            if(checkCommand(command, commands)){
                executeCommand(command, commands);
                cin >> command;
            } else {
                cin >> command;
>>>>>>> parent of 4088f88 (minor changes)
            }
        }
    }

    return 0;
}
