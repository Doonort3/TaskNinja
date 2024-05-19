#include "../include/Task.h"
#include "../include/TaskNinja.h"
#include "../include/ConsoleUtils.h"
#include "../include/RenderUtils.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // vector<Task> tasks; раскоментируй когда коммитить будешь
    // bool isTaskOpen;
    vector<string> logs;
    string userInput;
    int rows, cols;
    getConsoleSize(rows, cols);

    // DEBUG START
    std::vector<Task> tasks = {
    {0, "Short task name", "Short description"},
    {1, "This is a much longer task name that should be truncated", "This description is also very long and should be truncated to fit in the console"}
    };

    // showTaskDetails(tasks, { "open_task", "0" }, logs, isTaskOpen);
    // cout << "\n\n" << isTaskOpen << "\n";
    //setCursorPosition(0, rows - 1);
    //userInput = getInput();
    // DEBUG END

 /*   clearConsole();
    displayTaskListHeader(tasks, logs);
    setCursorPosition(0, rows - 1);
    cout << "> ";
    getline(cin, userInput);*/

    while (true) {
        // isTaskOpen = false;

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
            else if (tokens[0] == "open_task") {
                showTaskDetails(tasks, tokens, logs);
                getchar();
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
