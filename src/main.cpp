#include "../include/TaskNinja.h"
#include "../include/ConsoleUtils.h"
#include "../include/RenderUtils.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<Task> tasks;
    vector<string> logs;
    string userInput;
    int rows, cols;
    getConsoleSize(rows, cols);

    while (true) {
        clearConsole();
        displayTaskListHeader(tasks, logs);
        setCursorPosition(0, rows - 1); // I set the caret to the very bottom of the console for the command entry field
        cout << "> ";
        getline(cin, userInput);

        string commands = toLower(userInput);
        vector<string> tokens = splitString(commands);

        if (!tokens.empty()) {
            if (tokens[0] == "add_task") {
                addTask(tasks, tokens, logs);
            }
            else if (tokens[0] == "del_task") {
                deleteTask(tasks, tokens, logs);
            }
            else if (tokens[0] == "edit_task") {
                editTask(tasks, tokens, logs);
            }
            else if (tokens[0] == "clear_logs") {
                clearLogs(logs);
            }
            else {
                addLog(logs, "Unknown cmd: " + tokens[0]);
            }
        }
        else {
            addLog(logs, "Empty input.");
        }
    }
    return 0;
}
