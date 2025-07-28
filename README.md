A debugger created with the help of the book, "Building A Debugger" by Sy Brand

# INSTALLATION
- in a different folder, `git clone git@github.com:microsoft/vcpkg.git`
- `cd ./build`
- `cmake .. -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake`
- `cmake --build .`

# PROBLEMS AND FIXES

## PROBLEM 1
libedit currently requires the following programs from the system package manager:
    autoconf autoheader aclocal automake libtoolize
On Debian and Ubuntu derivatives:
    sudo apt install autoconf libtool
[removed for simplicity]
error: building libedit:x64-linux failed with: BUILD_FAILED
See https://learn.microsoft.com/vcpkg/troubleshoot/build-failures?WT.mc_id=vcpkg_inproduct_cli for more information.
Elapsed time to handle libedit:x64-linux: 8.2 s
Please ensure you're using the latest port files with `git pull` and `vcpkg update`.
Then check for known issues at:
  https://github.com/microsoft/vcpkg/issues?q=is%3Aissue+is%3Aopen+in%3Atitle+libedit
You can submit a new issue at:
  https://github.com/microsoft/vcpkg/issues/new?title=[libedit]+Build+error+on+x64-linux&body=Copy%20issue%20body%20from%20%2Fhome%2Fcc2%2Frepos%2Fsdb%2Fbuild%2Fvcpkg_installed%2Fvcpkg%2Fissue_body.md

-- Running vcpkg install - failed
CMake Error at <path-to-vcpkg>/vcpkg/scripts/buildsystems/vcpkg.cmake:941 (message):
  vcpkg install failed.  See logs for more information:
  <path-to-sdb>/sdb/build/vcpkg-manifest-install.log
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/CMakeDetermineSystem.cmake:124 (include)
  CMakeLists.txt:3 (project)

## FIX 1
install libncurses-dev, the error given is COMPLETELY fake news, read the error log in <path-to-vcpkg>/vcpkg/buildtrees/libedit/config-x64-linux-dbg-err.log

## PROBLEM 2
<path-to-sdb>/tools/sdb.cpp:12:10: fatal error: editline/readline.h: No such file or directory
   12 | #include <editline/readline.h>
      |          ^~~~~~~~~~~~~~~~~~~~~
compilation terminated.
gmake[2]: *** [tools/CMakeFiles/sdb.dir/build.make:76: tools/CMakeFiles/sdb.dir/sdb.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:916: tools/CMakeFiles/sdb.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2

## FIX 2
install package `libedit-dev` (what is the point of needing vcpkg if i need something else...)

## PROBLEM 3
cannot globally attach to processes not a child of sdb

# FIX 3 (UNVERIFIED)
`echo 0 > /proc/sys/kernel/yama/ptrace_scope` OR `setcap CAP_SYS_PTRACE=+eip sdb`
