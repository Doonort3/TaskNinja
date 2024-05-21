#ifndef SWTasks_H
#define SWTasks_H

#include <string>
#include <vector>
#include "Task.h"

void saveTasksToFile(const std::vector<Task>& tasks);
std::vector<Task> loadTasksFromFile();
void saveLogsToFile(const std::vector<std::string>& logs);
std::vector<std::string> loadLogsFromFile();

#endif // SWTasks_H
