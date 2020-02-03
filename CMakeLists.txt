cmake_minimum_required(VERSION 3.15)
project(corbeau_neonakis_toularhmine_trimoulet)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)


pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(TXML REQUIRED tinyxml2)
pkg_check_modules(RSVG REQUIRED librsvg-2.0)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${TXML_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS} ${RSVG_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS} ${RSVG_LIBRARY_DIRS} ${CAIRO_LIBRARY_DIRS} ${TXML_LIBRARY_DIRS})

add_executable(corbeau_neonakis_toularhmine_trimoulet moteur.cpp)

target_link_libraries(corbeau_neonakis_toularhmine_trimoulet ${GTK3_LIBRARIES} ${RSVG_LIBRARIES} ${CAIRO_LIBRARIES} ${TXML_LIBRARIES})
