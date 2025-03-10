#include "libcompressor/libcompressor.hpp"
#include "gtest/gtest.h"
#include <string.h>

TEST(CompressTest, NotEmptyBuffer) {
  libcompressor_Buffer buff = {strdup("adasdasda"), 10};

  auto result = libcompressor_compress(libcompressor_Zlib, buff);

  EXPECT_NE(result.data, (char*)0);
  EXPECT_NE(result.size, 0);

  result = libcompressor_compress(libcompressor_Bzip, buff);

  EXPECT_NE(result.data, (char*)0);
  EXPECT_NE(result.size, 0);
}

TEST(CompressTest, EmptyBuffer) {
  libcompressor_Buffer buff = {strdup("\0"), 0};

  auto result = libcompressor_compress(libcompressor_Zlib, buff);

  ASSERT_EQ(result.data, (char*)0);
  ASSERT_EQ(result.size, 0);

  result = libcompressor_compress(libcompressor_Bzip, buff);

  ASSERT_EQ(result.data, (char*)0);
  ASSERT_EQ(result.size, 0);
}

TEST(CompressTest, zlibTest) {
  libcompressor_Buffer buff = {strdup("test_string"), 11};
  unsigned char correct_result[] = {0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89,
                                    0x2f, 0x2e, 0x29, 0xca, 0xcc, 0x4b, 0x07,
                                    0x00, 0x1c, 0x79, 0x04, 0xb7};
  int correct_size = 19;

  auto result = libcompressor_compress(libcompressor_Zlib, buff);

  ASSERT_EQ(correct_size, result.size);

  for (int i = 0; i < correct_size; i++) {
    ASSERT_EQ((unsigned char)result.data[i], correct_result[i]);
  }
}

TEST(CompressTest, bZipTest) {
  libcompressor_Buffer buff = {strdup("test_string"), 11};
  unsigned char correct_result[] = {
      0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c,
      0x69, 0x05, 0x00, 0x00, 0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c,
      0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30, 0x22, 0x50, 0xdf, 0x04,
      0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0,
  };
  int correct_size = 48;

  auto result = libcompressor_compress(libcompressor_Bzip, buff);

  ASSERT_EQ(correct_size, result.size);

  for (int i = 0; i < correct_size; i++) {
    ASSERT_EQ((unsigned char)result.data[i], correct_result[i]);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}