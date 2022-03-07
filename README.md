# OpenGL-Explorer

A toy example to explore both C++17 and OpenGL (4.1) on an m1 mac, for ARM specifically (no rosetta2 here).

## How to build

First, please to make sure that:
* you have a clang version that supports C++17 (I used `Apple clang version 13.0.0 (clang-1300.0.29.30)` for this exercise),
* the following tools: `make`, `cmake`, `c++`,
* a macintosh computer (this exercise does not supports other platforms yet).

Now, in the root folder: `cmake . && make && ./opengl-explorer`.

I wrote a blog post about this exercise here, please take a look for the troubleshootings: [blog post](https://carette.xyz/opengl_and_cpp_on_m1_mac).

## Screenshot

![rgb_triangle.png](docs/rgb_triangle.png)
