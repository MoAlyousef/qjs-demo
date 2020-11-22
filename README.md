# QuickJs C++ app demo

This shows how to embed Javascript into a C++ cmake based project using Quickjs.
Quickjs is fetched automatically using CMake's FetchContent command.

To build:
```
$ cmake -Bbin
$ cmake --build bin --parallel
$ ./bin/main hello.js
```

Quickjs needs a posix environment and compiler.
