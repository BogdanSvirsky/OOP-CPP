/**
 * @file compressor.cpp
 * @brief Implementation of compressor programm.
 */
#include "spdlog/spdlog.h"
#include <libcompressor.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Programm which compresses input string (second command line argument)
 * by specified compression algorithm (first command line argimument).
 * @return status of programm execution
 */
int main(int argc, char** argv) {
  if (argc < 3) {
    spdlog::error("Invalid arguments count!");
    exit(EXIT_FAILURE);
  }

  libcompressor_Buffer input = {strdup(argv[2]), (int)strlen(argv[2])};
  libcompressor_Buffer result;

  if (strcmp("zlib", argv[1]) == 0) {
    result = libcompressor_compress(libcompressor_Zlib, input);
  } else if (strcmp("bzip", argv[1]) == 0) {
    result = libcompressor_compress(libcompressor_Bzip, input);
  } else {
    spdlog::error("Invalid compression type!");
    exit(EXIT_FAILURE);
  }

  if (result.data == NULL) {
    spdlog::error("Compression failed!");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < result.size; i++) {
    printf("%.2hhx ", result.data[i]);
  }
  printf("\n");

  exit(EXIT_SUCCESS);
}