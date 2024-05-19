#pragma once

#ifndef TASKNINJA_H
#define TASKNINJA_H

#include <vector>
#include <string>
#include "Task.h"

// Functions for working with tasks
std::vector<std::string> splitString(const std::string& input);
void addLog(std::vector<std::string>& logs, const std::string& message);
void clearLogs(std::vector<std::string>& logs);
void addTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens, std::vector<std::string>& logs);
void editTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens, std::vector<std::string>& logs);
void deleteTask(std::vector<Task>& tasks, const std::vector<std::string>& tokens, std::vector<std::string>& logs);
void showTaskDetails(std::vector<Task>& tasks, const std::vector<std::string>& tokens, std::vector<std::string>& logs);

std::string toLower(const std::string& str);


#endif // TASKNINJA_H