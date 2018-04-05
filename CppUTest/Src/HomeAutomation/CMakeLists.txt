file(GLOB SOURCES "./*.c" "./*.cpp")
add_library(HomeAutomation STATIC ${SOURCES})
target_include_directories(HomeAutomation PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)
