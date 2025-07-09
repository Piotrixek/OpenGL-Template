cmake_minimum_required(VERSION 3.10)
project(OpenGL_Project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(LIBS_DIR "C:/libs")

add_library(glad STATIC ${LIBS_DIR}/OpenGL/glad/src/glad.c)
target_include_directories(glad PUBLIC ${LIBS_DIR}/OpenGL/glad/include)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "${LIBS_DIR}/OpenGL/glfw/lib-vc2022/glfw3.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBS_DIR}/OpenGL/glfw/include")

add_library(imgui STATIC
    ${LIBS_DIR}/imgui-docking/imgui.cpp
    ${LIBS_DIR}/imgui-docking/imgui_draw.cpp
    ${LIBS_DIR}/imgui-docking/imgui_tables.cpp
    ${LIBS_DIR}/imgui-docking/imgui_widgets.cpp
    ${LIBS_DIR}/imgui-docking/backends/imgui_impl_glfw.cpp
    ${LIBS_DIR}/imgui-docking/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC 
    ${LIBS_DIR}/imgui-docking
    ${LIBS_DIR}/OpenGL/glfw/include
    ${LIBS_DIR}/OpenGL/glad/include
)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
target_include_directories(main PUBLIC
    src 
    ${LIBS_DIR}/OpenGL/glm
    ${LIBS_DIR}/OpenGL/glad/include
    ${LIBS_DIR}/OpenGL/glfw/include
    ${LIBS_DIR}/OpenGL
    ${LIBS_DIR}/imgui-docking
    ${LIBS_DIR}/imgui-docking/backends
    ${LIBS_DIR}/tinyfiledialogs
)

set_target_properties(main PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:main>"
)

target_link_libraries(main glad glfw imgui opengl32)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${LIBS_DIR}/fonts/Fira_Code_v6.2/ttf"
    "$<TARGET_FILE_DIR:main>/fonts"
    COMMENT "copying fonts to build directory"
)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:main>/shaders"
    COMMENT "copying shaders to build directory"
)
