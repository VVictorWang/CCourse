cmake_minimum_required(VERSION 3.8)
project(course)

set(CMAKE_C_STANDARD 99)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
add_definitions(${GTK2_CFLAGS_OTHER})

set(SOURCE_FILES main.c head.h gui.c guiHelper.c  initInfo.c guiGrade.c guiClass.c informationIn.c testInfo.c changeInfo.c deleteInfo.c guiStudent.c saveInfo.c dataHepler.c guiGradeInfoSearch.c searchInfo.c guiClassInfoSearch.c guiStudentInfoSearch.c guiStatistic.c statistics.c)
add_executable(course ${SOURCE_FILES})
target_link_libraries(course ${GTK2_LIBRARIES})