#pragma once

#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <iostream>

void getConsoleSize(int& rows, int& cols);
void setCursorPosition(int x, int y);
void clearConsole();

#endif // CONSOLEUTILS_H
