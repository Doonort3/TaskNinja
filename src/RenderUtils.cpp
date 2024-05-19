#include "../include/RenderUtils.h"
#include "../include/TaskNinja.h"

void displayTaskListHeader(const std::vector<Task>& tasks, std::vector<std::string>& logs) {
    int rows, cols;
    getConsoleSize(rows, cols);

    /* "Tab" prefir - Co-ordinates by X 
        "Space" prefix - Space occupied by the table row */
    int nameTab = 6;
    int indexSpace = 5; 
    int descTab = cols / 4;
    int logsTab = cols - 30;
    int logsSpace = cols - logsTab;
    int descSpace = cols - descTab - logsSpace;
    int nameSpace = cols - indexSpace - descSpace - logsSpace;
    int maxNameLength = nameSpace - 4;
    int maxDescLength = descSpace - 3;
    int maxLogsLength = logsSpace - 3;

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
        renderTasks(tasks, descTab, nameTab, maxNameLength, maxDescLength);
        renderLogs(logs, logsTab, 28);
    }
}

void renderTasks(const std::vector<Task>& tasks, int descTab, int nameTab, int maxNameLength, int maxDescLength) {
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        std::string displayName = task.name;
        std::string displayDesc = task.description;

        if (displayName.length() > maxNameLength) {
            displayName = displayName.substr(0, maxNameLength - 3) + "...";
        }

        if (displayDesc.length() > maxDescLength) {
            displayDesc = displayDesc.substr(0, maxDescLength - 3) + "...";
        }
        // 2 cols, i + 2 rows (start 3 row). Each iteration of rows is added
        setCursorPosition(2, i + 2);
        std::cout << i;
        // 6 cols, i + 2 rows (start 3 row).
        setCursorPosition(nameTab, i + 2);
        std::cout << "| " << displayName;

        // cols / 4 (ex. windows 120 / 4 = 30), i + 2 rows (start 3 row).
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
    for (size_t i = 0; i < cols; i++)
    {
        std::cout << "_";
    }
}