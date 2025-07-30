if [[ -z "$1" ]]; then
    echo "expected (1) argument for program name, given 0"
    exit -1
fi

cd ./build
cmake --build .
sudo setcap CAP_SYS_PTRACE=+eip ./tools/sdb
./tools/sdb $1
