include(bgfx.cmake)

add_library(thirdparty_libs INTERFACE)
target_link_libraries(thirdparty_libs PRIVATE INTERFACE bgfx)