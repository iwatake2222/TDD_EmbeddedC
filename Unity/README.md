# About
テスト駆動開発による組み込みプログラミングの第10章(モックオブジェクト)までの写経

- Target: MinGW on Windows10 (can be any)
- Editor: VSCode (can be any)
- Unit Test Framework: Unity
- Build tool: CMake

# How to Build
For test code

```sh:test_code
cd TDD_EmbeddedC/Unity/Build
cmake .. -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=DEBUG -DTARGET_GROUP=test
make
# ctest --verbose
./bin/project1.exe -v
```

For product code

```sh:product_code
cd TDD_EmbeddedC/Unity/Build
cmake .. -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=DEBUG -DTARGET_GROUP=production
make clean all
./bin/project1.exe
```

# How to use cmock
- Install ruby (for MinGW `pacman -S ruby`)
- Create the directory named 'mocks' (`mkdir mocks`)
- `ruby.exe ../Test/External/cmock/lib/cmock.rb ../Include/MyFunc.h`

# How to generate test runner code
`python ../generate_TEST_RUNNER.py ../Test/TestCode.cpp`

### Note
I use the same binary name(project1.exe) both for test code and product code, so that I can use the same command to run the project with test/production option. (They should be different names, but I'm just lazy...)

# Acknowledge
http://www.throwtheswitch.org/unity/
