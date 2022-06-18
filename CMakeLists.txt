cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

#check if conanbuildinfo.cmake exists
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
  #if not, generate it
  execute_process(
    COMMAND conan install . -if=${CMAKE_CURRENT_LIST_DIR}/build --build=missing
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  )
endif()

# Set project name using its directory name.
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJECT_NAME)

# Set the project name.
project(${PROJECT_NAME})

# include conan cmake modules
include(build/conanbuildinfo.cmake)
conan_basic_setup()

# Conan install command
add_custom_target(
    conan_install
    COMMAND conan install . -if=${CMAKE_CURRENT_LIST_DIR}/build --build=missing
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

# Copy compile_commands.json project root
add_custom_target(
  copy_compile_commands ALL
  ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_LIST_DIR}
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE PCHEADERS src/*.PCH.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${PCHEADERS})

# check operating system in CMAKE_SYSTEM_NAME and set defines
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  target_compile_definitions(${PROJECT_NAME} PUBLIC BUILD_WINDOWS)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  target_compile_definitions(${PROJECT_NAME} PUBLIC BUILD_LINUX)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  target_compile_definitions(${PROJECT_NAME} PUBLIC BUILD_DARWIN)
else()
  message(FATAL_ERROR "Unsupported operating system")
endif()

include(3rdparty/bgfx.cmake)
target_link_libraries(${PROJECT_NAME} bgfx)