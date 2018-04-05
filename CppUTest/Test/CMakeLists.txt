# Memo: It seems unable to use sub modules as library(.so, .a) in CppUTest
file(GLOB SOURCES 
	"./*.c" "./*.cpp"
	"Mock/*.c" "Mock/*.cpp"
	"Util/*.c" "Util/*.cpp"
	"LedDriver/*.c" "LedDriver/*.cpp"
	"HomeAutomation/*.c" "HomeAutomation/*.cpp"
	"IO/*.c" "IO/*.cpp"
)

add_executable(project1 ${SOURCES})
target_include_directories(project1 PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(project1 Src)
target_link_libraries(project1 Mock)

add_subdirectory(External/cpputest)
target_link_libraries(project1 CppUTest)
target_link_libraries(project1 CppUTestExt)

add_test(project1_test  ${EXECUTABLE_OUTPUT_PATH}/project1)
