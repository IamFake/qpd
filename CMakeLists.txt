cmake_minimum_required(VERSION 3.9)
project(QtPrintDocument)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

add_executable(QtPrintDocument main.cpp text.cpp text.h block.cpp block.h stackable.cpp stackable.h table.cpp table.h base.h document.cpp document.h wrap.cpp wrap.h)
target_link_libraries(QtPrintDocument Qt5::Core Qt5::Gui Qt5::PrintSupport)