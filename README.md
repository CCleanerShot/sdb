## PROBLEMS AND FIXES

# PROBLEM 1
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
CMake Error at /<path-to-vcpkg>/vcpkg/scripts/buildsystems/vcpkg.cmake:941 (message):
  vcpkg install failed.  See logs for more information:
  /<path-to-sdb>/sdb/build/vcpkg-manifest-install.log
Call Stack (most recent call first):
  /usr/share/cmake-3.22/Modules/CMakeDetermineSystem.cmake:124 (include)
  CMakeLists.txt:3 (project)

# FIX 1
install libncurses-dev, the error given is COMPLETELY fake news, read the error log in /<path-to-vcpkg>/vcpkg/buildtrees/libedit/config-x64-linux-dbg-err.log
