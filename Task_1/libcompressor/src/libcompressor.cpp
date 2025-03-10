/**
 * @file libcompressor.cpp
 * @brief Source code of libcompressor library.
 */
#include <bzlib.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <libcompressor.hpp>
#include <zlib.h>

/**
 * @brief bzip2 compressing of libcompressor_Buffer object with specified.
 * parameters
 * @param input_buffer input buffer
 * @param output_buffer pointer to allocated buffer for output
 * @return 0 on success and -1 on failure
 */
int bz2_compress(libcompressor_Buffer input_buff,
                 libcompressor_Buffer* output_buff) {
  if (BZ_OK != BZ2_bzBuffToBuffCompress(
                   output_buff->data, (unsigned int*)&output_buff->size,
                   input_buff.data, input_buff.size, 1, 0, 0)) {
    return -1;
  }
  return 0;
}

/**
 * @brief zlib compressing of libcompressor_Buffer object with specified
 * parameters.
 * @param input_buffer input buffer
 * @param output_buffer pointer to allocated buffer for output
 * @return 0 on success and -1 on failure
 */
int zlib_compress(libcompressor_Buffer input, libcompressor_Buffer* output) {
  z_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;
  if (Z_OK != deflateInit(&stream, Z_DEFAULT_COMPRESSION)) {
    deflateEnd(&stream);
    return -1;
  }
  stream.avail_in = input.size;
  stream.next_in = (unsigned char*)input.data;
  stream.avail_out = output->size;
  stream.next_out = (unsigned char*)output->data;
  if (Z_STREAM_END != deflate(&stream, Z_FINISH)) {
    deflateEnd(&stream);
    return -1;
  }
  output->size = stream.total_out;
  deflateEnd(&stream);
  return 0;
}

libcompressor_Buffer
libcompressor_compress(libcompressor_CompressionAlgorithm algo,
                       libcompressor_Buffer input) {
  if (input.data == NULL || input.size == 0) {
    return {NULL, 0};
  }

  libcompressor_Buffer output = {
      (char*)malloc(sizeof(char) * (input.size + 1024)), input.size + 1024};

  if (output.data == NULL) {
    return {NULL, 0};
  }

  switch (algo) {
  case (libcompressor_Bzip):
    if (bz2_compress(input, &output) != 0) {
      free(output.data);
      output = {NULL, 0};
    }
    break;
  case (libcompressor_Zlib):
    if (zlib_compress(input, &output) != 0) {
      free(output.data);
      output = {NULL, 0};
    }
    break;
  default:
    free(output.data);
    output = {NULL, 0};
  }
  return output;
}