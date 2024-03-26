# cmake_minimum_required(VERSION 3.23)
# project(bgfx_project)

include(ProcessorCount)
ProcessorCount(CORE_COUNT)

# Platform detection
string(TOLOWER ${CMAKE_SYSTEM_NAME} PLATFORM)
if(PLATFORM STREQUAL "darwin")
    set(PLATFORM "osx")
endif()

# Architecture detection
if(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "arm")
    set(ARCH "arm64")
else()
    set(ARCH "x64")
endif()

# Build type detection
set(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
if(NOT BUILD_TYPE)
    set(BUILD_TYPE "release")
endif()

# build bgfx library and its dependencies
if(${PLATFORM} STREQUAL "windows")
    add_custom_target(
        bgfx_build
        COMMAND ${CMAKE_CURRENT_LIST_DIR}/bx/tools/bin/windows/genie.exe --with-tools --with-examples vs2022
        COMMAND msbuild /p:Configuration=${BUILD_TYPE} ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/projects/vs2022/bgfx.sln /p:WindowsTargetPlatformVersion=10.0
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bgfx
        USES_TERMINAL
    )
else()
    add_custom_target(
        bgfx_build
        COMMAND make ${PLATFORM}-${ARCH}-${BUILD_TYPE} -j ${CORE_COUNT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bgfx
        USES_TERMINAL
    )
endif()


add_custom_command(
    TARGET bgfx_build
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/bgfx/tools
    # copy shaderc, texturec, geometryc, geometryv
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/shaderc${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_BINARY_DIR}/bgfx/tools/shaderc
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/texturec${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_BINARY_DIR}/bgfx/tools/texturec
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/geometryc${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_BINARY_DIR}/bgfx/tools/geometryc
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/geometryv${CMAKE_BUILD_TYPE} ${CMAKE_CURRENT_BINARY_DIR}/bgfx/tools/geometryv
)

function(create_imported_target TARGET_NAME TYPE)
    if(${TYPE} STREQUAL "library")
        add_library(${TARGET_NAME} STATIC IMPORTED)
        set_target_properties(${TARGET_NAME} PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/lib${TARGET_NAME}${BUILD_TYPE}.a)
    elseif(${TYPE} STREQUAL "executable")
        add_executable(${TARGET_NAME} IMPORTED)
        set_target_properties(${TARGET_NAME}
            PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/${TARGET_NAME}${BUILD_TYPE}
        )
    endif()
    target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/${TARGET_NAME}/include)
    add_dependencies(${TARGET_NAME} bgfx_build)
endfunction()

# Create imported targets
create_imported_target(bgfx "library")
create_imported_target(bimg "library")
create_imported_target(bx "library")
create_imported_target(shaderc "executable")

target_link_libraries(bgfx INTERFACE bimg bx)