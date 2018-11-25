# Community Compiler for Dusk

The Dusk original Community Compiler project from the community of thebennybox's YouTube channel and Discord server

# Building

## Building on Unix systems

```
mkdir build && cd build
cmake .. && make
```

The command `cmake ..` generates build files in the current directory, based on the CMakeLists.txt file in the parent directory.
`make` builds the project, and creates the binary `CommunityCompiler`.

## Building on Windows

```
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017 Win64"
```

This creates a `.sln` file in the directory, which can then be used as any other Visual Studio project.
