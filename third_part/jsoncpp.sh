wget https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.tar.gz
tar -zxf 1.9.5.tar.gz
pushd jsoncpp-1.9.5
mkdir tmp
pushd tmp
cmake -D CMAKE_INSTALL_PREFIX=`pwd`/../../jsoncpp ..
make
make install
popd
popd

rm -rf 1.9.5.tar.gz
rm -rf jsoncpp-1.9.5/
