file(GLOB SOURCES "./*.c" "./*.cpp")
add_library(IO STATIC ${SOURCES})
target_include_directories(IO PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)
