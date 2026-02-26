cmake_minimum_required(VERSION 3.20)
project(test_netcdf4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg provides the netCDFCxx config package
find_package(netCDFCxx CONFIG REQUIRED)

add_executable(test_netcdf4 src/main.cpp)
target_link_libraries(test_netcdf4 PRIVATE netCDF::netcdf-cxx4)

# Simple CTest integration
enable_testing()
add_test(NAME netcdf4_smoke_test COMMAND test_netcdf4)
