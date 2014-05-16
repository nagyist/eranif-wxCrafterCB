**wxCrafter Integration for Code::Blocks IDE**
----

This plugin integrates wxCrafter - a wxWidgets RAD Tool - with Code::Blocks IDE

Build
====

Windows:

 1. Install [CodeLite IDE][1] 
 2. Install CodeBlocks SDK 13.12
 3. Install wxWidgets 2.8.12
 4. Defined an environment variable CB_SRC_DIR pointing to CodeBlocks source folder
 5. Build the workspace

Linux

 1. Install CMake
 2. Install CodeBlocks development package `sudo apt-get install codeblocks-dev`
 3. Execute CMake like this:
```
cd /path/to/plugin/sources
mkdir build-debug
cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug 
sudo make install
```
 
The above will create `libwxCrafterCB.so` and `wxCrafterCB.zip` and will install them under
`/usr/lib/codeblocks/plugins` and `/usr/share/codeblocks`

Start CodeBlocks and the plugin should be loaded

  [1]: http://codelite.org