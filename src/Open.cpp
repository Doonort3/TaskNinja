/*****************************************************************//**
 * \file   Open.cpp
 * \brief  This file contains the implementation of working with the task if it is opened in full-screen mode.
 * 
 * \author ikuyu
 * \date   May 2024
 *********************************************************************/

#include "../include/Open.h"
#include "../include/ConsoleUtils.h"
#include "../include/Config.h"
#include "../include/TaskNinja.h"

#include <iostream>
#include <string>

using namespace std;

void manageTask(std::vector<Task>& tasks, size_t taskIndex, std::vector<std::string>& logs) {
    while (true) {
        setCursorPosition(0, 0);
        Task& task = tasks[taskIndex];
        // 
        std::cout << "Task Name: " << task.name << std::endl;
        std::cout << "Description: " << task.description << std::endl;

        setCursorPosition(0, rows - 1);
        string userInputInTask;
        cout << "> ";
        getline(cin, userInputInTask);

        vector<string> tokens = splitString(userInputInTask);
        if (!tokens.empty()) {
            if (tokens[0] == "edit_name") {
                if (tokens.size() < 2) {
                    addLog(logs, "Usage: edit_name <newName>");
                    clearConsole();
                    setCursorPosition(0, rows - 2);
                    cout << "Usage: edit_name <newName>";

                }
                else {
                    string newName = userInputInTask.substr(userInputInTask.find(tokens[1]));
                    tasks[taskIndex].name = newName;
                    clearConsole();
                    setCursorPosition(0, rows - 2);
                    addLog(logs, "Name for task " + std::to_string(taskIndex) + " changed to: " + newName);
                    cout << ANSI_COLOR_GREEN "* " ANSI_COLOR_RESET << "Updated task name " + std::to_string(taskIndex) + " > " + newName;
                }
            }
            else if (tokens[0] == "edit_desc") {
                if (tokens.size() < 2) {
                    clearConsole();
                    setCursorPosition(0, rows - 2);
                    cout << "Usage: edit_desc <newDescription>";
                    addLog(logs, "Usage: edit_desc <newDescription>");
                }
                else {
                    string newDescription = userInputInTask.substr(userInputInTask.find(tokens[1]));
                    tasks[taskIndex].description = newDescription;
                    clearConsole();
                    setCursorPosition(0, rows - 2);
                    addLog(logs, "Description for task " + std::to_string(taskIndex) + " changed to: " + newDescription);
                    cout << ANSI_COLOR_GREEN "* " ANSI_COLOR_RESET << "Updated task description " + std::to_string(taskIndex) + " > " + newDescription;
                } 
            }
            else if (tokens[0] == "exit") {
                break; // Выход из редактирования задачи
            }
            else {
                addLog(logs, "Unknown command: " + tokens[0]);
                clearConsole();
                setCursorPosition(0, rows - 2);
                cout << ANSI_COLOR_RED "* " ANSI_COLOR_RESET << "Unknown command: " + tokens[0];
            }
        }
        else {
            addLog(logs, "Empty input.");
            clearConsole();
            setCursorPosition(0, rows - 2);
            cout << ANSI_COLOR_RED "* " ANSI_COLOR_RESET << "Empty input.";
        }
    }
}

void openLogs(const vector<string>& logs) {
    clearConsole();
    if (logs.empty()) {
        cout << "No logs." << endl;
    }
    else {
        
        cout << "Logs:" << endl;
        for (size_t i = 0; i < logs.size(); ++i) {
            cout << i + 1 << ". " << logs[i] << endl;
        }
    }
    cout << "\nPress any key to close..." << endl;
    getchar();
}