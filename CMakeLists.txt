cmake_minimum_required(VERSION 2.8)

project (clade_wars)

add_definitions(-std=c89 -Wall -Werror)

file(GLOB sources . src/*)
add_executable(run_tests ${sources})

install(TARGETS run_tests DESTINATION bin)
