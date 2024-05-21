/*****************************************************************//**
 * \file   WR.cpp
 * \brief  This file works with writing and reading files.
 * 
 * \author ikuyu
 * \date   May 2024
 *********************************************************************/


#include "../include/WR.h"
#include "../include/ConsoleUtils.h"
#include "../include/FileSystemUtils.h"
#include "../include/Config.h"
#include <fstream>
#include <iostream>
#include <sstream>


const std::string TASKS_FILE_PATH = getSaveFilePath();
const std::string LOGS_FILE_PATH = getSaveLogsPath();

void saveTasksToFile(const std::vector<Task>& tasks) {
    clearConsole();
    std::ofstream file(TASKS_FILE_PATH);
    if (file.is_open()) {
        for (const Task& task : tasks) {
            file << task.index << ',' << task.name << ',' << task.description << '\n';
        }
        file.close();
        if (!tasks.empty()) {
            std::cout << "Tasks saved successfully to " << TASKS_FILE_PATH << std::endl;
        }

    }
    else {
        //std::cerr << "Unable to open file for saving tasks: " << TASKS_FILE_PATH << std::endl;
        //std::cout << std::endl << "Press any key to close..." << std::endl;
        //getchar();
    }
}

std::vector<Task> loadTasksFromFile() {
    std::vector<Task> tasks;
    std::ifstream file(TASKS_FILE_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string idStr, name, description;
            if (std::getline(iss, idStr, ',') && std::getline(iss, name, ',') && std::getline(iss, description)) {
                int id = std::stoi(idStr);
                tasks.push_back({ id, name, description });
            }
            else {
                std::cerr << "Error reading task data from line: " << line << std::endl;
            }
        }
        file.close();
        std::cout << "Tasks loaded successfully from " << TASKS_FILE_PATH << std::endl;
    }
    else {
        std::cerr << "Unable to open file for loading tasks: " << TASKS_FILE_PATH << "\n\n";
    }
    return tasks;
}

void saveLogsToFile(const std::vector<std::string>& logs) {
    // std::string logFilePath = saveDirectory + "logs.txt";
    std::ofstream logFile(LOGS_FILE_PATH);
    if (logFile.is_open()) {
        for (const auto& log : logs) {
            logFile << log << std::endl;
        }
        logFile.close();
        if (!logs.empty()) {
            std::cout << "Logs saved successfully to " << LOGS_FILE_PATH << std::endl;
        }
        
        //std::cout << std::endl << "Press any key to close..." << std::endl;
        // getchar();
    }
    else {
        std::cerr << "Unable to open log file for writing: " << LOGS_FILE_PATH << std::endl;
    }
}

std::vector<std::string> loadLogsFromFile() {
    std::vector<std::string> logs;
    std::ifstream logFile(LOGS_FILE_PATH);
    if (logFile.is_open()) {
        std::string logEntry;
        while (std::getline(logFile, logEntry)) {
            logs.push_back(logEntry);
        }
        logFile.close();
        //std::cout << "Logs loaded successfully from " << LOGS_FILE_PATH << std::endl;
        //std::cout << std::endl << "Press any key to close..." << std::endl;
        //getchar();
    }
    else {
        std::cerr << "Unable to open log file for reading: " << LOGS_FILE_PATH << std::endl;
    }
    return logs;
}