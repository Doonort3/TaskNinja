#ifndef OPEN_H
#define OPEN_H

#include <vector>
#include <string>
#include "Task.h"

void manageTask(std::vector<Task>& tasks, size_t taskIndex, std::vector<std::string>& logs);
void openLogs(const std::vector<std::string>& logs);
#endif // OPEN_H
