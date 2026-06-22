## Overview
The project is a simple graphical application that generates and visualizes 2D Perlin noise in real-time. It uses custom libraries for rendering, which include support for different operating systems like Linux, Windows, and WebAssembly.

## Features
- Real-time generation of 2D Perlin noise
- Visualization of the generated noise as a heatmap on a graphical window
- Adjustable parameters (octaves and persistence) to control the noise characteristics
- Cross-platform execution: Linux, Windows, and WebAssembly

## Project Structure
```
Project/
├── build/              # .exe files produced by Main.c
├── src/                # source code
│   ├── Main.c          # Entry point
│   └── *.h             # stand alone Header-based C-files, without *.c files that implement it
├── Makefile.linux      # Linux Build configuration
├── Makefile.windows    # Windows Build configuration
├── Makefile.wine       # Wine Build configuration
└── Makefile.web        # Emscripten Build configuration
```

## Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - **Linux**: X11 for windowing, PNG and JPEG libraries for image handling
  - **Windows**: User32, GDI32, Winmm libraries
  - **WebAssembly (Emscripten)**: No specific libraries, but requires Emscripten SDK

## Build & Run
### Linux
To build and run on Linux:
```sh
cd Project/
make -f Makefile.linux all
make -f Makefile.linux exe
```

### Windows
To build and run on Windows:
```sh
cd Project/
make -f Makefile.windows all
make -f Makefile.windows exe
```

### WebAssembly (Emscripten)
To build for WebAssembly:
```sh
cd Project/
emmake make -f Makefile.web all
make -f Makefile.web exe
```

The project provides a comprehensive build and run process across different platforms, ensuring compatibility and ease of development.