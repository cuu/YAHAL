<div align="center">
  <a href="https://git.fh-aachen.de/Terstegge/YAHAL" target="_blank" rel="noopener noreferrer">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="doc/assets/YAHAL_logo.png">
      <img src="doc/assets/YAHAL_logo_transparent.png" height="237" alt="YAHAL Logo" onerror="this.onerror=null;this.src='YAHAL_logo_transparent.png'">
    </picture>
  </a>
  <h1>Yet Another Hardware Abstraction Library</h1>
</div>

## Documentation

Visit [https://terstegge.pages.fh-aachen.de/YAHAL](https://terstegge.pages.fh-aachen.de/YAHAL) to view the full API 
documentation.

## Getting Started

### 1. MinGW64 (Minimalist GNU for Windows)
Under Windows, a rudimentary Unix environment (MinGW64) must be installed first.
For this we use [WinLibs](https://winlibs.com/), from whose site you can download the latest ZIP file with UCRT runtime 
and without LLVM support:

![WinLibs Download](doc/assets/getting-started_img1.png)

Unpack this ZIP file under `C:\`, then a new directory `C:\mingw64` must exist.

In order for the MinGW programs to work on the command line, the corresponding paths to the programs must be entered
in the path environment variable.
To do this, start the system properties and click on the 'Environment variables' button under the 'Advanced' tab
(see image below).

![Environment Variables](doc/assets/getting-started_img2.png)

Then select the `PATH` environment variable in the lower area of the newly opened window and click on
'Edit'.

Add the path `C:\mingw64\bin` to the list.
You can use the 'New' and 'Browse' buttons to do this.<br>
_Tip:_ In case of strange behavior (entries in the list are overwritten), it helps to first enter something in a new field
(e.g. "C:") before clicking on 'Browse'.

At the end, the window for editing the path environment variable should look something like this:

![Adding MinGW to PATH](doc/assets/getting-started_img3.png)

_Note:_ You will need to add new elements into the PATH environment variable in the following steps as well!

Under Linux and MacOS, please ensure that the tools `gcc`, `g++`, `make` and `cmake` are installed.
To do this, use the package management of your operating system.

### 2. ARM GNU Toolchain (ARM Cross-compiler)
At https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain you will find a button 'Download Arm GNU Toolchain'.
For your platform (Windows, Linux, MacOS), download the latest 'bare metal target' version (the name of the file **must** 
contain `arm-none-eabi`).
Make sure you have the correct processor architecture (x86_64, aarch32/64).<br>
For Windows there is an .exe file with an installer:

(e.g. `arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi.exe`)

Under Windows, run this .exe file and follow the instructions in the installer (no changes to the default settings
are necessary!).
After completing the installation, you need to extend the PATH environment variable (see above).<br>
The window for the path environment variable will then look like this, for example:

![Adding ARM GNU Toolchain to PATH](doc/assets/getting-started_img4.png)

Under Linux and MacOS, either install the corresponding version from the page above, or install the GNU ARM 
Cross-compiler via the package management of your operating system.

### 3. git
At https://git-scm.com/download/ you will find the latest 64-bit version of git for Windows, which you can install
without modifying the installer settings. 
The installation should automatically update the path environment variable:

![Adding git to PATH](doc/assets/getting-started_img5.png)

On Linux and MacOS, please make sure that git is installed.
Use the package management of your operating system to do this.

### 4. OpenOCD
OpenOCD (Open On-Chip Debugger) is a tool that we need in order to download and debug programs on our microcontroller.
At https://openocd.org/pages/getting-openocd.html you will find a link to (unofficial) binary packages for Windows:
https://github.com/xpack-dev-tools/openocd-xpack/releases.
To see all files, you have to click on 'show all assets' at the bottom of the file list on this page!
For Windows, select e.g. the ZIP file `xpack-openocd-0.12.0-1-win32-x64.zip`, which you download and extract e.g. 
to `C:\` (or another suitable location). <br>
As always, extend the path afterward:

![Adding OpenOCD to PATH](doc/assets/getting-started_img6.png)

Under Linux and MacOS, download the corresponding installation file (.tar.gz), extract it to a suitable location and 
make sure that the `bin` sub-folder is in the path (just like Windows).

### 5. Putty
PuTTY is a small program for Windows that we use in order to communicate with our microcontroller
(via a virtual serial interface).
At https://www.putty.org/ you will find the latest msi file, which can be simply installed.<br>
Under Linux and MacOS, other programs can be used for communication (e.g. `GTKTerm` under Linux).

### 6. Zadig (USB Driver)
For Windows, we also need a small utility program that installs USB drivers into the operating system.
This program is not necessary for Linux and MacOS!
Zadig can be downloaded from https://zadig.akeo.ie/ (it is a directly executable exe file).
Simply move this file to the directory `C:\mingw64\bin` so that this tool can also be found from the command line!

### 7. Editor or IDE
Generally, you should use an IDE. The IDE supported in this course is CLion (https://www.jetbrains.com/clion/).
Students of the FH Aachen have an 'academic license' with which the software can be used without restrictions.
Alternatively, you can of course also work with another IDE of your choice (e.g. VSCode) or an editor which does not
visually support the debugging of programs.

### 8. Verify the tools via command line
At this point, you should check that all important tools are installed correctly and can also be found from the 
command line.
To do this, open a new terminal window (`command.com` in Windows) and make sure that the following programs are executed
after the corresponding command has been entered manually:

`g++, make (or under Windows: mingw32-make), arm-none-eabi-g++, git , cmake, openocd, PuTTY, zadig-2.8`

If these programs are not found, check the installation and the correctness of the entries in the PATH environment
variable!

<div align="center">
<span style="color:green;font-weight:bold">
You should now have all the necessary programs installed!
</span>
</div>

### 9. Clone YAHAL
The following step installs YAHAL, the software framework for our microcontroller used in this course.
If you have not already done so, clone YAHAL in your home directory (or another suitable location).
In a terminal you can enter e.g:

`git clone https://git.fh-aachen.de/Terstegge/YAHAL.git`

### 10. Execute example program
- Change the working directory:<br>
  `cd YAHAL/examples/rp2040-launchpad/blink_simple`
- Create a new subdirectory `build` and enter it:<br>
  `mkdir build`<br>
  `cd build`
- Call cmake:<br>
  for Windows: `cmake -G "MinGW Makefiles" ..`<br>
  for Linux/MacOS: `cmake ..`
- Compile the example program:<br>
  for Windows: `mingw32-make`<br>
  for Linux/MacOS: `make`

Now connect the RP2040 launchpad board to your computer.
Windows (unlike Linux and MacOS) does not have USB drivers for this device by default, so this device, so you must now
start `zadig-2.8` from the command line. 
Click on the "Install Driver" button.
Then please be **patient** the program takes a few seconds to start working.<br>
Exit the program and **repeat** this step!

- Download and run the sample program:<br>
  for Windows: `mingw32-make upload_blink_simple`<br>
  for Linux/MacOS: `make upload_blink_simple`

If an <span style="color:red">**LED**</span> now flashes on your board, you have done it!!!

<div class="image">
  <img src="doc/assets/getting-started_img7.png" alt="Good Job!" height="200px" 
       onerror="this.onerror=null;this.src='getting-started_img7.png'"/>
</div>
