# file(GLOB SOURCES  ./*.c)
file(GLOB_RECURSE SOURCES  ./*.c)

add_executable(project1 ${SOURCES})

target_link_libraries(project1 Src Unity)
target_include_directories(project1 PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)

add_test(project1_test  ${EXECUTABLE_OUTPUT_PATH}/project1)
