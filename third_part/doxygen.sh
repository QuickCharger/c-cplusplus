apt install flex
apt install bison
apt install python2.7

wget https://www.doxygen.nl/files/doxygen-1.9.2.src.tar.gz
tar -zxf doxygen-1.9.2.src.tar.gz

mkdir doxygen-1.9.2/sln
pushd doxygen-1.9.2/sln
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../doxygen ..
cmake --build . --target install --clean-first --config Release
popd

rm -rf doxygen-1.9.2.src.tar.gz
rm -rf doxygen-1.9.2
