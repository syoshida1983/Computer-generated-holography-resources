# Computer-generated holography resources

## CGH
C++ program for hologram calculation. [Visual Studio](https://visualstudio.microsoft.com/downloads/) is required to build the program.

### Build and Run
[Wave Field Library (WFL)](http://www.laser.ee.kansai-u.ac.jp/WaveFieldTools/download/wfl.html) and [Polygon Source Library (PSL)](http://www.laser.ee.kansai-u.ac.jp/WaveFieldTools/download/psl.html) are required to build the program.
To build the program, download and install the above two libraries.
After installation, add the "include" directory in the library's installation path to the "[Additional Include Directories](https://learn.microsoft.com/en-us/cpp/build/reference/i-additional-include-directories)" of the Visual Studio project.
  Similarly, add "wfl3.lib" and "psl.lib" in the "lib" directory of the installation path to "[Additional Dependencies](https://learn.microsoft.com/en-us/cpp/build/reference/linker-property-pages#input-property-page)."

"wfl3.dll" and "psl.dll" are required to run the program.
These files are in the "bin" directory of the installation path.
[Intel Compilers Runtime Libraries](https://www.intel.com/content/www/us/en/developer/articles/tool/compilers-redistributable-libraries-by-version.html) are also required to run the program.

## Jig
Drawings of the jig used to secure the DMD evaluation board [DLPLCR6500EVM](https://www.ti.com/product/DLPLCR6500EVM/part-details/DLPLCR6500EVM) to the lab bench.
Files are provided in STEP format.

## LD-Driver
Circuit schematic and PCB layout of common anode 3-channel LD driver.
Files are provided in .sch and .brd format.
