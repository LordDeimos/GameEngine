cmake_minimum_required (VERSION 3.8)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo")

set(SRC ${CMAKE_SOURCE_DIR}/src)
file(GLOB CPP_FILES ${SRC}/*.cpp)
file(GLOB HPP_FILES ${SRC}/*.h)

set(RESOURCES ${CMAKE_SOURCE_DIR}/resources)

if(NOT SDL2_DIR)
	set(SDL2_DIR "" CACHE PATH "SDL2 Directory")
endif()
if(NOT glbinding_DIR)
	set(glbinding_DIR "" CACHE PATH "glbinding Directory")
endif()

find_package(glbinding REQUIRED)
find_package(SDL2 REQUIRED)

# Add source to this project's executable.
add_executable (GameEngine ${CPP_FILES} ${HPP_FILES})
target_link_libraries(GameEngine glbinding::glbinding)
target_include_directories(GameEngine PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(GameEngine ${SDL2_LIBRARIES})