cmake_minimum_required(VERSION 3.5)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "rtype-client")
set(SERVER_BINARY "rtype-server")

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.86.0
)

CPMAddPackage(
    NAME SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1  # Latest stable version
)

# Compile SFML statically
set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARIES ON)

find_package(Boost REQUIRED COMPONENTS asio system filesystem thread)
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

add_compile_definitions(__USE_MINGW_ANSI_STDINC=1)

set(NETWORK_SOURCES
    src/client/ClientNetworkManager.cpp
    src/server/ServerNetworkManager.cpp
)

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

set(CLIENT_SOURCES ${NETWORK_SOURCES} ${ECS_SOURCES} src/main_client.cpp)
set(SERVER_SOURCES ${NETWORK_SOURCES} ${ECS_SOURCES} src/main_server.cpp)

find_package(Threads REQUIRED)

add_executable(${CLIENT_BINARY} ${CLIENT_SOURCES})
add_executable(${SERVER_BINARY} ${SERVER_SOURCES})

target_link_libraries(${CLIENT_BINARY}
    PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    Boost::asio
    Boost::system
    Boost::filesystem
    Boost::thread
   # -lvorbis
   # -lvorbisfile
    #-logg
    #-lFLAC
    #-lfreetype
)

target_link_libraries(${SERVER_BINARY}
    PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    Boost::asio
    Boost::system
    Boost::filesystem
    Boost::thread
    #-lFLAC
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
