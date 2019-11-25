cmake_minimum_required(VERSION 3.0.0)

project(peony-qt-share VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Concurrent REQUIRED)
find_package(PkgConfig)

pkg_search_module(PEONY_QT REQUIRED peony-qt)
message(${PEONY_QT_INCLUDE_DIRS})
message(${PEONY_QT_LIBRARIES})

include_directories(${PEONY_QT_INCLUDE_DIRS})

aux_source_directory(. SRC_FILES)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Concurrent ${PEONY_QT_LIBRARIES})

install(TARGETS peony-qt-share DESTINATION /usr/lib/peony-qt-extensions)
