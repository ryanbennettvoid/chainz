
cmake_minimum_required( VERSION 3.12 )

set(CMAKE_BUILD_TYPE Debug)

project( chainztest )
add_executable( 
  chainztest 
  ./test/general.c
  ./src/block.c
)

target_include_directories( 
  chainztest PUBLIC 
  ./include
)

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