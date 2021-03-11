cmake_minimum_required (VERSION 2.6)
project (lr)
set(SRCS
    ./Src/lr.cpp
    ./Src/Objet.cpp
    ./Src/Sphere.cpp
    ./Src/Materiau.cpp
    ./Src/Couleur.cpp
    ./Src/Plan.cpp
    ./Src/Scene.cpp
    ./Src/Point.cpp
    ./Src/Vecteur.cpp
    ./Src/Intensite.cpp
    ./Src/Source.cpp
    ./Src/Image.cpp
    ./Src/Camera.cpp
    ./Src/Rayon.cpp
    ./Src/Intersection.cpp
    )
    
set(HEADERS
    ./Src/Objet.hpp
    ./Src/Sphere.hpp
    ./Src/Materiau.hpp
    ./Src/Couleur.hpp
    ./Src/Plan.hpp
    ./Src/Scene.hpp
    ./Src/Point.hpp
    ./Src/Vecteur.hpp
    ./Src/Intensite.hpp
    ./Src/Source.hpp
    ./Src/Image.hpp
    ./Src/Camera.hpp
    ./Src/Rayon.hpp
    ./Src/Intersection.hpp
    )

add_definitions(-std=c++11)

add_executable(lr ${SRCS} ${HEADERS})
