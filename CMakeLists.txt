cmake_minimum_required(VERSION 3.8)
project(OpenGL_Game C CXX)

set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

# GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

# Warning Flags and other libs for Glad
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

# Include Paths
include_directories(src
                    vendor/glad/include/
                    vendor/glfw/include/
                    vendor/glm/
                    vendor/stb/)

# Glad
set(GLAD_SRC vendor/glad/src/glad.c
             vendor/glad/include/glad/glad.h
             vendor/glad/include/KHR/khrplatform.h)
add_library(glad STATIC ${GLAD_SRC})

# Helpers sources
set(SOURCE src/helpers/shader.hpp
                src/helpers/objloader.cpp src/helpers/objloader.hpp
                src/objects/object.hpp)

# Libraries
find_package(OpenGL REQUIRED)
set(ALL_LIBS OpenGL::GL glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES})

# Executables

add_executable(game_example src/game_example.cpp ${SOURCE})
target_link_libraries(game_example PUBLIC  ${ALL_LIBS})

######

#####


# add_definitions(-DGLFW_INCLUDE_NONE
#                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
# add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
#                                ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
#                                ${VENDORS_SOURCES})
# target_link_libraries(${PROJECT_NAME}  glfw
#                       ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
#                         )
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

