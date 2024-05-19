#pragma once

#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include "TaskNinja.h"
#include "ConsoleUtils.h"
#include <sstream>
#include <vector>
#include <string>

void displayTaskListHeader(const std::vector<Task>& tasks, std::vector<std::string>& logs);
void renderTasks(const std::vector<Task>& tasks, int descTab, int nameTab, int maxNameLength, int maxDescLength);
void renderLogs(const std::vector<std::string>& logs, int logsTab, int maxLogLength);
void renderSeparator(int cols);

#endif // RENDER_UTILS_H
