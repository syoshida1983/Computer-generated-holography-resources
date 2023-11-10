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
- For each LD, connect the anode to the power supply (+V) and the cathode to R-LD(K), G-LD(K), or B-LD(K).
- The current between +V and R-LD(K) is determined by the ratio of the input voltage to R-DRV and the resistor R2. Similarly, the currents of the other two channels are determined by G-DRV and R6 and B-DRV and R10.
- Connect variable resistors to R-VOL, G-VOL, and B-VOL to adjust the current.
- Use n-channel power MOSFETs for Q1, Q2, and Q3 and a quad operational amplifier with a typical pin assignment for the OPAMP.
- Molex connector 53047-0510 is for connection to HOLOEYE LETO-3.
![LD-driver](https://github.com/syoshida1983/Computer-generated-holography-resources/blob/images/LD-driver.jpg)
