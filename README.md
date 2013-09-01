autocomplete
============
Simple autocomplete engine.  
Contains of data preprocessor, and a module for blizzard http server.  
Requires compiler with c++11 standart support (for example gcc4.7+)  

### Building procedure
    cd Autocomplete
    mkdir build
    cd build
    export CMAKE_DEFS="-DCMAKE_CXX_COMPILER=/usr/bin/g++-4.7" #this is required if your default compiler doesn't support c++11
    export CMAKE_DEFS="$CMAKE_DEFS -DCMAKE_CXX_COMPILER=/usr/bin/g++-4.7" #You can specify RELEASE build here
    cmake $CMAKE_DEFS ../
    make

### Running preprocessor
It requres file with your input data in encoding you will use further and lines splitted by \n  
First you need to build autocomplete project, than
    cd Autocomplete
    ./build/preprocessor /path/to/queries /path/to/compressed/chunks/output/file

You will get in `/path/to/compressed/chunks/output/` files like
    /path/to/compressed/chunks/output/file
    /path/to/compressed/chunks/output/file.0
    /path/to/compressed/chunks/output/file.1
    /path/to/compressed/chunks/output/file.2

### Running http server
Compile blizzard (and optionally install) as described in https://github.com/antmat/blizzard  
copy config/blizzard.xml to any file  
change in it <params> section to /path/to/compressed/chunks/output/file you used in preprocessor  
Change other values to desired ones (see https://github.com/antmat/blizzard)  
run `/path/to/blizzard/binary -c your_copied_config_file`  
You can add optional -d to daemonize
query http://localhost:your_port/?q=qwe&cnt=10  
Enjoy)
