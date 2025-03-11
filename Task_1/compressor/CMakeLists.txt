add_executable(compressor src/compressor.cpp)

find_package(spdlog REQUIRED)

target_link_libraries(compressor PRIVATE libcompressor spdlog::spdlog)

install(TARGETS compressor RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
