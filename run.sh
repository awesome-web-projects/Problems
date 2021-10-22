#!/usr/bin/env bash
set -e
set -u
set -o pipefail

export CC=$(which clang)
export CXX=$(which clang++)
export RUNNER=$1

mkdir -p bin tests output
rm -rf bin/* 
rm -rf output/*

# dd if=/dev/random of=tests/input01.txt bs=32 count=1
# dd if=/dev/random of=tests/input02.txt bs=32 count=1
# dd if=/dev/random of=tests/input03.txt bs=32 count=1
# head -c 32 /dev/zero > tests/input04.txt
# dd if=/dev/random of=tests/input05.txt bs=32 count=1
# head -c 32 /dev/zero > tests/input06.txt

cd bin/
CC=$CC CXX=$CXX cmake -I include -DCMAKE_CXX_FLAGS="-w -fsanitize=address -fsanitize=leak" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../
clang-tidy -checks=* -p bin/ ../src/${RUNNER}.cpp
make -j 12
cd ../

counter=0
for files in tests/*;
do
    echo "Running with input $files"
    ((counter+=1))
    bin/${RUNNER} < $files > output/${counter}_out.txt
done