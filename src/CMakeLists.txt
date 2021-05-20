# CMakeList.txt : CMake project for MemoryMatchGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("MemoryMatchGame")

# Add source to this project's executable.
add_executable (MemoryMatchGame "MatchGame.cpp" "Card.h" "Card.cpp" "Game.h" "Game.cpp" "Image.h"   "Image.cpp" "Sound.h" "Sound.cpp")
target_include_directories(MemoryMatchGame PUBLIC "D:\\C\\Cplus\\MemoryMatchGame\\nana\\include")
add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
add_definitions(-DNANA_ENABLE_AUDIO)
target_link_directories(MemoryMatchGame PUBLIC "D:\\C\\Cplus\\MemoryMatchGame\\nana\\build\\bin")
target_link_libraries(MemoryMatchGame "nana_v142_Release_x64")
# TODO: Add tests and install targets if needed.
