cmake_minimum_required(VERSION 3.15)
project(QtPrintDocument)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Gui PrintSupport REQUIRED)

add_executable(QtPrintDocument main.cpp text.cpp text.h block.cpp block.h stackable.cpp stackable.h table.cpp table.h base.h document.cpp document.h wrap.cpp wrap.h)
target_link_libraries(QtPrintDocument Qt5::Core Qt5::Gui Qt5::PrintSupport)