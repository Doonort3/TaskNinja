#include "TaskNinja.h"
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
void addTask(vector<Task>& tasks, const vector<string>& tokens) {
    if (tokens.size() > 1) {
        string taskName;
        for (size_t i = 1; i < tokens.size(); ++i) {
            taskName += tokens[i] + " ";
        }
        // Delete the last space
        if (!taskName.empty()) {
            taskName.pop_back();
        }

        Task newTask;
        newTask.name = taskName;
        newTask.description = "no description.";
        tasks.push_back(newTask);
        cout << "A new task has been added: " << newTask.name << "\n";
    }
    else {
        cout << "The name of the task is not specified.\n";
    }
}

// Function to delete a task
void deleteTask(vector<Task>& tasks, const vector<string>& tokens) {
    if (tokens.size() > 1) {
        try {
            size_t taskIndex = stoi(tokens[1]);
            if (taskIndex < tasks.size()) {
                string deletedTaskName = tasks[taskIndex].name;
                tasks.erase(tasks.begin() + taskIndex);
                cout << "Task deleted: " << deletedTaskName << "\n";
            }
            else {
                cout << "Incorrect task number.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: Invalid task number format.\n";
        }
    }
    else {
        cout << "No task number is specified for deletion.\n";
    }
}

// Function to list tasks
void listTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "The task list is empty.\n";
    }
    else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i << ": " << tasks[i].name << " - " << tasks[i].description << endl;
        }
    }
}

// Function to edit a task
void editTask(vector<Task>& tasks, const vector<string>& tokens) {
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
                    cout << "Name of task number " << taskIndex << " changed: " << tasks[taskIndex].name << " - " << tasks[taskIndex].description << endl;
                }
                else if (option == "-d") {
                    tasks[taskIndex].description = newContent;
                    cout << "Description of task number " << taskIndex << " changed: " << tasks[taskIndex].name << " - " << tasks[taskIndex].description << endl;
                }
                else {
                    cout << "Unknown option: " << option << "\n";
                }
            }
            else {
                cout << "Invalid task number.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: Invalid task number format.\n";
        }
    }
    else {
        cout << "Insufficient arguments to edit the task.\n";
    }
}

// Function to convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
