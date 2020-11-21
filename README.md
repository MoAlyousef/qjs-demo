# QuickJs C++ app demo

This shows how to use to embed Javascript into a C++ app using Quickjs.
To build:
```
$ git submodule update --init
$ cmake -Bbin
$ cmake --build bin --parallel
$ ./bin/main hello.js
```