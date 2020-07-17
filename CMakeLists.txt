cmake_minimum_required(VERSION 3.15)

project(Ongine)

# Libraries
add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/imgui)

# GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library Linking
target_link_libraries(imgui glfw glad)
target_include_directories(imgui PRIVATE deps/glfw/include)
target_include_directories(imgui PRIVATE deps/glad/include)

# Project Stuff
add_subdirectory(Ongine)
target_link_libraries(Ongine glfw glad glm imgui spdlog)
target_include_directories(Ongine PRIVATE deps/glfw/include)
target_include_directories(Ongine PRIVATE deps/glad/include)
target_include_directories(Ongine PRIVATE deps/spdlog/include)
target_include_directories(Ongine PRIVATE deps/stb)
target_include_directories(Ongine PRIVATE deps/glm)
target_include_directories(Ongine PRIVATE deps/imgui)
set_target_properties( Ongine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(Sandbox)
target_link_libraries(Sandbox glfw glad glm spdlog imgui Ongine)
target_include_directories(Sandbox PRIVATE deps/glfw/include)
target_include_directories(Sandbox PRIVATE deps/glad/include)
target_include_directories(Sandbox PRIVATE deps/spdlog/include)
target_include_directories(Sandbox PRIVATE deps/stb)
target_include_directories(Sandbox PRIVATE deps/glm)
target_include_directories(Sandbox PRIVATE Ongine/src)
target_include_directories(Sandbox PRIVATE deps/imgui)
set_target_properties( Sandbox
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)