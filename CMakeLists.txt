cmake_minimum_required(VERSION 3.25)
project(RoboOpVisualizer LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(RoboOp
    GIT_REPOSITORY https://github.com/RandomPythonProgrammer/RoboOp.git
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(RoboOp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

FetchContent_Declare(soil2
    GIT_REPOSITORY https://github.com/Jacob-Tate/soil2-cmake.git
)
FetchContent_MakeAvailable(soil2)

include_directories(include)
include_directories(imgui)
include_directories(implot)
include_directories(font)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB IMGUI_CORE "imgui/*.cpp")
file(GLOB IMPLOT_CORE "implot/*.cpp")
add_executable(main ${SOURCES} ${IMGUI_CORE} imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp ${IMPLOT_CORE})

target_link_libraries(main PRIVATE glfw)
target_link_libraries(main PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(main PRIVATE RoboOp)
target_link_libraries(main PRIVATE soil2)
target_compile_features(main PRIVATE cxx_std_20)

file(COPY font/fa-solid-900.ttf DESTINATION ${CMAKE_BINARY_DIR})