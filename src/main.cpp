#include <iostream>
#include <vector>
#include <cstdlib>   // std::remove
#include <netcdf>    // netcdf-cxx4

// Simple smoke-test: write a NetCDF-4 file, read it back, verify values.
int main()
{
    const std::string filename = "test_output.nc";
    const std::size_t NX = 6;
    const std::size_t NY = 12;

    // ---------------------------------------------------------------
    // Write
    // ---------------------------------------------------------------
    try {
        netCDF::NcFile ncOut(filename, netCDF::NcFile::replace);

        netCDF::NcDim xDim = ncOut.addDim("x", NX);
        netCDF::NcDim yDim = ncOut.addDim("y", NY);

        netCDF::NcVar data = ncOut.addVar("data", netCDF::ncFloat,
                                          {xDim, yDim});
        data.putAtt("units", "K");
        data.putAtt("long_name", "test temperature field");

        std::vector<float> buf(NX * NY);
        for (std::size_t i = 0; i < NX * NY; ++i)
            buf[i] = static_cast<float>(i) * 0.5f;

        data.putVar(buf.data());
        std::cout << "[write] OK – " << filename << "\n";
    } catch (const netCDF::exceptions::NcException& e) {
        std::cerr << "[write] NetCDF error: " << e.what() << "\n";
        return 1;
    }

    // ---------------------------------------------------------------
    // Read back
    // ---------------------------------------------------------------
    try {
        netCDF::NcFile ncIn(filename, netCDF::NcFile::read);

        auto xDim = ncIn.getDim("x");
        auto yDim = ncIn.getDim("y");
        if (xDim.getSize() != NX || yDim.getSize() != NY) {
            std::cerr << "[read] Dimension mismatch!\n";
            return 1;
        }

        auto dataVar = ncIn.getVar("data");
        std::vector<float> buf(NX * NY);
        dataVar.getVar(buf.data());

        // Verify a few known values
        for (std::size_t i = 0; i < NX * NY; ++i) {
            float expected = static_cast<float>(i) * 0.5f;
            if (buf[i] != expected) {
                std::cerr << "[read] Value mismatch at index " << i
                          << ": got " << buf[i]
                          << ", expected " << expected << "\n";
                return 1;
            }
        }
        std::cout << "[read]  OK – all " << NX * NY << " values verified\n";
    } catch (const netCDF::exceptions::NcException& e) {
        std::cerr << "[read] NetCDF error: " << e.what() << "\n";
        return 1;
    }

    // Clean up
    std::remove(filename.c_str());

    std::cout << "All tests passed.\n";
    return 0;
}
