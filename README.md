# C Template Code

This repository provides a template for a C project that includes support for building static libraries and executable binaries. The Makefile simplifies common build tasks.

## Features
- Compile source code into an executable binary
- Generate a static library
- Inspect the generated static library
- Debug builds and custom build targets

## Requirements
- `gcc` or `icx` (or any compatible C compiler)
- `make`
- Optional: `gnuplot` for visualizations (if applicable)

## Usage

### 1. Compile the Project
To build the project and generate the executable binary:
```bash
make
```

### 2. Run the Executable
After compiling, you can execute the program using:
```bash
make execute
```

### 3. Generate Static Library
To create a static library from the source code:
```bash
make lib
```

### 4. Inspect the Static Library
To view the symbols in the generated static library:
```bash
make inspect
```

### 5. Clean Build Artifacts
To remove all compiled files and intermediate build artifacts:
```bash
make clean
```

### 6. Debug Build
To compile with debug flags:
```bash
make debug
```

### 7. Build Other Libraries
If your project includes submodules or parts with their own Makefiles, build them with:
```bash
make build-other
```

## Visualizations (Optional)
If you have `gnuplot` installed, you can generate visualizations such as PNG or GIF plots using:
```bash
make png
make gif
```

## Additional Information
This template is designed to be flexible and can be customized to suit various C projects. The Makefile supports both `gcc` and `icx` compilers and can be easily extended for other tools or targets.

---
Written by **Croyfet** in 2022, updated in 2024 for improved functionality and usability.

