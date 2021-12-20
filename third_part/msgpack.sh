# make sure you have done boost.sh doxygen.sh first

wget https://github.com/msgpack/msgpack-c/releases/download/cpp-4.0.3/msgpack-cxx-4.0.3.tar.gz
tar -zxf msgpack-cxx-4.0.3.tar.gz

export PATH=`pwd`/boost:`pwd`/doxygen/bin:$PATH

mkdir msgpack-cxx-4.0.3/sln
pushd msgpack-cxx-4.0.3/sln
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../msgpack ..
cmake --build . --target install --clean-first --config Release
popd

rm msgpack-cxx-4.0.3.tar.gz
rm -rf msgpack-cxx-4.0.3/
