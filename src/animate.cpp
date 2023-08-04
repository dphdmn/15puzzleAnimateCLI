#include <iostream>
#include <string>
#include <cstdio>
#include <Windows.h>

void fixPath(){
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string executablePath = buffer;
    std::string executableDir = executablePath.substr(0, executablePath.find_last_of("\\/"));
    SetCurrentDirectory(executableDir.c_str());
}

std::string applyCommand(const std::string& command) {
    std::string result;
    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe) {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        pclose(pipe);
    }
    return result;
}

int main(int argc, char* argv[]) {
    fixPath();
    std::string arg1 = "";
    std::string arg2 = "";

    if (argc == 2) {
        arg1 = applyCommand("slidy invert " + std::string(argv[1]) + " | slidy apply-to-solved --size 4");
        arg1.pop_back();
        arg2 = std::string(argv[1]);
    } else if (argc == 3) {
        arg1 = argv[1];
        arg2 = argv[2];
    }

    arg2 = applyCommand("slidy format -l \"" + arg2 + "\"");
    arg2.pop_back();
    std::string input = applyCommand("scripts\\generate.exe \"" + arg1 + "\" \"" + arg2 + "\"");
    FILE* pipe = popen("scripts\\core.exe", "w");
    fwrite(input.c_str(), 1, input.size(), pipe);
    pclose(pipe);

    return 0;
}
