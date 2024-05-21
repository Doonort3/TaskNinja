/*****************************************************************//**
 * \file   Config.cpp
 * \brief  This file contains all customizable settings like markup proportions, paths to save data.
 * 
 * \author ikuyu
 * \date   May 2024
 *********************************************************************/

#include <string>
#include <filesystem>

#include "../include/Config.h"
#include "../include/ConsoleUtils.h"
#include "../include/FileSystemUtils.h"

int rows;                       // Console rows
int cols;                       // Console cols
int nameTab = 6;                // Left margin where the task name begins
int descTab;                    
int logsTab;
int indexSpace = 5;             // The number of characters in the cell with the task number
int nameSpace;
int logsSpace;
int descSpace;
int maxNameLength;              
int maxDescLength;
int maxLogsLength;

std::string ExecutablePath;
std::string saveDirectory;      // Path to the folder where the files for recovery will be saved
std::string saveFilePath;       // Path to data file


void updateConfig() {
    descTab = cols / 3;         // Changes depending on the cols of the console
    logsTab = cols - 30;        
    logsSpace = cols - logsTab;
    descSpace = cols - descTab - logsSpace;
    nameSpace = cols - indexSpace - descSpace - logsSpace;
    maxNameLength = nameSpace - 4;
    maxDescLength = descSpace - 3; // I picked up these numbers at random
    maxLogsLength = logsSpace - 3;

    ExecutablePath = getExecutablePath();
    size_t lastSlashPos = ExecutablePath.find_last_of("/\\");
    saveDirectory = ExecutablePath.substr(0, lastSlashPos + 1) + "Data\\"; // Setting the save folder as "Data"
    saveFilePath = saveDirectory + "tasks.txt"; // TODO: поправить
}

void updateConsoleSize() {
    getConsoleSize(rows, cols); // TODO: избавиться от повторения 
}