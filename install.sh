#!/usr/bin/env bash
add-apt-repository ppa:ubuntu-toolchain-r/test -y
apt-get update
apt-get install g++-4.9 libsfml-dev cmake clang-3.5 git -y
add-apt-repository --remove ppa:ubuntu-toolchain-r/test -y

git clone https://github.com/jean553/Memoris
cd ./Memoris/
mkdir build && cd build/
cmake ..
make
./bin/Memoris
