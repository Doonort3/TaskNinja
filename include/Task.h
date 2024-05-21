#ifndef TASK_H
#define TASK_H

#include <string>

struct Task {
    int index = 0;
    std::string name;
    std::string description;
};

#endif // TASK_H