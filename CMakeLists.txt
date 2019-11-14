project(OSM)


#
# CMake
#

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)

set(BIN_PATH "bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_PATH}")


#
# Paths
#

set(DIR_CODE code)
set(DIR_APP ${DIR_CODE}/apps)
set(DIR_TEST ${DIR_CODE}/test)
set(DIR_INCLUDE ${DIR_CODE}/include)
set(DIR_OSMPBF osmpbf)

find_package(Qt5 COMPONENTS Widgets WebEngineWidgets REQUIRED)
find_package(Protobuf REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(
    ${DIR_INCLUDE}
    ${DIR_OSMPBF}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebEngineWidgets_INCLUDE_DIRS}
    ${DIR_OSMPBF}/osmpbf/include)

link_directories(
    ${DIR_OSMPBF}/build/osmpbf)

#
# Compiler
#

SET(GCC_COMPILE_FLAGS "-Wall -Wextra -pedantic -O3 -fPIC")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")


#
# Libraries
#

set(QT_LIBS
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebEngineWidgets_LIBRARIES})

set(LIBRARIES
    -lpthread
    -losmpbf
    -lz
    ${QT_LIBS}
    ${PROTOBUF_LIBRARIES})

set(TEST_LIBRARIES
    -lgtest
    -lgtest_main
    ${LIBRARIES})


#
# Conan
#

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


#
# Resources
#

set(RESOURCES
    resources.qrc)

#
# Includes
#

set(INCLUDES
    code/include/prototypes.hpp
    code/include/structures/AdjacencyArray.hpp
    code/include/structures/Primitives.hpp
    code/include/io/osmpbfReader.hpp
    code/include/gui/UIBridge.hpp
    code/include/gui/mapTypes.hpp
    code/include/alg/Dijkstra.hpp
    code/include/NonCopyable.hpp
    code/include/NonMoveable.hpp
    code/include/structures/Graph.hpp)

set(GUI_INCLUDES
    code/include/gui/Window.hpp
    code/include/gui/UIMap.hpp
    code/include/gui/Panel.hpp)


#
# Sources
#

set(SOURCES
    code/source/structures/AdjacencyArray.cpp
    code/source/io/osmpbfReader.cpp
    code/source/structures/Graph.cpp)

set(GUI_SOURCES
    code/source/gui/Window.cpp
    code/source/gui/Panel.cpp
    code/source/gui/UIMap.cpp
    code/source/gui/UIBridge.cpp)


#
# All files
#

set(GUI_FILES ${GUI_INCLUDES} ${GUI_SOURCES})
set(FILES ${INCLUDES} ${SOURCES} ${GUI_FILES})


#
# Tests
#

set(TEST_SOURCES
    )

set(TEST_FILES
    ${FILES}
    ${TEST_SOURCES})


#
# Builds
#

# Task 2
add_executable(${PROJECT_NAME}_Task_2 ${FILES} ${DIR_APP}/task2.cpp)
target_link_libraries(${PROJECT_NAME}_Task_2 ${LIBRARIES})

# Task 3
add_executable(${PROJECT_NAME}_Task_3 ${FILES} ${DIR_APP}/task3.cpp)
target_link_libraries(${PROJECT_NAME}_Task_3 ${LIBRARIES})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Task 4
add_executable(${PROJECT_NAME}_Task_4 ${FILES} ${RESOURCES} ${DIR_APP}/task4.cpp)
target_link_libraries(${PROJECT_NAME}_Task_4 ${LIBRARIES})

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

# Task 5
add_executable(${PROJECT_NAME}_Task_5 ${FILES} ${DIR_APP}/task5.cpp)
target_link_libraries(${PROJECT_NAME}_Task_5 ${LIBRARIES})

# Main
add_executable(${PROJECT_NAME} ${FILES} ${GUI_FILES} ${DIR_APP}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} ${QT_LIBS})

# Test
add_executable(${PROJECT_NAME}_Test ${TEST_FILES} ${DIR_TEST}/test.cpp)
target_link_libraries(${PROJECT_NAME}_Test ${TEST_LIBRARIES})
