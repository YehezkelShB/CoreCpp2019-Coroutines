I use vcpkg for including Boost in `02-future-then` project.
For this to work, the simplest option is to pass `-DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>\scripts\buildsystems\vcpkg.cmake` in CMake command-line (or set it in `CMakeSettings.json` file generated by Visual Studio).
