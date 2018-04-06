file(GLOB SOURCES "./Src/*.c" "./Src/*.cpp")
add_library(OS STATIC ${SOURCES})
target_include_directories(OS PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Include ${PROJECT_SOURCE_DIR}/Include)


