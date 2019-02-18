cmake_minimum_required (VERSION 3.8)

project(GameEngine)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo")

set(SRC ${CMAKE_SOURCE_DIR}/src)
file(GLOB CPP_FILES ${SRC}/*.cpp)
file(GLOB HPP_FILES ${SRC}/*.h)
file(GLOB SHADER_FILES ${SRC}/Shaders/*.glsl)

set(RESOURCES ${CMAKE_SOURCE_DIR}/resources)

set(LIB ${CMAKE_SOURCE_DIR}/lib)

if(NOT SDL2_DIR)
	set(SDL2_DIR "" CACHE PATH "SDL2 Directory")
endif()
if(NOT glbinding_DIR)
	set(glbinding_DIR "" CACHE PATH "glbinding Directory")
endif()
if(NOT libjpeg-turbo_DIR)
	set(libjpeg-turbo_DIR "" CACHE PATH "glbinding Directory")
endif()

find_package(opengl REQUIRED)
find_package(glbinding REQUIRED)
find_package(SDL2 REQUIRED)
find_package(libjpeg-turbo REQUIRED)
find_package(PNG REQUIRED)
find_package(glm REQUIRED)
find_package(Assimp REQUIRED)

# Add source to this project's executable.
add_executable (GameEngine ${CPP_FILES} ${HPP_FILES} ${SHADER_FILES})
target_link_libraries(GameEngine glbinding::glbinding ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${libjpeg-turbo_LIBRARIES} ${PNG_LIBRARIES} ${ASSIMP_LIBRARIES})
target_include_directories(GameEngine PUBLIC ${LIB} ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${libjpeg-turbo_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR})

source_group("Shaders" files ${SHADER_FILES})
source_group("Source Files" files ${CPP_FILES})
source_group("Header Files" files ${HPP_FILES})