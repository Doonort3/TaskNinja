# CMakeList.txt: проект CMake для TaskNinja; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TaskNinja")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (TaskNinja "src/TaskNinja.cpp" "include/TaskNinja.h" "src/main.cpp" "include/ConsoleUtils.h" "src/ConsoleUtils.cpp" "include/RenderUtils.h" "src/RenderUtils.cpp" "include/Task.h"  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TaskNinja PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
