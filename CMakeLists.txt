cmake_minimum_required(VERSION 3.8)
project(ccourse)

set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
add_definitions(${GTK2_CFLAGS_OTHER})

set(SOURCE_FILES src/main.c src/head.h src/view/guiInterface.c src/view/guiHelper.c src/model/initInfo.c src/view/guiGrade.c
        src/view/guiClass.c src/model/inputInfo.c src/model/testInfo.c src/model/changeInfo.c src/model/deleteInfo.c src/view/guiStudent.c
        src/model/saveInfo.c src/model/dataHepler.c src/view/guiGradeInfoSearch.c src/model/searchInfo.c src/view/guiClassInfoSearch.c
        src/view/guiStudentInfoSearch.c src/view/guiStatistic.c src/model/statisticsInfo.c)
add_executable(ccourse ${SOURCE_FILES})
target_link_libraries(ccourse ${GTK2_LIBRARIES})