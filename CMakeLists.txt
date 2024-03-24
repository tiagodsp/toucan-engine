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
        -fvisibility=hidden
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
        -Wno-declaration-after-statement
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

# Conan dependencies
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(imgui REQUIRED)

set(CONANDEPS glm SDL2 spdlog imgui)

message("Conan dependencies: ${CONANDEPS}")

# Conan install command
add_custom_target(
    conan_install
    COMMAND conan install . -of=${CMAKE_CURRENT_LIST_DIR}/build --build=missing -s build_type=${CMAKE_BUILD_TYPE}
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

# Conan dependencies
find_package(glm)
find_package(SDL2)
find_package(spdlog)
find_package(imgui)

set(CONANDEPS  glm::glm  SDL2::SDL2main  spdlog::spdlog  imgui::imgui )

# Toucan ---------------------------------------------------------------
file(GLOB_RECURSE SOURCES core/*.cpp)
file(GLOB_RECURSE PCHEADERS core/*.PCH.h)
add_library(${PROJECT_NAME}_core SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME}_core PUBLIC ${CONANDEPS})
target_include_directories(${PROJECT_NAME}_core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/core)
target_precompile_headers(${PROJECT_NAME}_core PRIVATE ${PCHEADERS})
add_dependencies(${PROJECT_NAME}_core copy_data)

# Add thirdparty libraries
add_subdirectory(3rdparty)
target_link_libraries(${PROJECT_NAME}_core PRIVATE thirdparty_libs)

# Generate api.h
# set MODULE_NAME_UPPER as uppercase of <module_name>
string(TOUPPER core MODULE_NAME_UPPER)
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/templates/api.h.in ${CMAKE_CURRENT_LIST_DIR}/generated/core/core.api.gen.h)
target_include_directories(${PROJECT_NAME}_core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/generated/core)
target_compile_definitions(${PROJECT_NAME}_core PRIVATE ${MODULE_NAME_UPPER}_BUILD_SHARED)

# Editor ---------------------------------------------------------------
file(GLOB_RECURSE SOURCES editor/*.cpp)
file(GLOB_RECURSE PCHEADERS editor/*.PCH.h)
add_executable(${PROJECT_NAME}_editor ${SOURCES})
target_include_directories(${PROJECT_NAME}_editor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/editor)
target_precompile_headers(${PROJECT_NAME}_editor PUBLIC ${PCHEADERS})
add_dependencies(${PROJECT_NAME}_editor ${PROJECT_NAME}_core)
target_link_libraries(${PROJECT_NAME}_editor PRIVATE ${PROJECT_NAME}_core)

string(TOUPPER editor MODULE_NAME_UPPER)
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/templates/api.h.in ${CMAKE_CURRENT_LIST_DIR}/generated/editor/editor.api.gen.h)
target_include_directories(${PROJECT_NAME}_editor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/generated/editor)
target_compile_definitions(${PROJECT_NAME}_editor PRIVATE ${MODULE_NAME_UPPER}_BUILD_SHARED)

# check operating system in CMAKE_SYSTEM_NAME and set defines
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  add_compile_definitions(BUILD_WINDOWS)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  add_compile_definitions(BUILD_LINUX)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  add_compile_definitions(BUILD_DARWIN)
else()
  message(FATAL_ERROR "Unsupported operating system")
endif()
