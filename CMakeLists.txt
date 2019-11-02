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

find_package(Qt5 COMPONENTS Core Gui WebKitWidgets WebEngineWidgets Widgets REQUIRED)
find_package(Protobuf REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(
    ${DIR_INCLUDE}
    ${DIR_OSMPBF}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5WebEngine_INCLUDE_DIRS}
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
    ${Qt5WebEngineWidgets_LIBRARIES}
    ${Qt5WebKitWidgets_LIBRARIES})

set(LIBRARIES
    -lpthread
    -losmpbf
    -lz
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
# Includes
#

set(INCLUDES
    code/include/prototypes.hpp
    code/include/structures/AdjacencyArray.hpp
    code/include/structures/Primitives.hpp
    code/include/io/osmpbfReader.hpp code/include/gui/Window.hpp code/include/gui/UIMap.hpp code/include/gui/Panel.hpp)


#
# Sources
#

set(SOURCES
    code/source/structures/AdjacencyArray.cpp
    code/source/structures/Primitives.cpp
    code/source/io/osmpbfReader.cpp code/source/gui/Window.cpp code/source/gui/Panel.cpp)


#
# All files
#

set(FILES ${INCLUDES} ${SOURCES})


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

# Task 4
add_executable(${PROJECT_NAME}_Task_4 ${FILES} ${DIR_APP}/task4.cpp)
target_link_libraries(${PROJECT_NAME}_Task_4 ${LIBRARIES} ${QT_LIBS})

# Task 5
add_executable(${PROJECT_NAME}_Task_5 ${FILES} ${DIR_APP}/task5.cpp)
target_link_libraries(${PROJECT_NAME}_Task_5 ${LIBRARIES} ${QT_LIBS})

# Main
add_executable(${PROJECT_NAME} ${FILES} ${DIR_APP}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Test
add_executable(${PROJECT_NAME}_Test ${TEST_FILES} ${DIR_TEST}/test.cpp)
target_link_libraries(${PROJECT_NAME}_Test ${TEST_LIBRARIES})
