file(GLOB SOURCES "./*.c" "./*.cpp")

add_executable(project1 ${SOURCES})
target_include_directories(project1 PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(project1 OS)
