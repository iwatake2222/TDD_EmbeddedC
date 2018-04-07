file(GLOB SOURCES "./*.c" "./*.cpp")
add_library(Mock STATIC ${SOURCES})
target_include_directories(Mock PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(Mock gtest_main)
target_link_libraries(Mock gtest)
target_link_libraries(Mock gmock)