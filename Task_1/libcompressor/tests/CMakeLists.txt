add_executable(libcompressortest libcompressortest.cpp)

target_link_libraries(libcompressortest libcompressor GTest::GTest)

set_property(TARGET libcompressor PROPERTY CXX_STANDARD 20)

include(GoogleTest)
gtest_discover_tests(libcompressortest
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/tests_results)
