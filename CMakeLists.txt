#Version de Cmake
cmake_minimum_required(VERSION 3.15)
#Projet
project(corbeau_neonakis_toularhmine_trimoulet)

#Standard de c++
set(CMAKE_CXX_STANDARD 17)

#Outil pour trouver les packages
find_package(PkgConfig REQUIRED)

#Tous les packages utilisés
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(TXML REQUIRED tinyxml2)
pkg_check_modules(RSVG REQUIRED librsvg-2.0)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

#On les inclus
include_directories(${TXML_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS} ${RSVG_INCLUDE_DIRS})

#On les lies
link_directories(${GTK3_LIBRARY_DIRS} ${RSVG_LIBRARY_DIRS} ${CAIRO_LIBRARY_DIRS} ${TXML_LIBRARY_DIRS})

#On crée l'éxectuable pour le serveur
add_executable(serveur serveur/moteur.cpp serveur/window.cpp cbor11/cbor11.cpp)

add_executable(testsServeur serveur/maintest.cpp serveur/message.cpp cbor11/cbor11.cpp serveur/dataparser.cpp exceptions/erreurException.cpp serveur/serveur.cpp serveur/serveur.hpp)

#On crée l'executable pour le client
add_executable(client client/client.cpp client/launcher.cpp client/functions.cpp exceptions/udpRuntimeException.cpp cbor11/cbor11.cpp exceptions/udpSendingException.cpp client/functions.h)

add_executable(testClient2 testClientServeur/client.cpp exceptions/udpRuntimeException.cpp exceptions/udpAdresseConvertionException.cpp exceptions/udpAdresseConvertionException.h exceptions/udpBindsException.cpp exceptions/udpBindsException.h exceptions/udpConnectionException.cpp exceptions/udpConnectionException.h exceptions/udpSendingException.cpp)

add_executable(testServeur2 testClientServeur/server.cpp exceptions/udpRuntimeException.cpp exceptions/udpBindsException.cpp exceptions/udpReceiveException.cpp)

#On lies les librairies pour le serveur
target_link_libraries(serveur ${GTK3_LIBRARIES} ${RSVG_LIBRARIES} ${CAIRO_LIBRARIES} ${TXML_LIBRARIES})
