cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

project(vinny LANGUAGES C CXX)

# set C++ standard (required by libultraship)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)

# macOS-specific settings
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    enable_language(OBJCXX)
    set(CMAKE_OBJC_FLAGS "${CMAKE_OBJC_FLAGS} -fobjc-arc")
    set(CMAKE_OBJCXX_FLAGS "${CMAKE_OBJCXX_FLAGS} -fobjc-arc")
endif()

# disable building utility programs (code generation tools, etc.) from libultraship dependencies
set(BUILD_UTILS OFF CACHE STRING "no utilities")
# link against static libraries instead of shared/dynamic libraries
set(BUILD_SHARED_LIBS OFF CACHE STRING "static libs")

add_executable(${PROJECT_NAME}
    vinny.cxx
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        libultraship
)
