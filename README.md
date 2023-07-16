# Arithmo
> A fast and simple-to-use library for math expressions processing

[![Version: v0.0.0](https://img.shields.io/badge/version-v0.0.0-red)](https://vstan02.github.io/arithmo)
[![License: GPL v3](https://img.shields.io/badge/license-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)

## Contents
- [Building and Installation](#building-and-installation)
    - [Dependencies](#dependencies)
    - [Building the project](#building-the-project)
    - [Running tests](#running-tests)
    - [Installing](#installing)
- [License](#license)
- [Contributing](#contributing)

## Building and Installation

### Dependencies
- C compiler (gcc, clang, etc...)
- cmake (>= 3.16)

These packages can usually be installed through your distributions package manager.

### Building the project
To build the project, we first need to create a separate build directory:
```
mkdir build
```

Now that we've created our build directory (assuming it's created in the project root), we can `cd` into it and run `cmake` and pass the parent directory path to it, which is where the `CMakeLists.txt` file is located:
```
cd build
cmake ..
```

Once `cmake` is done generating makefiles, we can build the library by running `make` inside our build directory:
```
make
```

### Installing
To install the library run:
```
sudo make install
```
By default, the libraries and headers will be installed in `/usr/local/lib` and `/usr/local/include` directories.

## License
Arithmo is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
For more details, see [LICENSE](https://github.com/vstan02/arithmo/blob/master/LICENSE) file.

## Contributing
Contributions are welcome.
If you have a feature request, or have found a bug, feel free to open a [new issue](https://github.com/vstan02/arithmo/issues/new).
If you wish to contribute code, see [CONTRIBUTING.md](https://github.com/vstan02/arithmo/blob/master/CONTRIBUTING.md) for more details.
