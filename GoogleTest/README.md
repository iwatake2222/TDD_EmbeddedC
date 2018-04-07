# About
テスト駆動開発による組み込みプログラミングの第10章(モックオブジェクト)までの写経 + Google Mock(for C and C++)

- Target: MinGW on Windows10 (can be any)
- Editor: VSCode (can be any)
- Unit Test Framework: GoogleTest
- Build tool: CMake

# How to Clone the Project
```sh
git clone https://github.com/take-iwiw/TDD_EmbeddedC.git
cd TDD_EmbeddedC/GoogleTest
git submodule update -i
```

# How to Build
For test code

```sh:test_code
cd Build
cmake .. -G "MSYS Makefiles" -DTARGET_GROUP=test -DCMAKE_BUILD_TYPE=DEBUG
make
# ctest --verbose
./bin/project1.exe -v
```

For product code

```sh:product_code
cd Build
cmake .. -G "MSYS Makefiles" -DTARGET_GROUP=production -DCMAKE_BUILD_TYPE=DEBUG
make clean all
./bin/project1.exe
```

### Note
I use the same binary name(project1.exe) both for test code and product code, so that I can use the same command to run the project with test/production option. (They should be different names, but I'm just lazy...)

# Acknowledge
https://github.com/google/googletest

