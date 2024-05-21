/*****************************************************************//**
 * \file   FileSystemUtils.cpp
 * \brief  This file contains an implementation of... 
 *         of creating and writing tasks and logs to the files intended for them? (I'll rethink this file and functionality)
 * 
 * \author ikuyu
 * \date   May 2024
 *********************************************************************/

#include "../include/FileSystemUtils.h"
#include "../include/Config.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "../include/Task.h"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <limits.h>
#endif

std::string getExecutablePath() {
    std::string executablePath;

#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    executablePath = std::string(buffer);
#elif __linux__
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        result[count] = '\0';
        executablePath = std::string(result);
    }
#endif

    return executablePath;
}

std::string getSaveDirectory() {
    std::string executablePath = getExecutablePath();
    size_t lastSlashPos = executablePath.find_last_of("/\\");
    return executablePath.substr(0, lastSlashPos + 1) + "Data\\";
}

std::string getSaveFilePath() {
    std::string saveDirectory = getSaveDirectory();
    return saveDirectory + "tasks.txt";
}

std::string getSaveLogsPath() {
    std::string saveDirectory = getSaveDirectory();
    return saveDirectory + "logs.txt";
}

void createSaveDirectory() {
    std::string saveDirectory = getSaveDirectory();

    if (!std::filesystem::exists(saveDirectory)) {
        std::filesystem::create_directory(saveDirectory);
        std::cout << "Created directory: " << saveDirectory << std::endl;
    }
}

void createSaveFile() {
    std::string saveFilePath = getSaveFilePath();
    if (!std::filesystem::exists(saveFilePath)) {
        std::ofstream saveFile(saveFilePath);
        if (saveFile.is_open()) {
            std::cout << "Created file: " << saveFilePath << std::endl;
            saveFile.close();
        }
        else {
            std::cerr << "Unable to create file: " << saveFilePath << std::endl;
        }
    }
}

void removeTaskFromFile(size_t taskIndex) {
    std::string saveFilePath = getSaveFilePath();
    std::ifstream inputFile(saveFilePath);
    std::vector<Task> tasks;
    Task task;

    while (inputFile >> task.index >> task.name >> std::ws && std::getline(inputFile, task.description)) {
        tasks.push_back(task);
    }
    inputFile.close();

    tasks.erase(tasks.begin() + taskIndex);

    std::ofstream outputFile(saveFilePath);
    for (const auto& t : tasks) {
        outputFile << t.index << " " << t.name << " " << t.description << std::endl;
    }
    outputFile.close();
}

void saveNewTasksToFile(const std::vector<Task>& tasks) {
    std::string saveFilePath = getSaveFilePath();
    std::ifstream inputFile(saveFilePath);
    std::vector<Task> existingTasks;
    Task task;

    while (inputFile >> task.index >> task.name >> std::ws && std::getline(inputFile, task.description)) {
        existingTasks.push_back(task);
    }
    inputFile.close();

    std::vector<Task> newTasks;
    for (const auto& t : tasks) {
        auto it = std::find_if(existingTasks.begin(), existingTasks.end(), [&t](const Task& existingTask) {
            return existingTask.index == t.index;
            });
        if (it == existingTasks.end()) {
            newTasks.push_back(t);
        }
    }

    std::ofstream outputFile(saveFilePath, std::ios::app);
    for (const auto& newTask : newTasks) {
        outputFile << newTask.index << " " << newTask.name << " " << newTask.description << std::endl;
    }
    outputFile.close();
}

std::string getLogFilePath() {
    std::string saveDirectory = getSaveDirectory();
    return saveDirectory + "logs.txt";
}

void ensureLogFileExists() {
    std::string logFilePath = getLogFilePath();
    if (!std::filesystem::exists(logFilePath)) {
        std::ofstream logFile(logFilePath);
        if (logFile.is_open()) {
            std::cout << "Created log file: " << logFilePath << std::endl;
            logFile.close();
        }
        else {
            std::cerr << "Unable to create log file: " << logFilePath << std::endl;
        }
    }
}

void ensureSaveFileExists() {
    createSaveDirectory();
    createSaveFile();
}
