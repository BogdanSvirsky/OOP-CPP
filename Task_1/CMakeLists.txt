cmake_minimum_required(VERSION 3.15)

project(Task_1)

enable_testing()

set (CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_subdirectory(compressor)
add_subdirectory(libcompressor)

include(GNUInstallDirs)

find_program(CLANG_TIDY "clang-tidy")

if (CLANG_TIDY)
    set(
        CLANG_TIDY_COMMAND 
        ${CLANG_TIDY}
        --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
    )
    set_target_properties(compressor libcompressor PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
else()
    message("Can't find clang-tidy!")
endif()

find_program(CLANG_FORMAT "clang-format")

if (CLANG_FORMAT)
    file(GLOB_RECURSE MY_SOURCES "*.cpp" "*.hpp")
    add_custom_target(
        format COMMAND
        ${CLANG_FORMAT}
        -i
        ${MY_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
else()
    message("Can't find clang-format!")
endif()


find_package(Doxygen REQUIRED)

if (DOXYGEN_FOUND)
    set (DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set (DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(
        docs 
        ${CMAKE_SOURCE_DIR}/compressor/src
        ${CMAKE_SOURCE_DIR}/libcompressor/include
        ${CMAKE_SOURCE_DIR}/libcompressor/src
        ${CMAKE_SOURCE_DIR}/libcompressor/tests
        COMMENT "Generating documentation"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
else()
    message("Can't find doxygen!")
endif()

if (MSVC) 
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()