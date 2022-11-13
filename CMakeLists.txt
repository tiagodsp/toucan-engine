cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Set project name using its directory name.
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJECT_NAME)

# Set the project name.
project(${PROJECT_NAME} CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_BUILD_RPATH "./")
set(CMAKE_INSTALL_RPATH "./")

# set(TOUCAN_BUILD_DIR ${CMAKE_CURRENT_LIST_DIR}/output)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOUCAN_BUILD_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOUCAN_BUILD_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TOUCAN_BUILD_DIR}/lib)

# Set compiler flags -----------------------------------------------------------------------------------
message("Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # G++
    add_compile_options(
        -MD
        -fPIC
        -Wall
        -Wextra
        -fvisibility=hidden
        -Wno-unused-parameter
        -Wno-unused-variable
        -Wno-documentation
        -Wno-reorder
    )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "LLVM")
    #Clang
    add_compile_options(
        -MDd
        -Wall
        -Wextra
        -fvisibility=hidden
        -Wno-unused-parameter
        -Wno-unused-variable
        -fcxx-exceptions
        -Wno-documentation
        -Wno-reorder
    )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    #Clang
    add_compile_options(
        -MDd
        -fPIC
        -fms-compatibility
        -fdiagnostics-show-template-tree
        -fdelayed-template-parsing
        -Wno-unused-parameter
        -Wno-unused-variable
        -Wno-documentation
        -Wno-reorder
        -Wno-c++98-compat-pedantic
        -Wno-documentation-unknown-command
        -Wno-deprecated-declarations
        -Wno-reserved-id-macro
        -Wno-ambiguous-reversed-operator
        -Wno-deprecated-declarations
    )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    #Clang
    add_compile_options(
        # -fPIC
        # -fms-compatibility
        # -fdiagnostics-show-template-tree
        # -fdelayed-template-parsing
        -Wno-unused-parameter
        -Wno-unused-variable
        -Wno-documentation
        -Wno-reorder
        -Wno-c++98-compat-pedantic
        -Wno-documentation-unknown-command
        -Wno-deprecated-declarations
        -Wno-reserved-id-macro
        -Wno-ambiguous-reversed-operator
        -Wno-deprecated-declarations
    )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # MSVC
    add_compile_options(/EHsc /MDd /W2 /c)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Emscripten")
    add_compile_options(-Wall -Wextra -fvisibility=hidden -Wno-unused-parameter -Wno-unused-variable -fcxx-exceptions -Wno-documentation -Wno-reorder)
    # Prefixes/suffixes for building
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    # Prefixes/suffixes for finding libraries
    set(CMAKE_FIND_LIBRARY_PREFIXES "")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".bc")
endif()
# ----------------------------------------------------------------------------------------------------

#check if conanbuildinfo.cmake exists
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
  #if not, generate it
  execute_process(
    COMMAND conan install . -if=${CMAKE_CURRENT_LIST_DIR}/build --build=missing
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  )
endif()

# include conan cmake modules
include(build/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS)

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

# Copy assets to build directory
add_custom_target(
  copy_data ALL
  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR}/data/
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE PCHEADERS src/*.PCH.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${PCHEADERS})
add_dependencies(${PROJECT_NAME} copy_data)


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

add_subdirectory(3rdparty)
target_link_libraries(${PROJECT_NAME} thirdparty_libs)