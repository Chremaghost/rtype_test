cmake_minimum_required(VERSION 3.15)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "rtype-client")
set(SERVER_BINARY "rtype-server")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_MSC_VER=1911")

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
    GIT_TAG 2.5.1
)

# Check that dependencies are found
find_package(Boost REQUIRED COMPONENTS asio system filesystem thread)
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -static-libgcc -static-libstdc++")

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

# Create client executable
add_executable(${CLIENT_BINARY} ${CLIENT_SOURCES})

# Link libraries for client
if (WIN32)
target_link_libraries(${CLIENT_BINARY}
    PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    -lFLAC
    -logg
    -lvorbis
    -lvorbisfile
    -lfreetype
    -Wl,--enable-auto-import
    Boost::asio
    Boost::system
    Boost::filesystem
    Boost::thread
)
elseif (UNIX)
target_link_libraries(${CLIENT_BINARY}
    PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    -lFLAC
    -logg
    -lvorbis
    -lvorbisfile
    -lfreetype
    -Wl,--enable-auto-import
    Boost::asio
    Boost::system
    Boost::filesystem
    Boost::thread
)
endif()

# Create server executable
add_executable(${SERVER_BINARY} ${SERVER_SOURCES})

# Link libraries for server
target_link_libraries(${SERVER_BINARY}
    PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    -lFLAC
    -logg
    -lvorbis
    -lvorbisfile
    -lfreetype
    Boost::asio
    Boost::system
    Boost::filesystem
    Boost::thread
)

# Include directories for client
target_include_directories(${CLIENT_BINARY} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ECS/
    ${SFML_INCLUDE_DIR}  # Include path for SFML
)

# Include directories for server
target_include_directories(${SERVER_BINARY} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Game_Play/
    ${SFML_INCLUDE_DIR}  # Include path for SFML
)

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
