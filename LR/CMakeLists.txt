cmake_minimum_required (VERSION 2.6)
project (lr)
set(SRCS
    ./Src/lr.cpp


    ./Src/Plan.cpp
    ./Src/Scene.cpp
    ./Src/Source.cpp
    ./Src/Image.cpp
    ./Src/Camera.cpp

    ./Src/materiel/Couleur.cpp
    ./Src/materiel/Materiau.cpp

    ./Src/objets/Objet.cpp
    ./Src/objets/Sphere.cpp
    ./Src/objets/Rayon.cpp

    ./Src/infra/Vecteur.cpp
    ./Src/infra/Point.cpp
    ./Src/infra/Intensite.cpp
    ./Src/infra/Intersection.cpp
    )
    
set(HEADERS
    ./Src/Plan.hpp
    ./Src/Scene.hpp
    ./Src/Source.hpp
    ./Src/Image.hpp
    ./Src/Camera.hpp
    
    ./Src/materiel/Couleur.hpp
    ./Src/materiel/Materiau.hpp

    ./Src/objets/Objet.hpp
    ./Src/objets/Sphere.hpp
    ./Src/objets/Rayon.hpp

    ./Src/infra/Vecteur.hpp
    ./Src/infra/Point.hpp
    ./Src/infra/Intensite.hpp
    ./Src/infra/Intersection.hpp
    )

add_definitions(-std=c++11)

add_executable(lr ${SRCS} ${HEADERS})
