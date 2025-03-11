rm -rf build
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build . --target=format
cmake --build . --target=docs
cmake --build .
cmake --install . --prefix=install
ctest