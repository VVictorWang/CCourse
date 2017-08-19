cmake_minimum_required(VERSION 3.8)
project(course)

set(CMAKE_C_STANDARD 99)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
add_definitions(${GTK2_CFLAGS_OTHER})

set(SOURCE_FILES src/main.c src/head.h src/gui/guiInterface.c src/gui/guiHelper.c src/initInfo.c src/gui/guiGrade.c
        src/gui/guiClass.c src/informationIn.c src/testInfo.c src/changeInfo.c src/deleteInfo.c src/gui/guiStudent.c
        src/saveInfo.c src/dataHepler.c src/gui/guiGradeInfoSearch.c src/searchInfo.c src/gui/guiClassInfoSearch.c
        src/gui/guiStudentInfoSearch.c src/gui/guiStatistic.c src/statisticsInfo.c)
add_executable(course ${SOURCE_FILES})
target_link_libraries(course ${GTK2_LIBRARIES})