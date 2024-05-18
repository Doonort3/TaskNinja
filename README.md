![изображение](https://github.com/Doonort3/TaskNinja/assets/69197339/a8d00dd1-5cbb-4097-b0a6-b4e124e4cbf5)


# TaskNinja

is a powerful, console-based task manager written in C++ and built using CMake. Designed for efficiency and simplicity, TaskNinja allows users to manage their tasks directly from the command line, providing a lightweight alternative to GUI-based task managers.

## Features (updatable)

- **Add Tasks**: Easily add new tasks with a name and description.
- **Delete Tasks**: Remove tasks by specifying their index.
- **Edit Tasks**: Update task names and descriptions.
- **List Tasks**: Display all tasks with their names and descriptions.

## Future Features

- **Enhanced UI**: Improve the console interface with color and formatting.
- **Task Prioritization**: Assign priority levels to tasks.
- **Due Dates**: Set due dates for tasks and receive reminders.
- **Search Functionality**: Search for tasks by name or description.
- **Tags and Categories**: Organize tasks using tags and categories.
- **Export/Import**: Export tasks to a file and import tasks from a file.
- **Saving** The task list will be saved in a separate file for recovery between sessions.


## Installation

### Linux and macOS

1. Clone the repository:

    ```sh
    git clone https://github.com/Doonort3/TaskNinja.git
    ```

2. Navigate to the project directory:

    ```sh
    cd TaskNinja
    ```

3. Create a build directory and navigate into it:

    ```sh
    mkdir build
    cd build
    ```

4. Run CMake to configure the project:

    ```sh
    cmake ..
    ```

5. Build the project:

    ```sh
    make
    ```

### Windows (using MinGW)

1. Clone the repository:

    ```sh
    git clone https://github.com/Doonort3/TaskNinja.git
    ```

2. Navigate to the project directory:

    ```sh
    cd TaskNinja
    ```

3. Create a build directory and navigate into it:

    ```sh
    mkdir build
    cd build
    ```

4. Run CMake with MinGW Makefiles generator:

    ```sh
    cmake -G "MinGW Makefiles" ..
    ```

5. Build the project using MinGW make:

    ```sh
    mingw32-make
    ```

## Usage

1. Run the executable:

    ```sh
    ./TaskNinja
    ```

2. Enter commands in the running application: (help command will be added in the future)

   - **Add a Task**: To add a task, use the following command:
    
        ```sh
        add_task <task_name>
        ```
        
        Example:
        
        ```sh
        add_task "Write documentation"
        ```

    - **Delete a Task**: To delete a task, use the following command:
    
        ```sh
        del_task <task_number>
        ```
        
        Example:
        
        ```sh
        del_task 0
        ```

    - **Edit a Task**: To edit a task name or description, use the following commands:
    
        ```sh
        edit_task <task_number> -n <new_name>
        edit_task <task_number> -d <new_description>
        ```
        
        Examples:
        
        ```sh
        edit_task 1 -n "Write comprehensive documentation"
        edit_task 1 -d "Include all commands and usage examples"
        ```

    - **List Tasks**: To list all tasks, use the following command:
    
        ```sh
        list
        ```
        This will display all tasks with all the information about it.

## Contributing

Contributions are welcome! If you have any suggestions or find any issues, feel free to open an issue or submit a pull request.

## License

This project is licensed under the GNU General Public License (GPL). See the [LICENSE](LICENSE) file for details.

![изображение](https://github.com/Doonort3/TaskNinja/assets/69197339/0b53fe41-fe0a-44a7-b033-5d9f43f342ae)


