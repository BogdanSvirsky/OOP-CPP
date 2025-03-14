set (SOURCES 
    src/libcompressor.cpp
    include/libcompressor/libcompressor.hpp)

add_library(libcompressor ${SOURCES})

find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(libcompressor BZip2::BZip2 ZLIB::ZLIB GTest::GTest spdlog::spdlog)

target_include_directories(libcompressor PUBLIC include)

add_subdirectory(tests)

set_target_properties(libcompressor PROPERTIES PUBLIC_HEADER include/libcompressor/libcompressor.hpp)

install(TARGETS libcompressor 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
