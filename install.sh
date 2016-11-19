add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get update
apt-get install -y g++-4.9 libsfml-dev cmake clang-3.5 git
add-apt-repository -y --remove ppa:ubuntu-toolchain-r/test

git clone https://github.com/jean553/Memoris
cd ./Memoris/
mkdir build && cd build/
cmake ..
make
./bin/Memoris
