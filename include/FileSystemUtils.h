#ifndef FILE_SYSTEM_UTILS_H
#define FILE_SYSTEM_UTILS_H

#include <string>
#include <vector>
#include "../include/Task.h"

std::string getExecutablePath();
std::string getSaveDirectory();
std::string getSaveFilePath();
std::string getSaveLogsPath();
std::string getLogFilePath();
void createSaveDirectory();
void createSaveFile();
void removeTaskFromFile(size_t taskIndex);
void saveNewTasksToFile(const std::vector<Task>& tasks);
void ensureSaveFileExists();
void ensureLogFileExists();

#endif // FILE_SYSTEM_UTILS_H
