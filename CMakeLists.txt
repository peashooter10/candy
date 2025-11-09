cmake_minimum_required(VERSION 4.0)
project(Candy)

# Setează standardul C++ folosit
set(CMAKE_CXX_STANDARD 17)

# Adaugă folderul include la calea de căutare pentru fișierele header (.h)
include_directories(include)

# Căutăm toate fișierele sursă (.cpp) din folderul src
file(GLOB SOURCES "src/*.cpp")

# Creează executabilul "Candy" folosind fișierele sursă
add_executable(Candy ${SOURCES})

