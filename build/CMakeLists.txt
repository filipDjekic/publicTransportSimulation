cmake_minimum_required(VERSION 3.10)

project(Izmir)

set(CMAKE_CXX_STANDARD 14)

set(IZMIR_SOURCE_FILES
    ../src/main.cpp
    ../src/stanica/stanica.cpp
    ../src/stanica/nadzemna/nadzemna.cpp
    ../src/stanica/podzemna/podzemna.cpp
    ../src/putnik/putnik.cpp
    ../src/ulica/ulica.cpp
    ../src/prevoz/prevoz.cpp
    ../src/prevoz/samousluzno/samousluzno.cpp
    ../src/prevoz/imaVozaca/imaVozaca.cpp
    ../src/prevoz/imaVozaca/veliko/veliko.cpp
    ../src/prevoz/imaVozaca/malo/malo.cpp
    ../src/ruta/ruta.cpp
)

add_executable(izmir ${IZMIR_SOURCE_FILES})