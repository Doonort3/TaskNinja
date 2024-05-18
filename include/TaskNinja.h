#pragma once

#ifndef TASKNINJA_H
#define TASKNINJA_H

#include <vector>
#include <string>

// Structure for storing tasks
struct Task {
    std::string name;
    std::string description;
};

// Functions for working with tasks
std::vector<std::string> splitString(const std::string& input);

void addLog(std::vector<std::string>& logs, const std::string& message);
void clearLogs(std::vector<std::string>& logs);
void addTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens, std::vector<std::string>& logs);
void editTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens, std::vector<std::string>& logs);
void deleteTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens, std::vector<std::string>& logs);

void displayTaskListHeader(const std::vector<Task>& tasks, std::vector<std::string>& logs);
void renderTasks(const std::vector<Task>& tasks, int descTab);
void renderLogs(const std::vector<std::string>& logs, int logsTab, int maxLogLength);
void renderSeparator(int cols);

std::string toLower(const std::string& str);


#endif // TASKNINJA_H