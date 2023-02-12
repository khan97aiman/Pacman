set(PROJECT_NAME Pacman)

################################################################################
# Source groups
################################################################################

set(Source_Files
    "Blinky.cpp"
    "Candy.cpp"
    "Game.cpp"
    "Inky.cpp"
    "Button.cpp"
    "Cell.cpp"
    "Character.cpp"
    "Clyde.cpp"
    "excerptScreen.cpp"
    "Fruit.cpp"
    "GameLevelScreen.cpp"
    "GameObject.cpp"
    "FoodItem.cpp"
    "gameOverScreen.cpp"
    "gameScreen.cpp"
    "Ghost.cpp"
    "Level.cpp"
    "Lollipop.cpp"
    "LTexture.cpp"
    "menuScreen.cpp"
    "pauseScreen.cpp"
    "Pinky.cpp"
    "quitScreen.cpp"
    "word.cpp"
    "Screen.cpp"
    "splashScreen.cpp"
    "Pacman.cpp"
    "Main.cpp"
)

source_group("Source Files" FILES ${Source_Files})

set(Header_Files
    "FoodItem.h"
    "GlobalFunctions.h"
    "word.h"
    "Blinky.h"
    "Button.h"
    "Candy.h"
    "Cell.h"
    "Character.h"
    "Clyde.h"
    "excerptScreen.h"
    "Fruit.h"
    "GameLevelScreen.h"
    "GameObject.h"
    "Game.h"
    "gameOverScreen.h"
    "gameScreen.h"
    "Ghost.h"
    "Inky.h"
    "Level.h"
    "Lollipop.h"
    "LTexture.h"
    "menuScreen.h"
    "pauseScreen.h"
    "Pinky.h"
    "quitScreen.h"
    "Pacman.h"
    "Point.h"
    "Screen.h"
    "splashScreen.h"
)

source_group("Header Files" FILES ${Header_Files})

set(ALL_FILES
    ${Source_Files}
    ${Header_Files}
)

if(WIN32) 
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Middleware/SDL2") 
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Middleware/SDL2_Image") 
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Middleware/SDL2_Mixer") 

endif() 

#Import the SDL2 library 
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(".")
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})


################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME}  ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Pacman)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

################################################################################
# Compile definitions
################################################################################
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "UNICODE;"
        "_UNICODE" 
        "WIN32_LEAN_AND_MEAN"
        "_WINSOCKAPI_"   
        "_WINSOCK2API_"
        "_WINSOCK_DEPRECATED_NO_WARNINGS"
    )
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <vector>
    <map>
    <stack>
    <string>
    <list>
    <thread>
    <atomic>
    <functional>
    <iostream>
    <set>
)
 

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /Oi;
            /Gy
        >
        /permissive-;
        /std:c++latest;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
    )
endif()

################################################################################
# Dependencies
################################################################################
if(MSVC)
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC  "Winmm.lib")
endif()

#target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

