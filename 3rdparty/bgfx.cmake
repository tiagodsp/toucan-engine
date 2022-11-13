# cmake_minimum_required(VERSION 3.23)
# project(bgfx_project)

include(ProcessorCount)
ProcessorCount(CORE_COUNT)

# detect the platform
if (WIN32)
    set(PLATFORM "windows")
elseif (APPLE)
    set(PLATFORM "osx")
elseif (UNIX)
    set(PLATFORM "linux")
endif()

# detect if arm or x86
if(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "arm")
    set(ARCH "arm64")
else()
    set(ARCH "x64")
endif()

# detect the build type
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(BUILD_TYPE "debug")
else()
    set(BUILD_TYPE "release")
endif()

# build bgfx library and its dependencies
add_custom_target(
    bgfx_build
    COMMAND make ${PLATFORM}-${ARCH}-${BUILD_TYPE} -j ${CORE_COUNT}
    BYPRODUCTS
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbgfx${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbimg_decode${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbimg_encode${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbimg${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbx${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libfcpp${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libglsl-optimizer${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libglslang${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libspirv-cross${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libspirv-opt${CMAKE_BUILD_TYPE}.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/shaderc${CMAKE_BUILD_TYPE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bgfx
    USES_TERMINAL
)

#bgfx
add_library(bgfx STATIC IMPORTED GLOBAL)
target_include_directories(bgfx INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bgfx/include)
set_target_properties(bgfx PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbgfx${CMAKE_BUILD_TYPE}.a)
add_dependencies(bgfx bgfx_build)

#shaderc
add_executable(shaderc IMPORTED GLOBAL)
set_target_properties(shaderc PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/shaderc${CMAKE_BUILD_TYPE})
add_dependencies(shaderc bgfx_build)

#bimg
add_library(bimg STATIC IMPORTED GLOBAL)
target_include_directories(bimg INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bimg/include)
set_target_properties(bimg PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbimg${CMAKE_BUILD_TYPE}.a)

#bx
add_library(bx STATIC IMPORTED GLOBAL)
target_include_directories(bx INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bx/include)
set_target_properties(bx PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/${PLATFORM}-${ARCH}/bin/libbx${CMAKE_BUILD_TYPE}.a)

target_link_libraries(bgfx INTERFACE bimg bx)