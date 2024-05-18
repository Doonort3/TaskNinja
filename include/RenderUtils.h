#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include "TaskNinja.h"
#include "ConsoleUtils.h"
#include <sstream>

// Display the main header 
void displayTaskListHeader(const std::vector<Task>& tasks, std::vector<std::string>& logs) {
    int rows, cols;
    getConsoleSize(rows, cols);
    int descTab = cols / 4;
    int logsTab = cols - 30;

    if (tasks.empty()) {
        std::cout << "The task list is empty.\n";
    }
    else {
        std::cout << "Index | Name";
        setCursorPosition(descTab, 0);
        std::cout << "| Description" << "\n";
        setCursorPosition(logsTab, 0);
        std::cout << "| Logs" << "\n";
        setCursorPosition(0, 1);

        renderSeparator(cols);
        renderTasks(tasks, descTab);
        renderLogs(logs, logsTab, 28);
    }
}

// Display Tasks. Title and description to the table
void renderTasks(const std::vector<Task>& tasks, int descTab) {
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        setCursorPosition(2, i + 2);
        std::cout << i << "   | " << task.name;

        setCursorPosition(descTab, i + 2);
        std::cout << "| " << task.description << "\n";
    }
}

// Display logs with line breaks
void renderLogs(const std::vector<std::string>& logs, int logsTab, int maxLogLength) {
    int logIndex = 0;
    for (const auto& log : logs) {
        std::string currentLog = log;
        // As long as the current log exceeds the maximum length, output part of it and truncate it
        while (currentLog.length() > maxLogLength) {
            // Output the first maxLogLength characters of the current log taking into account coordinates
            setCursorPosition(logsTab, 2 + logIndex);
            std::cout << "| " << currentLog.substr(0, maxLogLength) << "\n";
            // Truncate the current log, leaving only the remaining part of the log
            currentLog = currentLog.substr(maxLogLength);
            logIndex++;
        }
        // Output the rest of the current log, if any
        if (!currentLog.empty()) {
            setCursorPosition(logsTab, 2 + logIndex);
            std::cout << "| " << currentLog << "\n";
            logIndex++;
        }
    }
}

void renderSeparator(int cols) {
    for (size_t i = 0; i < cols; i++)
    {
        std::cout << "_";
    }
}




#endif