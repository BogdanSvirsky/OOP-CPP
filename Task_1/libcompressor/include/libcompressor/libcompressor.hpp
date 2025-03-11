/**
 * @file libcompressor.hpp
 * @brief Public header of libcompressor library.
 */
#pragma once

/**
 * @brief Data buffer for libcompressor.
 */
struct libcompressor_Buffer {
  char* data;
  int size;
};

/**
 * @brief Enumeration of compresion algorithms in libcompressor.
 */
enum libcompressor_CompressionAlgorithm {
  libcompressor_Zlib,
  libcompressor_Bzip
};

/**
 * @brief Compressing Buffer by CompressionAlgorithm.
 * @param algo compression algorithm
 * @param input input buffer
 * @return result buffer which is equal to { NULL, 0 } on failure
 */
libcompressor_Buffer
libcompressor_compress(libcompressor_CompressionAlgorithm algo,
                       libcompressor_Buffer input);