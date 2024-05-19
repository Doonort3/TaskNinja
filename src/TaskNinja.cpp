#include "../include/TaskNinja.h"
#include "../include/ConsoleUtils.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to split a string into tokens. Parser
vector<string> splitString(const string& input) {
    istringstream iss(input);
    vector<string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to add a task
void addTask(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {
    if (tokens.size() < 2) {
        addLog(logs, "No task name specified.");
        return;
    }

    string taskName;
    for (size_t i = 1; i < tokens.size(); ++i) {
        taskName += tokens[i] + " ";
    }
    // Удаляем последний пробел
    if (!taskName.empty()) {
        taskName.pop_back();
    }

    Task newTask;
    newTask.name = taskName;
    newTask.description = "No description.";
    tasks.push_back(newTask);
    addLog(logs, "Add: " + newTask.name);
}

// Function to delete a task
void deleteTask(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {

    if (tokens.size() > 2)
    {
        addLog(logs, "Superfluous arguments.");
        return;
    }

    if (tokens.size() > 1) {
        try {
            size_t taskIndex = stoi(tokens[1]);
            if (taskIndex < tasks.size()) {
                string deletedTaskName = tasks[taskIndex].name;
                tasks.erase(tasks.begin() + taskIndex);
                addLog(logs, "Del: " + deletedTaskName);
            }
            else {
                addLog(logs, "Incorrect task number.");
            }
        }
        catch (const exception& e) {
            addLog(logs, "Invalid task number format.");
        }
    }
    else {
        addLog(logs, "No task number specified.");
    }
}

// Function to edit a task
void editTask(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {
    if (tokens.size() > 3) {
        try {
            size_t taskIndex = stoul(tokens[1]);
            if (taskIndex < tasks.size()) {
                string option = tokens[2];
                string newContent;
                for (size_t i = 3; i < tokens.size(); ++i) {
                    newContent += tokens[i] + " ";
                }

                if (!newContent.empty()) {
                    newContent.pop_back();
                }

                /* the '-n' key changes the task name
                   the '-d' key changes the task description */
                if (option == "-n") {
                    tasks[taskIndex].name = newContent;
                    addLog(logs, "Name updated: " + newContent);
                }
                else if (option == "-d") {
                    tasks[taskIndex].description = newContent;
                    addLog(logs, "Desc updated: " + newContent);
                }
                else {
                    addLog(logs, "Unknown option: " + option);
                }
            }
            else {
                addLog(logs, "Invalid task number.");
            }
        }
        catch (const exception& e) {
            addLog(logs, "Invalid task number format.");
        }
    }
    else {
        addLog(logs, "Insufficient arguments.");
    }
}


void showTaskDetails(vector<Task>& tasks, const vector<string>& tokens, vector<string>& logs) {
    if (tokens.size() > 2) 
    {
        addLog(logs, "Superfluous arguments.");
        return;
    }

    if (tokens.size() > 1) {
        try
        {
            clearConsole();
            size_t taskIndex = stoul(tokens[1]);
            if (taskIndex < tasks.size()) {
                size_t taskIndex = stoul(tokens[1]);
                    Task& task = tasks[taskIndex];
                    // setCursorPosition(0, 0);
                    std::cout << "Task Name: " << task.name << std::endl;
                    std::cout << "Description: " << task.description << std::endl;
            }
            else {
                addLog(logs, "Invalid task number.");
            }
        }
        catch (const std::exception&)
        {
            addLog(logs, "Invalid task number format.");
        }
    }
    else {
        addLog(logs, "Insufficient arguments.");
    }
   
    // while (true) {
        // Реализовать команды для редактирования открытой задачи
    // }
}

void addLog(vector<string>& logs, const string& message) {
    logs.push_back(message);
}

void clearLogs(std::vector<std::string>& logs) {
    logs.clear();
}

// Function to convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
