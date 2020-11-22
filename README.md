# QuickJs C++ app demo

This shows how to use to embed Javascript into a C++ app using Quickjs.
Quickjs is fetched using CMake's FetchContent command.
To build:
```
$ cmake -Bbin
$ cmake --build bin --parallel
$ ./bin/main hello.js
```

Quickjs needs a posix environment and compiler.