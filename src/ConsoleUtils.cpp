#include "../include/ConsoleUtils.h"

#ifdef _WIN32
#include <Windows.h> // Including the header file for working with Windows API
#else
#include <sys/ioctl.h> // Including header files for input-output operations in Unix-like systems
#include <unistd.h>
#endif

void getConsoleSize(int& rows, int& cols) {
#ifdef _WIN32
    // Getting information about the console screen buffer in Windows
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Calculating the number of rows and columns based on the buffer information
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    // Getting the console size in Unix-like systems
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    // Calculating the number of rows and columns based on the retrieved data
    rows = size.ws_row;
    cols = size.ws_col;
#endif
}

void setCursorPosition(int x, int y) {
#ifdef _WIN32
    // Setting the cursor position in Windows using the COORD structure
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    // Setting the cursor position in Unix-like systems using ANSI escape sequences
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "H";
#endif
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
