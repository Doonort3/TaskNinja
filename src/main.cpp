/*****************************************************************//**
 * \file   main.cpp
 * \brief  This file contains the main program loop.
 * 
 * \author ikuyu
 * \date   May 2024
 *********************************************************************/

#include "../include/Task.h"
#include "../include/TaskNinja.h"
#include "../include/ConsoleUtils.h"
#include "../include/RenderUtils.h"
#include "../include/Config.h"
#include "../include/Open.h"
#include "../include/WR.h"
#include "../include/FileSystemUtils.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<Task> tasks = loadTasksFromFile();
vector<string> logs;
string userInput;
extern bool initialMessageDisplayed = false;


void initialize() {
    tasks = loadTasksFromFile();
    logs = loadLogsFromFile(); 

    updateConsoleSize();
    updateConfig(); 
    ensureSaveFileExists();
    ensureLogFileExists();
}

void updateScreen() {
    clearConsole();
    updateConsoleSize();
    updateConfig();
}

void cleanup() {
    saveTasksToFile(tasks);
    saveLogsToFile(logs);
}

int main() {
    initialize();

    while (true) {
        updateScreen();
        
        if (!initialMessageDisplayed) {
            initialMessageDisplayed = displayLoadingMessages(tasks, logs);
        }
        
        displayTaskListHeader(tasks, logs);
        setCursorPosition(0, rows - 1); // Set the caret at the very bottom of the console for the command entry field
        cout << "> ";
        getline(cin, userInput);

        string commands = toLower(userInput); 
        vector<string> tokens = splitString(commands); // TODO: поправить, все названия и описания с маленькой буквы

        if (!tokens.empty()) {
            if (tokens[0] == "help"){
                showHelp();
            }
            else if (tokens[0] == "add_task") {
                addTask(tasks, tokens, logs);
            }
            else if (tokens[0] == "del_task") {
                deleteTask(tasks, tokens, logs);
            }
            else if (tokens[0] == "edit_task") {
                editTask(tasks, tokens, logs);
            }
            else if (tokens[0] == "open_task") {
                showTaskDetails(tasks, tokens, logs);
            }
            else if (tokens[0] == "logs") {
                openLogs(logs);
            }
            else if (tokens[0] == "clear_logs") {
                clearLogs(logs);
            }
            else if (tokens[0] == "exit") {
                exitProgram(tasks);
            }
            else {
                addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Unknown cmd: " + tokens[0]);
            }
        }
        else {
            addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Empty input.");
        }
    }

    cleanup();
    return 0;
}
