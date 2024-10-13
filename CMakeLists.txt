cmake_minimum_required(VERSION 3.15)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # or 14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "rtype-client")
set(SERVER_BINARY "rtype-server")

# Integration of CPM
include(cmake/CPM.cmake)

# Adding dependencies with CPM
CPMAddPackage(
    NAME Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.83.0
)

CPMAddPackage(
    NAME SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1  # or a specific version for SFML 3
)

# Check that dependencies are found
find_package(Boost REQUIRED COMPONENTS asio system filesystem thread)
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

# Set compiler flags (consider simplifying)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

# Network source files
set(NETWORK_SOURCES
    src/client/ClientNetworkManager.cpp
    src/server/ServerNetworkManager.cpp
)

# ECS source files
file(GLOB ECS_SOURCES
    src/engine/ECS/*.cpp
    src/engine/input/*.cpp
    src/engine/physics/*.cpp
    src/engine/rendering/*.cpp
    src/engine/sound/*.cpp
    src/engine/gameplay/*.cpp
    src/engine/factory/*.cpp
    src/engine/spawn/*.cpp
    src/engine/utils/*.cpp
    src/engine/combat/*.cpp
)

if(NOT ECS_SOURCES)
    message(FATAL_ERROR "No source files found in src/engine/ECS/")
endif()

# Client source files
set(CLIENT_SOURCES ${NETWORK_SOURCES} ${ECS_SOURCES} src/main_client.cpp)

# Server source files
set(SERVER_SOURCES ${NETWORK_SOURCES} ${ECS_SOURCES} src/main_server.cpp)

find_package(Threads REQUIRED)

# Create client and server executables
add_executable(${CLIENT_BINARY} ${CLIENT_SOURCES})
add_executable(${SERVER_BINARY} ${SERVER_SOURCES})

# Link libraries
target_link_libraries(${CLIENT_BINARY}
    PRIVATE Threads::Threads
    sfml-graphics sfml-window sfml-system sfml-audio
    Boost::asio Boost::system Boost::filesystem Boost::thread
)

target_link_libraries(${SERVER_BINARY}
    PRIVATE Threads::Threads
    sfml-graphics sfml-window sfml-system sfml-audio
    Boost::asio Boost::system Boost::filesystem Boost::thread
)

# Include directories
target_include_directories(${CLIENT_BINARY} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_include_directories(${SERVER_BINARY} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)


# Platform-specific handling for custom commands
if (WIN32)
    add_custom_command(TARGET ${CLIENT_BINARY} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${CLIENT_BINARY}>/assets
    )
elseif (UNIX)
    add_custom_command(TARGET ${CLIENT_BINARY} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${CLIENT_BINARY}>/assets
    )
endif()
