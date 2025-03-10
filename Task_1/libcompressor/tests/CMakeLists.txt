add_executable(libcompressortest libcompressortest.cpp)

target_link_libraries(libcompressortest libcompressor GTest::GTest)

target_include_directories(libcompressortest PRIVATE ../include)

include(GoogleTest)
gtest_discover_tests(libcompressortest
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/tests_results)
