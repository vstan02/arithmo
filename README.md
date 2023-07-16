# Arithmo
> A fast and simple-to-use library for math expressions processing

[![Version: v0.1.0](https://img.shields.io/badge/version-v0.0.0-blue)](https://vstan02.github.io/arithmo)
[![License: GPL v3](https://img.shields.io/badge/license-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)

## Contents
- [Usage](#usage)
- [Building and Installation](#building-and-installation)
    - [Dependencies](#dependencies)
    - [Building the project](#building-the-project)
    - [Running example](#running-example)
    - [Installing](#installing)
- [License](#license)
- [Contributing](#contributing)

## Usage
Here is an example of usage (for the full version see [demo/main.c](https://github.com/vstan02/conix/blob/master/demo/main.c) file):
```c
const char* expression = "(23 - 4) * 3";

// Creating an new arithmo instance:
artm_calc_t* calc = artm_calc_init(5); // 5 is the approximate number of variables that will be used

// Processing a mathematical expression:
artm_result_t result = artm_calc_process(calc, expression);
switch (result.status) {
  case ARTM_NULL_CALC:
    return printf("[ERROR] NULL_CALC\n");
  case ARTM_NULL_EXPR:
    return printf("[ERROR] NULL_EXPR\n");
  case ARTM_ALLOC_ERR:
    return printf("[ERROR] ALLOC_ERR\n");
  case ARTM_INV_TOKEN:
    return printf("[ERROR] INV_TOKEN\n");
  case ARTM_UNDEF_VAR:
    return printf("[ERROR] UNDEF_VAR\n");
  case ARTM_SUCCESS:
    return printf("[SUCCESS] %s = %g\n", expression, result.as.value);
}

// Destroying the instance:
artm_calc_free(calc);
```

After project building you can run this example as you can see [here](#running-demo).

## Building and Installation

### Dependencies
- C compiler (gcc, clang, etc...)
- cmake (>= 3.17)

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

### Running example
```
./example
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
