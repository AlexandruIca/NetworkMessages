# Client/Server Communication
This project follows [this series](https://www.youtube.com/watch?v=2hNdkYInj4g&t=2311s) that uses ASIO to implement a framework suitable for massively-multiplayer-online games.

# Building
You must have:
- python
- conan
- cmake
- A C++17 compliant compiler
```sh
mkdir build && cd build

# Or use GCC or whatever compiler you want(or let it be the choice of cmake)
export CC=clang
export CXX=clang++

cmake \
    -DENABLE_CLANG_TIDY=ON \ # Runs clang-tidy at build time for every file
    -DENABLE_SANITIZER_ADDRESS=ON \ # Address sanitizer(recommended)
    -DENABLE_SANITIZER_UNDEFINED=ON \ # Undefined sanitizer(recommended)
    -DBUILD_TESTS=ON \ # To build the tests(-DBUILD_TESTS=OFF not to)
    -DBUILD_EXAMPLES=ON \ # To build the examples(-DBUILD_EXAMPLES=OFF not to)
    ..

mv compile_commands.json .. # Probably useful for IDEs/language servers

cmake --build . # Actually build the project
```
All dependencies are specified in [scrips/manifest.scm](./scripts/manifest.scm), you can use that to create a GUIX environment, the only additional thing you would have to do is `pip install conan`.
