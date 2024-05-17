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
void addTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens);
void deleteTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens);
void listTasks(const std::vector<Task>& tasks);
void editTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens);
std::string toLower(const std::string& str);

#endif // TASKNINJA_H