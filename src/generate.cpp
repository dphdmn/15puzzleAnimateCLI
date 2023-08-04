#include <iostream>
#include <string>
#include <cstdio>

std::string applyCommand(const std::string& command) {
    std::string result;
    char buffer[128];
    FILE* pipe = _popen(command.c_str(), "r");
    if (pipe) {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        _pclose(pipe);
    }
    return result;
}

int main(int argc, char* argv[]) {
    std::string arg1 = argv[1];
    std::string arg2 = argv[2];
    std::cout << arg1 << std::endl;

    for (char current_char : arg2) {
        arg1 = applyCommand("slidy apply --state \"" + arg1 + "\" --alg \"" + current_char + "\"");
        arg1.pop_back();
        std::cout << arg1 << std::endl;
    }

    return 0;
}