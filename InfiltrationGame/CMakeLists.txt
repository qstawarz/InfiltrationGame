cmake_minimum_required(VERSION 3.8)
project(DotProduct)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        #Actors
            #includes
                includes/Actors/IActor.h
                includes/Actors/Player.h
                includes/Actors/Enemy.h
            #src
                src/Actors/Player.cpp
                src/Actors/Enemy.cpp

        #Managers
            #includes
                includes/Managers/IManager.h
                includes/Managers/Game.h
                includes/Managers/DisplayManager.h
                includes/Managers/InputManager.h
                includes/Managers/UIManager.h
            #src
                src/Managers/Game.cpp
                src/Managers/DisplayManager.cpp
                src/Managers/InputManager.cpp
                src/Managers/UIManager.cpp

        #States
            #includes
            #src

        #Utils
            #includes
                includes/Utils/Vector.h
                includes/Utils/Sprite.h
                includes/Utils/Text.h
            #src
                src/Utils/Sprite.cpp
                src/Utils/Text.cpp
        )
add_executable(DotProduct ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(DotProduct ${SFML_LIBRARIES})
endif()