/*****************************************************************//**
 * \file   RenderUtils.cpp
 * \brief  This file contains the functions for rendering the interface.
 * 
 * \author ikuyu
 * \date   May 2024
 *********************************************************************/

#include "../include/Task.h"
#include "../include/RenderUtils.h"
#include "../include/TaskNinja.h"
#include "../include/Config.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

void displayTaskListHeader(const std::vector<Task>& tasks, std::vector<std::string>& logs) {
    if (tasks.empty()) {
        std::cout << "The task list is empty.\n";
    }
    else {
        std::cout << "Index | Name";
        setCursorPosition(descTab, 0);
        std::cout << "| Description";
        setCursorPosition(logsTab, 0);
        std::cout << "| Logs";
        setCursorPosition(0, 1);

        renderSeparator(cols);
        renderTasks(tasks, descTab, nameTab, maxNameLength, maxDescLength);
        renderLogs(logs, logsTab, maxLogsLength);
    }
}

void renderTasks(const std::vector<Task>& tasks, int descTab, int nameTab, int maxNameLength, int maxDescLength) {
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        std::string displayName = task.name;
        std::string displayDesc = task.description;

        // Truncate name/description if it's too long
        if (displayName.length() > maxNameLength) {
            displayName = displayName.substr(0, maxNameLength - 3) + "...";
        }

        if (displayDesc.length() > maxDescLength) {
            displayDesc = displayDesc.substr(0, maxDescLength - 3) + "...";
        }

        setCursorPosition(2, i + 2);
        std::cout << std::setw(5) << std::left << i; // Alignment

        setCursorPosition(nameTab, i + 2);
        std::cout << "| " << displayName;

        setCursorPosition(descTab, i + 2);
        std::cout << "| " << displayDesc << "\n";
    }
}

void renderLogs(const std::vector<std::string>& logs, int logsTab, int maxLogLength) {
    int logIndex = 0;
    for (const auto& log : logs) {
        std::string currentLog = log;
        // Check if the current log exceeds the maximum length
        if (currentLog.length() > maxLogLength) {
            // Output the truncated log with ellipsis
            setCursorPosition(logsTab, 2 + logIndex);
            std::cout << "| " << currentLog.substr(0, maxLogLength - 3) << "..." << "\n";
        }
        else {
            // Output the entire log
            setCursorPosition(logsTab, 2 + logIndex);
            std::cout << "| " << currentLog << "\n";
        }
        logIndex++;
    }
}

void renderSeparator(int cols) {
    std::cout << std::string(cols, '_') << std::endl;
}

bool displayLoadingMessages(const std::vector<Task>& tasks, const std::vector<std::string>& logs) {
    int index = 3;
    if (!tasks.empty()) {
        setCursorPosition(cols - 21, rows - index);
        std::cout << "[" ANSI_COLOR_GREEN "ok" ANSI_COLOR_RESET "] load tasks" << std::endl;
        index++;
    }
    else {
        setCursorPosition(cols - 21, rows - index);
        std::cout << "[" ANSI_COLOR_YELLOW "warning" ANSI_COLOR_RESET "] load tasks" << std::endl;
        index++;
    }

    if (!logs.empty()) {
        setCursorPosition(cols - 21, rows - index);
        std::cout << "[" ANSI_COLOR_GREEN "ok" ANSI_COLOR_RESET "] load logs" << std::endl;
        index++;
    }
    else {
        setCursorPosition(cols - 21, rows - index);
        std::cout << "[" ANSI_COLOR_YELLOW "warning" ANSI_COLOR_RESET "] load logs" << std::endl;
        index++;
    }
    setCursorPosition(0, 0);
    return true;
}

