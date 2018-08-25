# CMakeList.txt : CMake project for GameEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# TODO: Add tests and install targets if needed.
#set(glbinding_DIR "D:/documents/Github Projects/vcpkg/installed/x86-windows/share/glbinding")
#set(SDL_INCLUDE_DIR "D:/documents/Github Projects/SDL2-2.0.8/include")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo")
if(NOT SDL2_DIR)
	set(SDL2_DIR "" CACHE PATH "SDL2 Directory")
endif()
if(NOT glbinding_DIR)
	set(glbinding_DIR "" CACHE PATH "glbinding Directory")
endif()

find_package(glbinding REQUIRED)
find_package(SDL2 REQUIRED)

# Add source to this project's executable.
add_executable (GameEngine WIN32 "Shape.cpp" "Shape.h" "Screen.h" "Screen.cpp" "Image.cpp" "Image.h" "GameEngine.cpp" "GameEngine.h")
file(COPY "stim-it.tga" DESTINATION "Debug")
file(COPY "stim-it.bmp" DESTINATION "Debug")
file(COPY "stim-math.tga" DESTINATION "Debug")
file(COPY "stim-math.bmp" DESTINATION "Debug")
target_link_libraries(GameEngine glbinding::glbinding)
target_include_directories(GameEngine PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(GameEngine ${SDL2_LIBRARIES})