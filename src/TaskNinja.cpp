/*****************************************************************//**
 * \file   TaskNinja.cpp
 * \brief  This file contains command implementations for working with tasks.
 * 
 * \author ikuyu
 * \date   May 2024
 *********************************************************************/

#include "../include/TaskNinja.h"
#include "../include/ConsoleUtils.h"
#include "../include/Config.h"
#include "../include/Open.h"
#include "../include/WR.h"
#include "../include/FileSystemUtils.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iomanip>

using namespace std;

extern void cleanup();

vector<string> splitString(const string& input) {
    istringstream iss(input);
    vector<string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void showHelp() {
    clearConsole();
    cout << "Available commands:" << endl;
    cout << "1. " ANSI_COLOR_CYAN "add_task" ANSI_COLOR_RESET " "
        << ANSI_COLOR_YELLOW "<name> <description>" ANSI_COLOR_RESET ": Add a new task with the given name and description." << endl;
    cout << "2. " ANSI_COLOR_CYAN "del_task" ANSI_COLOR_RESET " "
        << ANSI_COLOR_YELLOW "<index>" ANSI_COLOR_RESET ": Delete the task with the specified index." << endl;
    cout << "3. " ANSI_COLOR_CYAN "edit_task" ANSI_COLOR_RESET " "
        << ANSI_COLOR_YELLOW "<index> <-n|-d> <newName|newDescription>" ANSI_COLOR_RESET ": Edit task name/description by index." << endl;
    cout << "4. " ANSI_COLOR_CYAN "open_task" ANSI_COLOR_RESET " "
        << ANSI_COLOR_YELLOW "<index>" ANSI_COLOR_RESET ": View detailed information about the task with the specified index." << endl;
    cout << "  4.1. " ANSI_COLOR_CYAN "edit_name" ANSI_COLOR_RESET " "
        << ANSI_COLOR_YELLOW "<newName>" ANSI_COLOR_RESET ": Edit the name of the open task." << endl;
    cout << "  4.2. " ANSI_COLOR_CYAN "edit_desc" ANSI_COLOR_RESET " "
        << ANSI_COLOR_YELLOW "<newDescription>" ANSI_COLOR_RESET ": Edit the description of the open task." << endl;
    cout << "  4.3. " ANSI_COLOR_CYAN "exit" ANSI_COLOR_RESET ": Close the open task and return to the main menu." << endl;
    cout << "5. " ANSI_COLOR_CYAN "clear_logs" ANSI_COLOR_RESET ": Clear the log messages." << endl;
    cout << "6. " ANSI_COLOR_CYAN "logs" ANSI_COLOR_RESET ": View the log messages." << endl;
    cout << "7. " ANSI_COLOR_CYAN "help" ANSI_COLOR_RESET ": Show available commands." << endl;
    cout << "8. " ANSI_COLOR_CYAN "exit" ANSI_COLOR_RESET ": Save data and exit the program." << endl;

    cout << endl << "Press any key to close..." << endl;
    getchar();
}

void addTask(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {
    if (tokens.size() < 2) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "No task name specified.");
        return;
    }

    size_t newTaskIndex = tasks.size();
    string taskName, taskDescription = "No description.";

    if (tokens.size() >= 2) {
        taskName = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            taskDescription += tokens[i] + " ";
        }
        // Удаляем последний пробел
        if (!taskDescription.empty() && taskDescription != "No description.") {
            taskDescription.pop_back();
        }
    }

    Task newTask = { static_cast<int>(newTaskIndex), taskName, taskDescription };
    tasks.push_back(newTask);
    addLog(logs, ANSI_COLOR_GREEN "* " ANSI_COLOR_RESET "Add: " + newTask.name);

    saveTasksToFile(tasks);
}

void deleteTask(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {
    if (tokens.size() != 2) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid number of arguments.");
        return;
    }

    try {
        size_t taskIndex = stoi(tokens[1]);
        if (taskIndex < tasks.size()) {
            string deletedTaskName = tasks[taskIndex].name;
            tasks.erase(tasks.begin() + taskIndex);
            removeTaskFromFile(taskIndex);
            addLog(logs, ANSI_COLOR_GREEN "* " ANSI_COLOR_RESET "Del: " + deletedTaskName);
        }
        else {
            addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid task number.");
        }
    }
    catch (const invalid_argument&) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid task number format.");
    }
    catch (const out_of_range&) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Task number out of range.");
    }
}

void editTask(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {
    if (tokens.size() < 4) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Insufficient arguments.");
        return;
    }

    try {
        size_t taskIndex = stoul(tokens[1]);
        if (taskIndex >= tasks.size()) {
            addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid task number.");
            return;
        }

        string option = tokens[2];
        string newContent = accumulate(tokens.begin() + 3, tokens.end(), string(), [](const string& a, const string& b) {
            return a + (a.length() > 0 ? " " : "") + b;
            });

        if (option == "-n") {
            tasks[taskIndex].name = newContent;
            addLog(logs, ANSI_COLOR_GREEN "* " ANSI_COLOR_RESET "Name updated: " + newContent);
        }
        else if (option == "-d") {
            tasks[taskIndex].description = newContent;
            addLog(logs, ANSI_COLOR_GREEN "* " ANSI_COLOR_RESET "Desc updated: " + newContent);
        }
        else {
            addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Unknown option: " + option);
        }
    }
    catch (const invalid_argument&) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid task number format.");
    }
    catch (const out_of_range&) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Task number out of range.");
    }
}

void showTaskDetails(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {
    if (tokens.size() != 2) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid number of arguments.");
        return;
    }

    try {
        size_t taskIndex = stoul(tokens[1]);
        if (taskIndex < tasks.size()) {
            clearConsole();
            manageTask(tasks, taskIndex, logs);
            clearConsole();
        }
        else {
            addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid task number.");
        }
    }
    catch (const invalid_argument&) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Invalid task number format.");
    }
    catch (const out_of_range&) {
        addLog(logs, ANSI_COLOR_RED "* " ANSI_COLOR_RESET "Task number out of range.");
    }
}

void addLog(vector<string>& logs, const string& message) {
    logs.push_back(message);
}

void clearLogs(vector<string>& logs) {
    logs.clear();
}

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void exitProgram(vector<Task>& tasks) {
    cleanup();
    exit(0);
}
