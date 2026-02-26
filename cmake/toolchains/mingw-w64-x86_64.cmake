# CMake toolchain for cross-compiling to Windows x86-64 using MinGW-w64 on Linux.
# Used by the GitHub Actions CI when building the Windows-cross job.
# Chained via VCPKG_CHAINLOAD_TOOLCHAIN_FILE so vcpkg picks up the right compilers.

set(CMAKE_SYSTEM_NAME    Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(MINGW_PREFIX x86_64-w64-mingw32)

find_program(CMAKE_C_COMPILER   ${MINGW_PREFIX}-gcc-posix
             NAMES ${MINGW_PREFIX}-gcc
             REQUIRED)
find_program(CMAKE_CXX_COMPILER ${MINGW_PREFIX}-g++-posix
             NAMES ${MINGW_PREFIX}-g++
             REQUIRED)
find_program(CMAKE_RC_COMPILER  ${MINGW_PREFIX}-windres REQUIRED)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
