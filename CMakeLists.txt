cmake_minimum_required(VERSION 3.10)

project(Demo)

set(EXE demo_app)

set(IMGUI_DIR ./imgui)
set(GLAD_DIR ./glad)
set(SRC_DIR ./src)
set(BACKEND_DIR ./backend)

file(GLOB imgui_SRC "./imgui/*.cpp")
file(GLOB src_SRC "./src/*.cpp")
file(GLOB backend_SRC "./backends/*.cpp")

set(SOURCES

    ${imgui_SRC}
    ${backend_SRC}
    ${GLAD_DIR}/glad.c
    ${src_SRC}

)

include_directories(
    ${IMGUI_DIR}
    ${BACKEND_DIR}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wformat")

if(UNIX)
    message(STATUS "UNIX")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW3 REQUIRED glfw3)
    find_package(OpenGL REQUIRED)
    include_directories(${GLFW3_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
    set(LINUX_GL_LIBS -lGL)
    set(LIBS ${LIBS} ${GLFW3_LIBRARIES} ${OPENGL_LIBRARIES} ${LINUX_GL_LIBS})
endif()

add_compile_options(-std=c++11 -g -Wall -Wformat)

add_executable(${EXE} ${SOURCES})

target_link_libraries(${EXE} ${LIBS} glfw )