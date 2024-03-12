#include <iostream>
#include "PasswordManager.h"

int main() {
    PasswordManager manager;
    std::string path, password;
    int choose;
    bool isExit = true;
    std::cout << "Choose a source file for passwords or type 1 for choosing file by default: ";
    std::getline(std::cin, path);
    if (path == "1") {
        path = "main.txt";
        if (!PasswordManager::checkFile(path)) {
            PasswordManager::createFile(path);
        }
    } else {
        if (!PasswordManager::checkFile(path)) {
            PasswordManager::createFile(path);
        }
    }
    manager.setFilePath(path);
    std::cout << "Enter main password: ";
    std::cin >> password;
    manager.setMainPass(password);
    manager.addTimestamp();
    manager.printTimestamps();
    while (isExit) {
        std::cout
                << "\tMenu\n 1. Search for passwords\n 2. Sort passwords\n 3. Add a password\n 4. Edit a password\n 5. Remove a password\n 6. Add a category\n 7. Remove a category\n 8. Exit\n";
        std::cout << "Type number of action: ";
        std::cin >> choose;
        switch (choose) {
            case 1: {
                std::cout << "Search password by:\n 1. Name\n 2. Category\n";
                int search;
                std::cout << "Type number of action: ";
                std::cin >> search;
                std::string passStr;
                if (search == 1) {
                    std::cout << "Enter name of password: ";
                    std::cin.ignore();
                    std::getline(std::cin, passStr);
                    std::vector<std::string> result = manager.searchPass(passStr, search);
                    if (result.empty()) {
                        std::cout << "No matching!" << std::endl;
                    } else {
                        std::cout << "List of password by '" << passStr << "':" << std::endl;
                        for (auto &i: result) {
                            std::cout << i << std::endl;
                        }
                    }
                } else if (search == 2) {
                    std::cout << "Enter category of password: ";
                    std::cin.ignore();
                    std::getline(std::cin, passStr);
                    std::vector<std::string> result = manager.searchPass(passStr, search);
                    if (result.empty()) {
                        std::cout << "No matching!" << std::endl;
                    } else {
                        std::cout << "List of password by '" << passStr << "':" << std::endl;
                        for (auto &i: result) {
                            std::cout << i << std::endl;
                        }
                    }
                }
                break;
            }
            case 2: {
                std::cout << "Sort passwords by: \n 1. Name\n 2. Category" << std::endl;
                std::cout << "Type number of action: ";
                int choise;
                std::cin >> choise;
                manager.sortPass(choise);
                break;
            }
            case 3: {
                std::string passAdd, passName, passCateg, choise;
                std::cout << "Name of password: ";
                std::cin.ignore();
                std::getline(std::cin, passName);
                std::cout << "Do you want to generate random password? [y|n]: ";
                std::cin >> choise;
                if (choise == "y") {
                    std::string tempchoise;
                    int length;
                    bool caps, special;
                    std::cout << "Enter length of password: ";
                    std::cin >> length;
                    std::cout << "Add uppercase to password? [y|n]: ";
                    std::cin >> tempchoise;
                    if (tempchoise == "y") caps = true;
                    else caps = false;
                    std::cout << "Add special characters to password? [y|n]: ";
                    std::cin >> tempchoise;
                    if (tempchoise == "y") special = true;
                    else special = false;
                    passAdd = manager.generatePass(caps, true, special, length);
                    std::cout << "Password generated!" << std::endl;
                } else {
                    std::cout << "Enter a password to add: ";
                    std::cin >> passAdd;
                }
                std::cout << "Enter a category for password: ";
                std::cin.ignore();
                std::getline(std::cin, passCateg);
                manager.addPass(passName, passAdd, passCateg);
                break;
            }
            case 4: {
                std::string pass, passName, passCateg;
                std::cout << "Enter name of password to edit: ";
                std::cin.ignore();
                std::getline(std::cin, passName);
                std::cout << "Enter a password to edit: ";
                std::cin >> pass;
                std::cout << "Enter a category for password to edit: ";
                std::cin.ignore();
                std::getline(std::cin, passCateg);
                manager.editPass(passName, pass, passCateg);
                break;
            }
            case 5: {
                std::string pass, passName, passCateg;
                std::cout << "Enter name of password to delete: ";
                std::cin.ignore();
                std::getline(std::cin, passName);
                std::cout << "Enter a password to delete: ";
                std::cin >> pass;
                std::cout << "Enter a category for password: ";
                std::cin.ignore();
                std::getline(std::cin, passCateg);
                manager.removePass(passName, pass, passCateg);
                break;
            }
            case 6: {
                std::string category;
                std::cout << "Enter a category of password: ";
                std::cin.ignore();
                std::getline(std::cin, category);
                manager.addCategory(category);
                std::cout << "Category successfully added!" << std::endl;
                break;
            }
            case 7: {
                std::string category;
                std::cout << "Enter a category to delete: ";
                std::cin.ignore();
                std::getline(std::cin, category);
                manager.removeCategory(category);
                break;
            }
            case 8: {
                isExit = false;
                break;
            }
        }
    }
}

