# Containers
[![CMake](https://github.com/grzegorz-grzeda/containers/actions/workflows/cmake.yml/badge.svg)](https://github.com/grzegorz-grzeda/containers/actions/workflows/cmake.yml)

Simple containers library in C.

This is a [G2EPM](https://github.com/grzegorz-grzeda/g2epm) library.

## Run tests
Just run `./test.sh`.

## How to compile and link it?

Just include this directory in your CMake project.

Example `CMakeLists.txt` content:
```
...

add_subdirectory(<PATH TO CONTAINERS LIBRARY>)

target_link_libraries(${PROJECT_NAME} PRIVATE containers)

...
```

## Documentation
If you want, you can run `doxygen` to generate HTML documentation. It will be available in `documentation` 
directory.


# Copyright
This library was written by G2Labs Grzegorz Grzęda, and is distributed under MIT Licence. Check the `LICENSE` file for
more details.