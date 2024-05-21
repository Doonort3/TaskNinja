#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <filesystem>

// AANSI Escape color codes. 
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

extern int rows;
extern int cols;

extern int nameTab;
extern int indexSpace;
extern int descTab;
extern int logsTab;
extern int logsSpace;
extern int descSpace;
extern int nameSpace;
extern int maxNameLength;
extern int maxDescLength;
extern int maxLogsLength;

extern std::string ExecutablePath;
extern std::string saveDirectory;
extern std::string saveFilePath;


void updateConfig();

void updateConsoleSize();

#endif // CONFIG_H