wget https://github.com/msgpack/msgpack-c/releases/download/cpp-4.0.3/msgpack-cxx-4.0.3.tar.gz
tar -zxf msgpack-cxx-4.0.3.tar.gz

pushd msgpack-cxx-4.0.3/
mkdir tmp
pushd tmp
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../msgpack ..
make
make install
popd
popd

rm msgpack-cxx-4.0.3.tar.gz
rm -rf msgpack-cxx-4.0.3/
