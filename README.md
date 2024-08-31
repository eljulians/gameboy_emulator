# GameBoy emulator

A GameBoy emulator written in C++. Semi-functioning at the moment, Dr. Mario is
working fine, but others such as Tetris currently get stuck after the menus due
to some tough bug I haven't figured out yet.

Versions:
* c++20 standard
* clang++ 18.1.8
* make 4.4.1
* SDL 2.30.6-1
* spdlog: 1.14.1-1
* Testing: Catch v2.13.10

TODO:
* Get rid of the dumpster fire of the Makefile and use CMake
* Implement rest of memory bank controllers (currently ROM only and MBC1
* Implement sound
* Add contextual menus for saving, loading, etc.
