#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include "TaskNinja.h"
#include "ConsoleUtils.h"
#include <sstream>

// Display the main header 
void displayTaskListHeader(const std::vector<Task>& tasks, std::vector<std::string>& logs);

// Display Tasks. Title and description to the table
void renderTasks(const std::vector<Task>& tasks, int nameTab, int descTab, int maxNameLength, int maxDescLength);

void renderLogs(const std::vector<std::string>& logs, int logsTab, int maxLogLength);
// Display separator
void renderSeparator(int cols);

#endif // RENDER_UTILS_H
