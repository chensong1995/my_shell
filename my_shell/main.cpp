#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

class JobRecord {
public:
    int job_number;
    char current;
    std::string state;
    std::string command;
}

int shell_jobs(std::vector<std::string> command) {
    assert command[0] == "jobs";

    return 0;
}

int shell_cd(std::vector<std::string> command) {
    assert command[0] == "cd";
    if (command.size() < 2) { // No arguments
        return -1; // Error occurs
    }
    return chdir(command[1].c_str());
}

int exec_command(std::vector<std::string> command) {
    std::string& prog_name = command[0];

    if ("exit" == prog_name) {
        exit(0);
    } else if ("jobs" == prog_name) {

    } else if ("cd" == prog_name) {

    } else {
        // Run another program
    }
    return 0;
}

int main() {

    while (true) {

        std::string input;
        std::cout << "Please input a command: "; // Print out a prompt
        std::getline (std::cin, input); // Read in user's input

        // Split user's input into commands by detecting pipes first and whitespace second
        std::vector<std::vector<std::string>> commands;
        char* input_str = new char[input.length() + 1];
        strcpy(input_str, input.c_str());
        char* save_ptr;
        char* pch = strtok_r(input_str, "|", &save_ptr);
        while (NULL != pch) {
            // Split arguments
            std::vector<std::string> args;
            char* save_ptr_args;
            char* pch_args = strtok_r(pch, " \t", &save_ptr_args);
            while (NULL != pch_args) {
                args.push_back(std::string(pch_args));
                pch_args = strtok_r(NULL, " \t", &save_ptr_args);
            }
            if (args.size() == 0) { // Two pipes with nothing between
                std::cout << "Syntax Error!" << std::endl;
                commands.clear();
                break;
            }
            commands.push_back(args);
            pch = strtok_r(NULL, "|", &save_ptr);
        }
        delete[] input_str;

        for (auto const& command : commands) {
            exec_command(command);
        }
    }

    return 0;
}
