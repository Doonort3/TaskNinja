#include "TaskNinja.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<Task> tasks;
    string userInput;

    while (true) {
        cout << "> ";
        getline(cin, userInput);

        // Convert string to lower case
        string commands = toLower(userInput);
        vector<string> tokens = splitString(commands);

        if (!tokens.empty()) {
            if (tokens[0] == "add_task") {
                addTask(tasks, tokens);
            }
            else if (tokens[0] == "del_task") {
                deleteTask(tasks, tokens);
            }
            else if (tokens[0] == "list") {
                listTasks(tasks);
            }
            else if (tokens[0] == "edit_task") {
                editTask(tasks, tokens);
            }
            else {
                cout << "Unknown command: " << tokens[0] << "\n";
            }
        }
        else {
            cout << "Empty input. Enter the command.\n";
        }
    }
    return 0;
}
