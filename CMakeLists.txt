cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Box2D physics library ####
add_subdirectory("lib/b2d/Box2D")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Maths interface library ####
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

#### Tile loader lib ####
file(GLOB_RECURSE SOURCE_FILES 
	lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" PUBLIC ${SFML_INCS})
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

#### Entity component model lib ####
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" PUBLIC ${SFML_INCS})
target_link_libraries(lib_ecm PRIVATE lib_maths sfml-graphics)

#### Copy res(ource) folder ####
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
	-E copy_directory
		"${PROJECT_SOURCE_DIR}/res"
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

#### Practical 1 - Pong ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)
set_target_properties(PRACTICAL_1 PROPERTIES 
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_1 copy_resources)

#### Practical 2 - Space Invaders ####
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(PRACTICAL_2_INVADERS ${SOURCES})
target_include_directories(PRACTICAL_2_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_2_INVADERS sfml-graphics)
set_target_properties(PRACTICAL_2_INVADERS PROPERTIES 
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_2_INVADERS copy_resources)

#### Practical 3 - Tile Engine####
file(GLOB_RECURSE SOURCES practical_3/*.cpp practical_3/*.h)
add_executable(PRACTICAL_3_TILE ${SOURCES})
target_include_directories(PRACTICAL_3_TILE SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_3_TILE lib_tile_level_loader sfml-graphics)
set_target_properties(PRACTICAL_3_TILE PROPERTIES 
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_3_TILE copy_resources)

#### Practical 4 - PacMan####
file(GLOB_RECURSE SOURCES practical_4/*.cpp practical_4/*.h)
add_executable(PRACTICAL_4_PACMAN ${SOURCES})
target_include_directories(PRACTICAL_4_PACMAN SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_4_PACMAN lib_tile_level_loader sfml-graphics lib_ecm)
set_target_properties(PRACTICAL_4_PACMAN PROPERTIES 
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_4_PACMAN copy_resources)

#### Physics ####
file(GLOB_RECURSE SOURCES practical_5/*.cpp practical_5/*.h)
add_executable(PRACTICAL_5_PHYSICS ${SOURCES})
target_include_directories(PRACTICAL_5_PHYSICS SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_5_PHYSICS)