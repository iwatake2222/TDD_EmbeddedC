# Use my own CMakeLists.txt instead of that of googletest
set(CPP_PLATFORM Gcc)
file(GLOB SOURCES "cpputest/src/CppUTest/*.cpp")
file(GLOB SOURCES_EXT "cpputest/src/CppUTestExt/*.cpp")
add_library(CppUTest ${SOURCES})
add_library(CppUTestExt ${SOURCES_EXT} cpputest/src/Platforms/${CPP_PLATFORM}/UtestPlatform.cpp)
# add_library(CppUTest STATIC 
# 	cpputest/src/CppUTest/CommandLineArguments.cpp
# 	cpputest/src/CppUTest/MemoryLeakWarningPlugin.cpp
# 	cpputest/src/CppUTest/TestHarness_c.cpp
# 	cpputest/src/CppUTest/TestRegistry.cpp
# 	cpputest/src/CppUTest/CommandLineTestRunner.cpp
# 	cpputest/src/CppUTest/SimpleString.cpp
# 	cpputest/src/CppUTest/TestMemoryAllocator.cpp
# 	cpputest/src/CppUTest/TestResult.cpp
# 	cpputest/src/CppUTest/JUnitTestOutput.cpp
# 	cpputest/src/CppUTest/TeamCityTestOutput.cpp
# 	cpputest/src/CppUTest/TestFailure.cpp
# 	cpputest/src/CppUTest/TestOutput.cpp
# 	cpputest/src/CppUTest/MemoryLeakDetector.cpp
# 	cpputest/src/CppUTest/TestFilter.cpp
# 	cpputest/src/CppUTest/TestPlugin.cpp
# 	cpputest/src/CppUTest/TestTestingFixture.cpp
# 	cpputest/src/CppUTest/SimpleMutex.cpp
# 	cpputest/src/CppUTest/Utest.cpp
# 	cpputest/src/Platforms/${CPP_PLATFORM}/UtestPlatform.cpp
# 	)
# add_library(CppUTestExt STATIC 
# 	cpputest/src/CppUTestExt/CodeMemoryReportFormatter.cpp
# 	cpputest/src/CppUTestExt/IEEE754ExceptionsPlugin.cpp
# 	cpputest/src/CppUTestExt/MemoryReporterPlugin.cpp
# 	cpputest/src/CppUTestExt/MockFailure.cpp
# 	cpputest/src/CppUTestExt/MockSupportPlugin.cpp
# 	cpputest/src/CppUTestExt/MockActualCall.cpp
# 	cpputest/src/CppUTestExt/MockSupport_c.cpp
# 	cpputest/src/CppUTestExt/MemoryReportAllocator.cpp
# 	cpputest/src/CppUTestExt/MockExpectedCall.cpp
# 	cpputest/src/CppUTestExt/MockNamedValue.cpp
# 	cpputest/src/CppUTestExt/OrderedTest.cpp
# 	cpputest/src/CppUTestExt/MemoryReportFormatter.cpp
# 	cpputest/src/CppUTestExt/MockExpectedCallsList.cpp
# 	cpputest/src/CppUTestExt/MockSupport.cpp)
target_include_directories(CppUTest PUBLIC cpputest/include)
target_include_directories(CppUTestExt PUBLIC cpputest/include)
