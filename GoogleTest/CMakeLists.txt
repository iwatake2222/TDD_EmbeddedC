project("Project1") 
cmake_minimum_required(VERSION 3.6)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
message("Binary will be created in " ${EXECUTABLE_OUTPUT_PATH})


### Switch for unit test
set(TARGET_GROUP production CACHE STRING "What Should I Build?")


### Common source directory
add_subdirectory(Src)
add_subdirectory(External)

### Switch for unit test
if(TARGET_GROUP STREQUAL production)
	message("This build is for product")
elseif(TARGET_GROUP STREQUAL test)
	message("This build is for test")
	include(CTest)
	add_subdirectory(Test)
	add_subdirectory(Mock)
else() 
	message(FATAL_ERROR "I don't know the TARGET_GROUP you gave me!")
endif()


### Optimization settings
set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_C_FLAGS_RELEASE "-O2 -s")
# set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-Wall -g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s")
