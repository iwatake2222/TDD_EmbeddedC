file(GLOB SOURCES "./*.c" "./*.cpp")
add_library(LedDriver STATIC ${SOURCES})
target_include_directories(LedDriver PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)
