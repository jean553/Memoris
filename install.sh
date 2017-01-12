echo Add needed repo
add-apt-repository -y ppa:ubuntu-toolchain-r/test

echo Update all repo
apt-get -qq update

echo Install dependancies
apt-get -qq install -y g++-4.9 libsfml-dev cmake clang-3.5 git

echo Remove previously added repo
add-apt-repository -y --remove ppa:ubuntu-toolchain-r/test

git clone https://github.com/jean553/Memoris
cd Memoris/
mkdir build && cd build/
cmake ..
make
cd ..
./bin/Memoris
