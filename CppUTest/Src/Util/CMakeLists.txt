file(GLOB SOURCES "./*.c" "./*.cpp")
add_library(Util STATIC ${SOURCES})
target_include_directories(Util PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)
