include(bgfx.cmake)
include(ShaderConductor.cmake)

add_library(thirdparty_libs INTERFACE)
target_link_libraries(thirdparty_libs INTERFACE bgfx ShaderConductor)