
cmake_minimum_required( VERSION 3.12 )

set(CMAKE_BUILD_TYPE Debug)

project( chainz )
add_executable( 
  chainz 
  ./src/main.c
  ./src/block.c
)

target_include_directories( 
  chainz PUBLIC 
  ./include
)