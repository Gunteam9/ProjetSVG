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
add_executable( serveur serveur/moteur serveur/window serveur/message serveur/dataparser
                cbor11/cbor11

                exceptions/udpRuntimeException exceptions/udpBindsException exceptions/udpReceiveException
                exceptions/erreurException
                )

add_executable(testsServeur serveur/maintest serveur/message cbor11/cbor11 serveur/dataparser serveur/serveur


        exceptions/udpRuntimeException exceptions/udpBindsException exceptions/udpReceiveException
        exceptions/erreurException
        )

#On crée l'executable pour le client
add_executable(client client/client client/launcher client/functions

        exceptions/udpAdresseConvertionException exceptions/udpRuntimeException exceptions/udpSendingException

        cbor11/cbor11
        )

add_executable(testClient2 testClientServeur/client cbor11/cbor11

        exceptions/udpAdresseConvertionException exceptions/udpRuntimeException
        exceptions/udpSendingException exceptions/udpConnectionException exceptions/udpBindsException

        )

add_executable(testServeur2 testClientServeur/server cbor11/cbor11 serveur/dataparser serveur/message

        exceptions/udpRuntimeException exceptions/udpBindsException exceptions/udpReceiveException

        exceptions/erreurException

        )

#On lies les librairies pour le serveur
target_link_libraries(serveur ${GTK3_LIBRARIES} ${RSVG_LIBRARIES} ${CAIRO_LIBRARIES} ${TXML_LIBRARIES})
