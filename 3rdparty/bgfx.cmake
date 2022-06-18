# cmake_minimum_required(VERSION 3.23)
# project(bgfx_project)

include(ProcessorCount)
ProcessorCount(CORE_COUNT)

# build bgfx library and its dependencies
add_custom_target(
    bgfx_build
    COMMAND make osx -j ${CORE_COUNT}
    BYPRODUCTS
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbgfxRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbimg_decodeRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbimg_encodeRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbimgRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbxRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libfcppRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libglsl-optimizerRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libglslangRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libspirv-crossRelease.a
    ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libspirv-optRelease.a
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bgfx
    USES_TERMINAL
)

#bgfx
add_library(bgfx STATIC IMPORTED GLOBAL)
target_include_directories(bgfx INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bgfx/include)
set_target_properties(bgfx PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbgfxRelease.a)
add_dependencies(bgfx bgfx_build)

#bimg
add_library(bimg STATIC IMPORTED GLOBAL)
target_include_directories(bimg INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bimg/include)
set_target_properties(bimg PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbimgRelease.a)

#bx
add_library(bx STATIC IMPORTED GLOBAL)
target_include_directories(bx INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bx/include)
set_target_properties(bx PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bgfx/.build/osx-arm64/bin/libbxRelease.a)

target_link_libraries(bgfx INTERFACE bimg bx)