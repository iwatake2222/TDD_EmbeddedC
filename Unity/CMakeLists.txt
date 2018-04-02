project("Project1" C) 
cmake_minimum_required(VERSION 3.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
message("Binary will be created in " ${EXECUTABLE_OUTPUT_PATH})

set(TARGET_GROUP production CACHE STRING "What Should I Build?")

add_subdirectory(Src)
add_subdirectory(External)

if(TARGET_GROUP STREQUAL production)
	message("production")
elseif(TARGET_GROUP STREQUAL test)
	message("test")
	include(CTest)
	add_subdirectory(test) 
else() 
	message(FATAL_ERROR "I don't know the TARGET_GROUP you gave me!")
endif()


set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_C_FLAGS_RELEASE "-O2 -s")
