file(GLOB SOURCES 
	"./*.c" "./*.cpp"
	"Mock/*.c" "Mock/*.cpp"
	"LedDriver/*.c" "LedDriver/*.cpp"
)

add_executable(project1 ${SOURCES})

target_link_libraries(project1)
target_include_directories(project1 PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(project1 Src)

add_subdirectory(External)
target_link_libraries(project1 Unity)

add_test(project1_test  ${EXECUTABLE_OUTPUT_PATH}/project1)
