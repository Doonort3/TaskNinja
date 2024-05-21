cmake_minimum_required (VERSION 3.8)

# Enable hot reloading for MSVC compilers, if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TaskNinja")

add_executable (TaskNinja "src/TaskNinja.cpp" "include/TaskNinja.h" "src/main.cpp" "include/ConsoleUtils.h" "src/ConsoleUtils.cpp" "include/RenderUtils.h" "src/RenderUtils.cpp" "include/Task.h"   "include/Config.h" "src/Config.cpp" "src/Open.cpp" "include/Open.h" "include/WR.h" "src/WR.cpp" "include/FileSystemUtils.h" "src/FileSystemUtils.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TaskNinja PROPERTY CXX_STANDARD 20)
endif()

