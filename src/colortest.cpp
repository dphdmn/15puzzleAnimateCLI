#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstring>
#include <vector>
#include <csignal> // For signal() function
#include <cstdlib> // For system() function
#include <conio.h>

// Signal handler function
void signalHandler(int signum) {
    // Catch and ignore the signal (Ctrl+C)
    if (signum == SIGINT) {
        std::cout << "Program interrupted. Performing cls before exit..." << std::endl;
        system("cls"); // Or "clear" on Linux/macOS
        exit(signum);
    }
}
// Function to show or hide the cursor in the console window
void ShowConsoleCursor(bool show) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = show ? TRUE : FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void drawPlaceholder(int color, int width) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < width; i++) {
        std::cout << " ";
    }
    SetConsoleTextAttribute(hConsole, 7);
}

int countDigits(int number) {
    int count = 0;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

void drawNumberOnColor(int color, int number, int width) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    if (number != 0) {
        int numDigits = countDigits(number);
        int padding = (width - numDigits) / 2;
        for (int i = 0; i < padding; i++) {
            std::cout << " ";
        }
        std::cout << number;
        for (int i = 0; i < width - padding - numDigits; i++) {
            std::cout << " ";
        }
    }
    else {
        drawPlaceholder(color, width);
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void parseNumbers(const char* input, int* numbers, int totalChunks) {
    int i = 0;
    int num;
    while (*input && i < totalChunks * totalChunks) {
        if (std::isdigit(*input)) {
            num = 0;
            while (std::isdigit(*input)) {
                num = num * 10 + (*input - '0');
                input++;
            }
            numbers[i] = (num == 0) ? 16 : num;
            i++;
        }
        input++;
    }
}

void drawState(const char* input) {
    const int gridSize = 12;
    const int totalChunks = gridSize / 3;

    int numbers[totalChunks * totalChunks] = { 0 };
    parseNumbers(input, numbers, totalChunks);

    const int chunkSize = 3;

    int chunkColors[totalChunks][totalChunks];

    for (int i = 0; i < totalChunks; i++) {
        for (int j = 0; j < totalChunks; j++) {
            int number = numbers[i * totalChunks + j];
            int chunkColor;

            // Assigning colors based on numbers
            switch (number) {
            case 1:
            case 2:
            case 3:
            case 4:
                chunkColor = BACKGROUND_RED;
                break;
            case 5:
            case 9:
            case 13:
                chunkColor = BACKGROUND_RED | BACKGROUND_GREEN;
                break;
            case 6:
            case 7:
            case 8:
                chunkColor = BACKGROUND_GREEN;
                break;
            case 10:
            case 14:
                chunkColor = BACKGROUND_GREEN | BACKGROUND_BLUE;
                break;
            case 11:
            case 12:
                chunkColor = BACKGROUND_BLUE;
                break;
            case 15:
                chunkColor = BACKGROUND_RED | BACKGROUND_BLUE;
                break;
            case 16:
                chunkColor = 0;
                break;
            default:
                chunkColor = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
            }

            chunkColors[i][j] = chunkColor;
        }
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD originalCursorPosition = csbi.dwCursorPosition;

    for (int chunkRow = 0; chunkRow < totalChunks; chunkRow++) {
        for (int row = 0; row < chunkSize; row++) {
            for (int chunkCol = 0; chunkCol < totalChunks; chunkCol++) {
                for (int col = 0; col < chunkSize; col++) {
                    int chunkColor = chunkColors[chunkRow][chunkCol];
                    int number = numbers[chunkRow * totalChunks + chunkCol];

                    COORD cursorPosition;
                    cursorPosition.X = (chunkCol * chunkSize + col) * 3 + originalCursorPosition.X;
                    cursorPosition.Y = chunkRow * chunkSize + row + originalCursorPosition.Y;
                    SetConsoleCursorPosition(hConsole, cursorPosition);

                    if (row == 1 && col == 1) {
                        drawNumberOnColor(chunkColor, number, 3);
                    }
                    else {
                        drawPlaceholder(chunkColor, 3);
                    }
                }
            }
        }
    }

    // Restore the cursor position
    SetConsoleCursorPosition(hConsole, originalCursorPosition);
}

void readStates(std::vector<std::string>& states) {
    std::string line;
    std::cout << "Put states from stdin to run:" << std::endl;
    // Read lines from stdin and save them in the states vector
    while (std::getline(std::cin, line)) {
        if (line.empty() || line == "exit") {
            break; // Stop inputting if the line is empty or "exit"
        }
        states.push_back(line);
    }
}


void setConsoleSizeAndHideCursor() {
    HWND hwnd = GetConsoleWindow();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
    ShowWindow(hwnd, SW_NORMAL);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    SMALL_RECT windowSize = { 0, 0, 35, 11 }; // 36x12 window size (zero-based index)
    COORD bufferSize = { 36, 12 }; // Buffer size should match the window size for simplicity

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Hide the cursor
    ShowConsoleCursor(false);
}

void showCursorAndResetConsoleSize() {
    HWND hwnd = GetConsoleWindow();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);

    // Show the cursor before exiting
    ShowConsoleCursor(true);

    // Reset the console window size and screen buffer size to their original values
    SetWindowLong(hwnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(hwnd, SW_MAXIMIZE);
    
    SetWindowLong(hwnd, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
    ShowWindow(hwnd, SW_NORMAL);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    SMALL_RECT originalWindowSize = bufferInfo.srWindow;
    COORD originalBufferSize = bufferInfo.dwSize;

    SetConsoleWindowInfo(hConsole, TRUE, &originalWindowSize);
    SetConsoleScreenBufferSize(hConsole, originalBufferSize);
}

void animateStates(const std::vector<std::string>& states) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Iterate through the states vector and draw each state
    int stateCount = states.size();
    for (int i = 0; i < stateCount; ++i) {
        const std::string& state = states[i];
        drawState(state.c_str()); // Convert to const char* before passing

        // Delay based on the position of the state in the loop
        if (i == 0 || i == stateCount - 1) {
            Sleep(800); // 1000 ms (1 second) delay for the first and last states
        }
        else {
            Sleep(100); // 100 ms delay for other states
        }
    }
}

int main() {
    system("cls");
    signal(SIGINT, signalHandler);
    std::vector<std::string> states;
    
    readStates(states);
    if (states.empty()) {
        std::cout << "No states provided. Exiting." << std::endl;
        return 1;
    }

    system("cls");
    setConsoleSizeAndHideCursor();
    animateStates(states);
    showCursorAndResetConsoleSize();
    system("cls");
    return 0;
}






