project(OSM)


#
# CMake
#

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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
    ${GTEST_INCLUDE_DIRS}
    ${DIR_OSMPBF}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebEngineWidgets_INCLUDE_DIRS}
    ${DIR_OSMPBF}/osmpbf/include)

link_directories(
    ${DIR_OSMPBF}/build/osmpbf)

#
# Compiler
#

SET(GCC_COMPILE_FLAGS "-Wall -Wextra -pedantic -fPIC -O3")
#SET(GCC_COMPILE_FLAGS "-Wall -Wextra -pedantic -fPIC -O0")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

set(CMAKE_BUILD_TYPE RELEASE)

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
    code/include/types.hpp
    code/include/structures/AdjacencyArray.hpp
    code/include/structures/Primitives.hpp
    code/include/io/osmpbfReader.hpp
    code/include/gui/UIBridge.hpp
    code/include/alg/RouteSearch.hpp
    code/include/NonCopyable.hpp
    code/include/NonMoveable.hpp
    code/include/io/MapData.hpp
    code/include/structures/Grid.hpp
    code/include/io/CMD.hpp
    code/include/util/Geo.hpp)

set(GUI_INCLUDES
    code/include/gui/Window.hpp
    code/include/gui/UIMap.hpp
    code/include/gui/Panel.hpp
    code/include/gui/UIGraph.hpp
    code/include/gui/WebPage.hpp)


#
# Sources
#

set(SOURCES
    code/source/structures/AdjacencyArray.cpp
    code/source/io/osmpbfReader.cpp
    code/source/io/MapData.cpp
    code/source/structures/Grid.cpp
    code/source/alg/RouteSearch.cpp
    code/source/util/Geo.cpp
    code/source/gui/WebPage.cpp)

set(GUI_SOURCES
    code/source/gui/Window.cpp
    code/source/gui/Panel.cpp
    code/source/gui/UIMap.cpp
    code/source/gui/UIBridge.cpp
    code/source/gui/UIGraph.cpp)


#
# All files
#

set(GUI_FILES ${GUI_INCLUDES} ${GUI_SOURCES})
set(FILES ${INCLUDES} ${SOURCES} ${GUI_FILES})


#
# Tests
#

set(TEST_SOURCES
    code/test/structures/test_AdjacencyArray.cpp
    code/test/structures/test_dijkstra.cpp
    code/test/structures/test_Grid.cpp)

set(TEST_FILES
    ${FILES}
    ${TEST_SOURCES})


#
# Builds
#

# Main
add_executable(${PROJECT_NAME} ${FILES} ${RESOURCES} ${DIR_APP}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

## Test
add_executable(${PROJECT_NAME}_Test ${TEST_FILES} ${DIR_TEST}/test.cpp)
target_link_libraries(${PROJECT_NAME}_Test ${TEST_LIBRARIES})
