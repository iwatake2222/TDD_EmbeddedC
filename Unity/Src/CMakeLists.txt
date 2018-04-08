file(GLOB SOURCES "./*.c" "./*.cpp")

if(TARGET_GROUP STREQUAL test)
	list(REMOVE_ITEM SOURCES "Main.c" "Main.cpp")
	set(MAIN_BIN_NAME Src)
	add_library(${MAIN_BIN_NAME} STATIC ${SOURCES})
	target_include_directories(${MAIN_BIN_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)
else()
	set(MAIN_BIN_NAME project1)
	add_executable(${MAIN_BIN_NAME} ${SOURCES})
	target_include_directories(${MAIN_BIN_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/Include)
endif()

add_subdirectory(LedDriver)
target_link_libraries(${MAIN_BIN_NAME} LedDriver)

add_subdirectory(HomeAutomation)
target_link_libraries(${MAIN_BIN_NAME} HomeAutomation)

add_subdirectory(Util)
target_link_libraries(${MAIN_BIN_NAME} Util)

add_subdirectory(IO)
target_link_libraries(${MAIN_BIN_NAME} IO)
