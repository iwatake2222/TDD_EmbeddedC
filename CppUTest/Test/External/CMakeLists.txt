# # Use my own CMakeLists.txt instead of that of googletest
# set(CPP_PLATFORM Gcc)
# file(GLOB SOURCES "cpputest/src/CppUTest/*.cpp")
# file(GLOB SOURCES_EXT "cpputest/src/CppUTestExt/*.cpp")
# add_library(CppUTest ${SOURCES})
# add_library(CppUTestExt ${SOURCES_EXT} cpputest/src/Platforms/${CPP_PLATFORM}/UtestPlatform.cpp)
# target_include_directories(CppUTest PUBLIC cpputest/include)
# target_include_directories(CppUTestExt PUBLIC cpputest/include)
